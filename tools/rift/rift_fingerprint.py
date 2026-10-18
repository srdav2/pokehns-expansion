#!/usr/bin/env python3
"""Rift compatibility fingerprint for Pokémon Right / Pokémon Left.

Pokémon cross between the two games byte-for-byte, so both repos must keep the same
numbering for species, moves, items, abilities and balls, and the same stored-Pokémon
and PC layouts. This script records those facts for one repo and compares two records.
Identical copy in both repos: tools/rift/rift_fingerprint.py.

  python3 tools/rift/rift_fingerprint.py --game right --out docs/rift/fingerprint_right.json
  python3 tools/rift/rift_fingerprint.py --compare docs/rift/fingerprint_right.json docs/rift/fingerprint_left.json

Run it whenever either repo upgrades pokeemerald-expansion or touches pokemon.h,
pokemon_storage_system.h, or the constants headers. Commit both JSON files to BOTH repos.
"""
import argparse
import hashlib
import json
import os
import re
import sys

# Differences we know about and accept (see docs/rift/RIFT_CONTRACT.md §6).
# Items never cross (held items are stripped at the crossing), so item differences are reported as info only.
INFO_ONLY_TABLES = {"items"}
ALLOWED = {
    "abilities": {"only_right_ok": True},   # Legends Z-A Mega abilities: only exist mid-battle, never in a box
    "balls": {"only_left_ok": {"BALL_GS"}},  # clamped to BALL_POKE at the crossing (RIFT_LAST_SHARED_BALL)
}
# Sentinels / markers that are not real data values.
IGNORE_NAME = re.compile(r"(RANDOM|CUSTOM_START|CUSTOM_END|_COUNT$|^ITEM_USE_|^MOVE_DEFAULT$|^MOVE_UNAVAILABLE$)")


def strip_comments(s):
    s = re.sub(r"//.*", "", s)
    return re.sub(r"/\*.*?\*/", "", s, flags=re.S)


def parse_constants(path, prefix):
    """Values for PREFIX_* names from enums and #defines (handles aliases and simple expressions)."""
    s = strip_comments(open(path, encoding="utf-8", errors="replace").read())
    raw = {}
    for m in re.finditer(r"#define\s+(%s[A-Z0-9_]*)\s+([^\n]+)" % prefix, s):
        raw[m.group(1)] = m.group(2).strip()
    order = []
    for m in re.finditer(r"enum[^{;]*\{(.*?)\}", s, flags=re.S):
        body = "\n".join(l for l in m.group(1).split("\n") if not l.strip().startswith("#"))
        for item in body.split(","):
            item = item.strip()
            if not item:
                continue
            if "=" in item:
                name, expr = [x.strip() for x in item.split("=", 1)]
            else:
                name, expr = item, None
            if re.match(r"^[A-Z_][A-Z0-9_]*$", name):
                order.append((name, expr))
    vals = {}

    def ev(expr, depth=0):
        if expr is None or depth > 8:
            return None
        expr = expr.strip()
        if re.match(r"^\d+$", expr):
            return int(expr)
        if re.match(r"^0x[0-9a-fA-F]+$", expr):
            return int(expr, 16)
        def sub(m):
            n = m.group(0)
            if n in vals and vals[n] is not None:
                return str(vals[n])
            if n in raw:
                v = ev(raw[n], depth + 1)
                return str(v) if v is not None else n
            return n
        e = re.sub(r"\b[A-Z_][A-Z0-9_]*\b", sub, expr)
        if re.search(r"[A-Za-z_]", e):
            return None
        try:
            return int(eval(e, {"__builtins__": {}}))
        except Exception:
            return None

    cur = -1
    for name, expr in order:
        if expr is not None:
            v = ev(expr)
            cur = v if v is not None else None
        else:
            cur = cur + 1 if cur is not None else None
        vals[name] = cur
    for name, expr in raw.items():
        if name not in vals:
            vals[name] = ev(expr)
    return {k: v for k, v in vals.items() if k.startswith(prefix) and v is not None}


def struct_text(path, name):
    s = strip_comments(open(path, encoding="utf-8", errors="replace").read())
    m = re.search(r"struct\s+%s\s*\{(.*?)\n\};" % re.escape(name), s, flags=re.S)
    if not m:
        return None
    t = re.sub(r"\s+", " ", m.group(1)).strip()
    t = re.sub(r"\b(enum \w+|u16|u32|u8)\s+(species|heldItem)\s*:", r"T \2:", t)  # enum-typed bitfields == u16
    return t


def sha(path):
    if not os.path.exists(path):
        return None
    return hashlib.sha256(open(path, "rb").read()).hexdigest()


