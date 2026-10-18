#!/usr/bin/env python3
"""Rift save inspector for Pokémon Right / Pokémon Left (Rift contract v2).

Reads a 128 KiB .sav, finds the newest valid save slot, rebuilds the PC storage
(flash sectors 5-13) and prints the RiftRecord plus how many Pokémon sit in each box.
Identical copy in both repos: tools/rift/rift_savetool.py. Read-only: never writes the .sav.

  python3 tools/rift/rift_savetool.py path/to/game.sav
  python3 tools/rift/rift_savetool.py --json path/to/game.sav
  python3 tools/rift/rift_savetool.py --selftest
"""
import json
import struct
import sys

SECTOR_SIZE = 0x1000
SECTOR_DATA_SIZE = 3968
FOOTER_OFFSET = SECTOR_DATA_SIZE + 116          # after SaveBlock3 chunk
SECTOR_SIGNATURE = 0x08012025
SECTORS_PER_SLOT = 14
STORAGE_FIRST_ID, STORAGE_LAST_ID = 5, 13

RIFT_MAGIC = 0x54464952
RIFT_VERSION = 2
RIFT_RECORD_OFFSET = 34144
RIFT_RECORD_SIZE = 340
RIFT_STORAGE_SIZE = 34484
BOXES, PER_BOX, BOXMON_SIZE = 14, 30, 80
BOXES_OFFSET = 4                                # u8 currentBox, then 4-byte aligned boxes
GAMES = {0: "none", 1: "Right", 2: "Left"}
PROGRESS = {0: "none", 1: "playing", 2: "first finish", 3: "second finish"}


def crc16_ccitt_false(data: bytes) -> int:
    crc = 0xFFFF
    for b in data:
        crc ^= b << 8
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
    return crc


