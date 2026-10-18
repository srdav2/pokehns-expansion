CeruleanCity_CryptoMine_hns_MapScripts::
	.byte 0

CeruleanCity_CryptoMine_EventScript_Exit::
	lock
	faceplayer
	msgbox CeruleanCity_CryptoMine_Text_Leave, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeruleanCity_CryptoMine_EventScript_Stay
	closemessage
	warp MAP_ROUTE10_POWER_PLANT_ENTRANCE_HNS, 9, 21
	waitstate
	end

CeruleanCity_CryptoMine_EventScript_Stay::
	closemessage
	release
	end

CeruleanCity_CryptoMine_EventScript_Thorne::
	msgbox CeruleanCity_CryptoMine_Text_Thorne, MSGBOX_NPC
	end

CeruleanCity_CryptoMine_EventScript_Bro1::
	trainerbattle_single TRAINER_CRYPTO_BRO_1_HNS, CeruleanCity_CryptoMine_Text_Bro1Seen, CeruleanCity_CryptoMine_Text_Bro1Beaten
	msgbox CeruleanCity_CryptoMine_Text_Bro1After, MSGBOX_AUTOCLOSE
	end

CeruleanCity_CryptoMine_EventScript_Bro2::
	trainerbattle_single TRAINER_CRYPTO_BRO_2_HNS, CeruleanCity_CryptoMine_Text_Bro2Seen, CeruleanCity_CryptoMine_Text_Bro2Beaten
	msgbox CeruleanCity_CryptoMine_Text_Bro2After, MSGBOX_AUTOCLOSE
	end

CeruleanCity_CryptoMine_EventScript_Grindwells::
	trainerbattle_single TRAINER_GRINDWELL_BROS_CRYPTO_MINE_HNS, CeruleanCity_CryptoMine_Text_GrindSeen, CeruleanCity_CryptoMine_Text_GrindBeaten
	msgbox CeruleanCity_CryptoMine_Text_GrindAfter, MSGBOX_AUTOCLOSE
	end

CeruleanCity_CryptoMine_EventScript_RigSign::
	msgbox CeruleanCity_CryptoMine_Text_Rig, MSGBOX_SIGN
	end

CeruleanCity_CryptoMine_EventScript_RigSign2::
	msgbox CeruleanCity_CryptoMine_Text_Rig2, MSGBOX_SIGN
	end

CeruleanCity_CryptoMine_Text_Leave:
	.string "Leave the $GAUDY mine?$"

CeruleanCity_CryptoMine_Text_Thorne:
	.string "THORNE: We burned COAL to mine\n"
	.string "EQUI-COIN.\p"
	.string "These idiots hooked a meme-coin\n"
	.string "rig to a whole POWER PLANT.\p"
	.string "Amateurs.$"

CeruleanCity_CryptoMine_Text_Bro1Seen:
	.string "Bro! The rig is mining $GAUDY!\n"
	.string "Do not touch the rig!$"

CeruleanCity_CryptoMine_Text_Bro1Beaten:
	.string "Down bad. Down very bad.$"

CeruleanCity_CryptoMine_Text_Bro1After:
	.string "It's not a loss until I sell.$"

CeruleanCity_CryptoMine_Text_Bro2Seen:
	.string "Diamond hands, bro!\n"
	.string "Diamond hands!$"

CeruleanCity_CryptoMine_Text_Bro2Beaten:
	.string "My hands are just regular hands.$"

CeruleanCity_CryptoMine_Text_Bro2After:
	.string "We're still early. Probably.$"

CeruleanCity_CryptoMine_Text_GrindSeen:
	.string "CHAD: You took the PART back.\n"
	.string "BRAD: Rude. We're doing a thing.$"

CeruleanCity_CryptoMine_Text_GrindBeaten:
	.string "CHAD: $GAUDY is down 98%.\n"
	.string "BRAD: That's just the dip.$"

CeruleanCity_CryptoMine_Text_GrindAfter:
	.string "CHAD: It's the whole coin, bro.\p"
	.string "BRAD: The PART is yours. We got\n"
	.string "a better power source anyway.$"

CeruleanCity_CryptoMine_Text_Rig:
	.string "A mining rig. The screen reads\n"
	.string "$GAUDY: -98%.$"

CeruleanCity_CryptoMine_Text_Rig2:
	.string "A tower of fans wired to the\n"
	.string "POWER PLANT's grid.$"
