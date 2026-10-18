RuinsOfAlph_FactCheck_hns_MapScripts::
	.byte 0

Gilded_FactCheck_Unown1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_UNOWN, CRY_MODE_NORMAL
	msgbox Gilded_FactCheck_Text1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Gilded_FactCheck_Unown2::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_UNOWN, CRY_MODE_NORMAL
	msgbox Gilded_FactCheck_Text2, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Gilded_FactCheck_Unown3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_UNOWN, CRY_MODE_NORMAL
	msgbox Gilded_FactCheck_Text3, MSGBOX_DEFAULT
	waitmoncry
	setvar VAR_0x8004, 4
	special GildedQuestBitTest
	goto_if_eq VAR_RESULT, TRUE, Gilded_FactCheck_Done
	setvar VAR_0x8004, 4
	special GildedQuestBitSet
	msgbox Gilded_FactCheck_Reward, MSGBOX_DEFAULT
	giveitem ITEM_TM_GRASS_KNOT
Gilded_FactCheck_Done::
	release
	end

Gilded_FactCheck_Sign::
	msgbox Gilded_FactCheck_SignText, MSGBOX_SIGN
	end

Gilded_FactCheck_Exit::
	lockall
	msgbox Gilded_FactCheck_ExitText, MSGBOX_DEFAULT
	warp MAP_RUINS_OF_ALPH_OUTSIDE_HNS, 22, 22
	waitstate
	releaseall
	end

Gilded_FactCheck_Text1:
	.string "U-N-O-W-N: FACT CHECK.\n"
	.string "'THE WALLS ARE MY OWN.' FALSE.$"

Gilded_FactCheck_Text2:
	.string "U-N-O-W-N: FACT CHECK.\n"
	.string "'WE'RE ALL IN ONE ECHO.' FALSE.$"

Gilded_FactCheck_Text3:
	.string "U-N-O-W-N: RULING: YOU HAVE\n"
	.string "BEEN ONLINE TOO LONG.\p"
	.string "TOUCH GRASS.\n"
	.string "TOUCH GRASS.$"

Gilded_FactCheck_Reward:
	.string "The UNOWN offers you a TM.\n"
	.string "It's GRASS KNOT. Seriously.$"

Gilded_FactCheck_SignText:
	.string "FACT-CHECK CHAMBER\n"
	.string "'Verified by Unown.'$"

Gilded_FactCheck_ExitText:
	.string "The glyphs fade. Outside, the\n"
	.string "grass is waiting.$"

Gilded_FactCheck_Enter::
	lock
	faceplayer
	goto_if_unset FLAG_COMPLETED_KABUTO_PUZZLE, Gilded_FactCheck_NotYet
	msgbox Gilded_FactCheck_AskText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_FactCheck_Decline
	warp MAP_RUINS_OF_ALPH_FACT_CHECK_HNS, 10, 13
	waitstate
	release
	end

Gilded_FactCheck_NotYet::
	msgbox Gilded_FactCheck_NotYetText, MSGBOX_DEFAULT
	release
	end

Gilded_FactCheck_Decline::
	msgbox Gilded_FactCheck_DeclineText, MSGBOX_DEFAULT
	release
	end

Gilded_FactCheck_NotYetText:
	.string "FACT-CHECKER: The Unown only\n"
	.string "speak to those who solved a\p"
	.string "puzzle. Do the KABUTO one.\n"
	.string "Then they'll fact-check you.$"

Gilded_FactCheck_AskText:
	.string "FACT-CHECKER: You solved the\n"
	.string "puzzle. Enter the chamber?$"

Gilded_FactCheck_DeclineText:
	.string "FACT-CHECKER: Fair. Facts\n"
	.string "are scary.$"