def sector_checksum(data: bytes) -> int:
    total = sum(struct.unpack_from("<%dI" % (len(data) // 4), data)) & 0xFFFFFFFF
    return ((total >> 16) + total) & 0xFFFF


def read_slots(raw: bytes):
    slots = []
    for slot in range(2):
        sectors, counters = {}, set()
        for i in range(SECTORS_PER_SLOT):
            base = (slot * SECTORS_PER_SLOT + i) * SECTOR_SIZE
            sec = raw[base:base + SECTOR_SIZE]
            sid, chk, sig, counter = struct.unpack_from("<HHII", sec, FOOTER_OFFSET)
            if sig != SECTOR_SIGNATURE or sid >= SECTORS_PER_SLOT:
                continue
            sectors[sid] = (sec[:SECTOR_DATA_SIZE], chk)
            counters.add(counter)
        if len(sectors) == SECTORS_PER_SLOT and len(counters) == 1:
            slots.append({"slot": slot, "counter": counters.pop(), "sectors": sectors})
    return slots


def rebuild_storage(slot):
    data, warnings = b"", []
    for sid in range(STORAGE_FIRST_ID, STORAGE_LAST_ID + 1):
        chunk, chk = slot["sectors"][sid]
        size = min(SECTOR_DATA_SIZE, RIFT_STORAGE_SIZE - (sid - STORAGE_FIRST_ID) * SECTOR_DATA_SIZE)
        if size <= 0:
            break
        if sector_checksum(chunk[:size]) != chk:
            warnings.append("sector %d checksum mismatch (save not written by a contract-v2 build?)" % sid)
        data += chunk[:size]
    return data, warnings


def parse_record(storage: bytes):
    rec = storage[RIFT_RECORD_OFFSET:RIFT_RECORD_OFFSET + RIFT_RECORD_SIZE]
    magic, version, last, first, pr, pl, unsealed, gender = struct.unpack_from("<IHBBBBBB", rec, 0)
    name = rec[0x0C:0x14]
    tid = struct.unpack_from("<I", rec, 0x14)[0]
    count, returned = rec[0x18], rec[0x19]
    levels = list(rec[0x1A:0x1D])
    overflow = struct.unpack_from("<H", rec, 0x110)[0]
    checksum = struct.unpack_from("<H", rec, 0x150)[0]
    anchors = [bool(rec[0x20 + i * BOXMON_SIZE + 19] & 0x02) for i in range(3)]
    return {
        "magic_ok": magic == RIFT_MAGIC,
        "version": version,
        "checksum_ok": checksum == crc16_ccitt_false(rec[:0x150]),
        "last_written_by": GAMES.get(last, "?%d" % last),
        "first_game": GAMES.get(first, "?%d" % first),
        "progress_right": PROGRESS.get(pr, "?%d" % pr),
        "progress_left": PROGRESS.get(pl, "?%d" % pl),
        "boxes_unsealed": bool(unsealed),
        "player_gender": gender,
        "player_name_bytes": name.hex(),
        "trainer_id": "%05d/%05d" % (tid & 0xFFFF, tid >> 16),
        "anchored_count": count,
        "anchored_present": anchors,
        "anchored_returned_bits": returned,
        "anchored_levels": levels,
        "overflow_boxes_mask": overflow,
    }


def box_counts(storage: bytes):
    counts = []
    for box in range(BOXES):
        n = 0
        for pos in range(PER_BOX):
            off = BOXES_OFFSET + (box * PER_BOX + pos) * BOXMON_SIZE
            if storage[off + 19] & 0x02:   # hasSpecies bit (byte 19, bit 1)
                n += 1
        counts.append(n)
    return counts


def inspect(raw: bytes):
    if len(raw) < 32 * SECTOR_SIZE:
        raise SystemExit("not a 128 KiB flash save (%d bytes)" % len(raw))
    slots = read_slots(raw)
    if not slots:
        raise SystemExit("no complete save slot found (empty or corrupt save)")
    slot = max(slots, key=lambda s: s["counter"])
    storage, warnings = rebuild_storage(slot)
    counts = box_counts(storage)
    return {
        "slot": slot["slot"], "counter": slot["counter"], "warnings": warnings,
        "current_box": storage[0] + 1,
        "rift": parse_record(storage),
        "boxes_right_1_7": counts[:7], "boxes_left_8_14": counts[7:],
    }


def build_test_save(record_overrides=None, mons=None) -> bytes:
    """Builds a synthetic 128 KiB save (one valid slot) for --selftest and for agents' fixtures."""
    storage = bytearray(RIFT_STORAGE_SIZE)
    for box, pos in (mons or []):
        off = BOXES_OFFSET + (box * PER_BOX + pos) * BOXMON_SIZE
        storage[off:off + 4] = b"\x01\x00\x00\x00"
        storage[off + 19] = 0x02
    rec = bytearray(RIFT_RECORD_SIZE)
    fields = {"last": 1, "first": 1, "pr": 2, "pl": 0, "unsealed": 0, "gender": 0}
    fields.update(record_overrides or {})
    struct.pack_into("<IHBBBBBB", rec, 0, RIFT_MAGIC, RIFT_VERSION, fields["last"], fields["first"],
                     fields["pr"], fields["pl"], fields["unsealed"], fields["gender"])
    rec[0x18] = 3
    rec[0x1A:0x1D] = bytes([5, 10, 15])
    struct.pack_into("<H", rec, 0x150, crc16_ccitt_false(bytes(rec[:0x150])))
    storage[RIFT_RECORD_OFFSET:RIFT_RECORD_OFFSET + RIFT_RECORD_SIZE] = rec
    raw = bytearray(b"\xFF" * (32 * SECTOR_SIZE))
    for sid in range(SECTORS_PER_SLOT):
        sec = bytearray(SECTOR_SIZE)
        if STORAGE_FIRST_ID <= sid <= STORAGE_LAST_ID:
            start = (sid - STORAGE_FIRST_ID) * SECTOR_DATA_SIZE
            chunk = bytes(storage[start:start + SECTOR_DATA_SIZE])
            sec[:len(chunk)] = chunk
            chk = sector_checksum(chunk)
        else:
            chk = 0
        struct.pack_into("<HHII", sec, FOOTER_OFFSET, sid, chk, SECTOR_SIGNATURE, 7)
        raw[sid * SECTOR_SIZE:(sid + 1) * SECTOR_SIZE] = sec
    return bytes(raw)


def selftest():
    assert crc16_ccitt_false(b"123456789") == 0x29B1
    raw = build_test_save(mons=[(0, 0), (6, 29), (7, 0)])
    out = inspect(raw)
    r = out["rift"]
    assert r["magic_ok"] and r["checksum_ok"] and r["version"] == RIFT_VERSION, r
    assert r["last_written_by"] == "Right" and r["progress_right"] == "first finish", r
    assert out["boxes_right_1_7"] == [1, 0, 0, 0, 0, 0, 1] and out["boxes_left_8_14"][0] == 1, out
    assert not out["warnings"], out["warnings"]
    print("selftest OK")


def main(argv):
    if "--selftest" in argv:
        selftest()
        return
    paths = [a for a in argv if not a.startswith("--")]
    if len(paths) != 1:
        raise SystemExit(__doc__)
    with open(paths[0], "rb") as f:
        out = inspect(f.read())
    if "--json" in argv:
        print(json.dumps(out, indent=2))
        return
    r = out["rift"]
    print("Save slot %d (counter %d), current box %d" % (out["slot"], out["counter"], out["current_box"]))
    for w in out["warnings"]:
        print("WARNING:", w)
    if not r["magic_ok"]:
        print("No Rift record: legacy (pre-contract) save.")
    else:
        print("Rift record v%d, checksum %s" % (r["version"], "OK" if r["checksum_ok"] else "BAD"))
        print("  last written by %s; first game finished: %s" % (r["last_written_by"], r["first_game"]))
        print("  Right: %s | Left: %s | boxes unsealed: %s" % (r["progress_right"], r["progress_left"], r["boxes_unsealed"]))
        print("  trainer ID %s; anchors %d present=%s returned=0b%s levels=%s" % (
            r["trainer_id"], r["anchored_count"], r["anchored_present"],
            format(r["anchored_returned_bits"], "03b"), r["anchored_levels"]))
        if r["overflow_boxes_mask"]:
            print("  overflow boxes mask: 0x%04x" % r["overflow_boxes_mask"])
    print("Boxes 1-7 (Right):  ", out["boxes_right_1_7"])
    print("Boxes 8-14 (Left):  ", out["boxes_left_8_14"])


if __name__ == "__main__":
    main(sys.argv[1:])