def fingerprint(root, game):
    inc = os.path.join(root, "include")
    c = os.path.join(inc, "constants")
    fp = {
        "game": game,
        "species": parse_constants(os.path.join(c, "species.h"), "SPECIES_"),
        "moves": parse_constants(os.path.join(c, "moves.h"), "MOVE_"),
        "items": parse_constants(os.path.join(c, "items.h"), "ITEM_"),
        "abilities": parse_constants(os.path.join(c, "abilities.h"), "ABILITY_"),
        "balls": parse_constants(os.path.join(c, "pokeball.h"), "BALL_"),
        "structs": {n: struct_text(os.path.join(inc, "pokemon.h"), n) for n in
                    ["BoxPokemon", "PokemonSubstruct0", "PokemonSubstruct1", "PokemonSubstruct2",
                     "PokemonSubstruct3", "Pokemon"]},
        "storage_struct": struct_text(os.path.join(inc, "pokemon_storage_system.h"), "PokemonStorage"),
        "storage_constants": parse_constants(os.path.join(inc, "pokemon_storage_system.h"), ""),
        "contract_files": {
            "docs/rift/rift_contract.h": sha(os.path.join(root, "docs/rift/rift_contract.h")),
            "include/rift_contract.h": sha(os.path.join(inc, "rift_contract.h")),
            "docs/rift/rift_shared.h": sha(os.path.join(root, "docs/rift/rift_shared.h")),
            "include/rift_shared.h": sha(os.path.join(inc, "rift_shared.h")),
            "docs/rift/rift_shared.c": sha(os.path.join(root, "docs/rift/rift_shared.c")),
            "src/rift_shared.c": sha(os.path.join(root, "src/rift_shared.c")),
        },
    }
    fp["storage_constants"] = {k: v for k, v in fp["storage_constants"].items()
                               if k in ("TOTAL_BOXES_COUNT", "IN_BOX_ROWS", "IN_BOX_COLUMNS",
                                        "BOX_NAME_LENGTH", "MAX_FUSION_STORAGE")}
    return fp


def compare(a, b):
    """Returns a list of problems. a/b are fingerprints; their 'game' fields say which is which."""
    right, left = (a, b) if a["game"] == "right" else (b, a)
    problems, info = [], []
    for table in ["species", "moves", "items", "abilities", "balls"]:
        r = {k: v for k, v in right[table].items() if not IGNORE_NAME.search(k) and v < 0xFFFF}
        l = {k: v for k, v in left[table].items() if not IGNORE_NAME.search(k) and v < 0xFFFF}
        if table in INFO_ONLY_TABLES:
            renum = sorted(k for k in set(r) & set(l) if r[k] != l[k])
            info.append("%s: %d shared, %d renumbered %s, %d only in Right, %d only in Left (never cross: held items are stripped)"
                        % (table, len(set(r) & set(l)), len(renum), renum[:5], len(set(r) - set(l)), len(set(l) - set(r))))
            continue
        allow = ALLOWED.get(table, {})
        for k in sorted(set(r) & set(l)):
            if r[k] != l[k] and k not in allow.get("renumbered_ok", set()):
                problems.append("%s: %s is %s in Right but %s in Left" % (table, k, r[k], l[k]))
        only_r, only_l = set(r) - set(l), set(l) - set(r)
        if only_r and not allow.get("only_right_ok"):
            problems.append("%s only in Right: %s" % (table, ", ".join(sorted(only_r)[:10])))
        if only_l:
            bad = sorted(k for k in only_l if k not in allow.get("only_left_ok", set()))
            if bad:
                problems.append("%s only in Left (numbering clash risk): %s" % (table, ", ".join(bad[:10])))
    for n, t in right["structs"].items():
        if t != left["structs"].get(n):
            problems.append("struct %s differs" % n)
    if right["storage_struct"] != left["storage_struct"]:
        problems.append("struct PokemonStorage differs")
    if right["storage_constants"] != left["storage_constants"]:
        problems.append("storage constants differ: %s vs %s" % (right["storage_constants"], left["storage_constants"]))
    for fp in (right, left):
        cf = fp["contract_files"]
        for doc, live in [("docs/rift/rift_contract.h", "include/rift_contract.h"),
                          ("docs/rift/rift_shared.h", "include/rift_shared.h"),
                          ("docs/rift/rift_shared.c", "src/rift_shared.c")]:
            if cf.get(live) and cf.get(live) != cf.get(doc):
                problems.append("%s: %s is not an exact copy of %s" % (fp["game"], live, doc))
    for doc in ["docs/rift/rift_contract.h", "docs/rift/rift_shared.h", "docs/rift/rift_shared.c"]:
        if right["contract_files"].get(doc) != left["contract_files"].get(doc):
            problems.append("%s differs between the repos" % doc)
    return problems, info


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game", choices=["right", "left"])
    ap.add_argument("--root", default=".")
    ap.add_argument("--out")
    ap.add_argument("--compare", nargs=2, metavar=("A_JSON", "B_JSON"))
    args = ap.parse_args()
    if args.compare:
        a, b = [json.load(open(p)) for p in args.compare]
        problems, info = compare(a, b)
        for i in info:
            print("info:", i)
        for p in problems:
            print("PROBLEM:", p)
        print("Rift compatibility: %s" % ("OK" if not problems else "%d problem(s)" % len(problems)))
        sys.exit(1 if problems else 0)
    if not args.game:
        ap.error("--game is required unless --compare is used")
    fp = fingerprint(args.root, args.game)
    text = json.dumps(fp, indent=1, sort_keys=True)
    if args.out:
        open(args.out, "w").write(text + "\n")
    else:
        print(text)


if __name__ == "__main__":
    main()
