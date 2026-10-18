GiratinaAxis_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GiratinaAxis_OnFrame
	.byte 0

GiratinaAxis_OnFrame::
	map_script_2 VAR_TEMP_0, 0, GiratinaAxis_EventScript_Scene
	.2byte 0

GiratinaAxis_EventScript_Scene::
	lockall
	setvar VAR_TEMP_0, 1
	delay 40
	playmoncry SPECIES_GIRATINA_ORIGIN, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox GiratinaAxis_Text_Giratina, MSGBOX_DEFAULT
	msgbox GiratinaAxis_Text_Arceus, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_GIRATINA_ORIGIN, 90, ITEM_GRISEOUS_CORE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GiratinaAxis_EventScript_Retry
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GiratinaAxis_EventScript_Retry
	msgbox GiratinaAxis_Text_ArceusCentre, MSGBOX_DEFAULT
	closemessage
	fadescreenspeed FADE_TO_WHITE, 4
	delay 30
	fadescreenspeed FADE_FROM_WHITE, 4
	msgbox GiratinaAxis_Text_ArceusQuiet, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	msgbox GiratinaAxis_Text_Crossfire, MSGBOX_DEFAULT
	goto_if_eq VAR_PRESSURE_POINTS, 0, GiratinaAxis_EventScript_EpilogueNone
	goto_if_le VAR_PRESSURE_POINTS, 5, GiratinaAxis_EventScript_EpilogueSome
	msgbox GiratinaAxis_Text_EpilogueMany, MSGBOX_DEFAULT
	goto GiratinaAxis_EventScript_Finish

GiratinaAxis_EventScript_EpilogueNone::
	msgbox GiratinaAxis_Text_EpilogueNone, MSGBOX_DEFAULT
	goto GiratinaAxis_EventScript_Finish

GiratinaAxis_EventScript_EpilogueSome::
	msgbox GiratinaAxis_Text_EpilogueSome, MSGBOX_DEFAULT
	goto GiratinaAxis_EventScript_Finish

GiratinaAxis_EventScript_Finish::
	msgbox GiratinaAxis_Text_PostCredits, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DEFEATED_RED
	setflag FLAG_END_NUZLOCKE
	special GameClear
	waitstate
	releaseall
	end

GiratinaAxis_EventScript_Retry::
	msgbox GiratinaAxis_Text_Retry, MSGBOX_DEFAULT
	closemessage
	warp MAP_MT_SILVER_SUMMIT_DAY_HNS, 10, 9
	waitstate
	releaseall
	end

GiratinaAxis_Text_Giratina:
	.string "GIRATINA: You've seen it spun\n"
	.string "left. You've seen it spun right.\p"
	.string "Aren't they fun?$"

GiratinaAxis_Text_Arceus:
	.string "ARCEUS: Enough. The world is\n"
	.string "not a top.$"

GiratinaAxis_Text_ArceusCentre:
	.string "ARCEUS: Left was loud.\n"
	.string "Right was loud.$"

GiratinaAxis_Text_ArceusQuiet:
	.string "The middle is quiet, and quiet\n"
	.string "is where people actually live.$"

GiratinaAxis_Text_Crossfire:
	.string "Later, on CROSSFIRE:\n"
	.string "BLEAK: You're shouting!\p"
	.string "PELL: YOU'RE shouting!\n"
	.string "You switch the TV off. Outside\l"
	.string "your party is running through\l"
	.string "the grass on ROUTE 29.$"

GiratinaAxis_Text_EpilogueNone:
	.string "You said no to everything.\n"
	.string "Exhausting. Correct.$"

GiratinaAxis_Text_EpilogueSome:
	.string "Go outside. Touch grass.\n"
	.string "ROUTE 29 has excellent grass.$"

GiratinaAxis_Text_EpilogueMany:
	.string "ARCEUS: You agreed to a great\n"
	.string "many things.\p"
	.string "Read the fine print next time.$"

GiratinaAxis_Text_PostCredits:
	.string "GIRATINA: …I wonder what it\n"
	.string "looks like spun UP.$"

GiratinaAxis_Text_Retry:
	.string "The Axis pulls you back.\n"
	.string "GIRATINA is not finished.$"
