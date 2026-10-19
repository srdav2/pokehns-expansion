GiratinaAxis_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GiratinaAxis_OnFrame
	.byte 0

GiratinaAxis_OnFrame::
	map_script_2 VAR_TEMP_0, 0, GiratinaAxis_EventScript_CheckScene
	.2byte 0

GiratinaAxis_EventScript_CheckScene::
	lockall
	setvar VAR_TEMP_0, 1
	specialvar VAR_RESULT, Rift_IsCurrentGameFinished
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_AlreadyFinished
	specialvar VAR_RESULT, IsRiftSecondGame
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_SecondGame
	goto GiratinaAxis_EventScript_FirstGame
	end

GiratinaAxis_EventScript_AlreadyFinished::
	releaseall
	end

GiratinaAxis_EventScript_FirstGame::
	delay 40
	playmoncry SPECIES_GIRATINA_ORIGIN, CRY_MODE_ENCOUNTER
	waitmoncry
	fadescreenspeed FADE_TO_WHITE, 4
	delay 30
	fadescreenspeed FADE_FROM_WHITE, 4
	msgbox GiratinaAxis_Text_GiratinaFirst, MSGBOX_DEFAULT
	msgbox GiratinaAxis_Text_ArceusOffer, MSGBOX_DEFAULT
	specialvar VAR_RESULT, Rift_HasFusionBlocker
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_ShowBlockers
	specialvar VAR_RESULT, Rift_HasOverflowBlocker
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_ShowBlockers
	goto GiratinaAxis_EventScript_AskToCross
	end

GiratinaAxis_EventScript_ShowBlockers::
	specialvar VAR_RESULT, Rift_HasFusionBlocker
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_ShowFusionBlocker
GiratinaAxis_EventScript_CheckOverflowBlocker::
	specialvar VAR_RESULT, Rift_HasOverflowBlocker
	goto_if_eq VAR_RESULT, TRUE, GiratinaAxis_EventScript_ShowOverflowBlocker
	releaseall
	end

GiratinaAxis_EventScript_ShowFusionBlocker::
	msgbox GiratinaAxis_Text_T5, MSGBOX_DEFAULT
	goto GiratinaAxis_EventScript_CheckOverflowBlocker

GiratinaAxis_EventScript_ShowOverflowBlocker::
	msgbox GiratinaAxis_Text_T6, MSGBOX_DEFAULT
	releaseall
	end

GiratinaAxis_EventScript_AskToCross::
	msgbox GiratinaAxis_Text_T7, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GiratinaAxis_EventScript_DeclineCrossing
	special Rift_ResetCrossingState
	setvar VAR_TEMP_1, 0
GiratinaAxis_EventScript_PickAnchor::
	copyvar VAR_0x8005, VAR_TEMP_1
	specialvar VAR_RESULT, Rift_CanPickAnotherAnchor
	goto_if_eq VAR_RESULT, FALSE, GiratinaAxis_EventScript_PrepareCrossing
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, GiratinaAxis_EventScript_PrepareCrossing
	copyvar VAR_0x8005, VAR_TEMP_1
	specialvar VAR_RESULT, Rift_StoreSelectedAnchor
	goto_if_eq VAR_RESULT, FALSE, GiratinaAxis_EventScript_InvalidAnchor
	addvar VAR_TEMP_1, 1
	goto GiratinaAxis_EventScript_PickAnchor
	end

GiratinaAxis_EventScript_InvalidAnchor::
	msgbox GiratinaAxis_Text_InvalidAnchor, MSGBOX_DEFAULT
	goto GiratinaAxis_EventScript_PickAnchor

GiratinaAxis_EventScript_PrepareCrossing::
	specialvar VAR_RESULT, Rift_PrepareCrossingForScript
	msgbox GiratinaAxis_Text_T8, MSGBOX_DEFAULT
	goto_if_eq VAR_RESULT, FALSE, GiratinaAxis_EventScript_SaveFirstFinish
	msgbox GiratinaAxis_Text_T8Lost, MSGBOX_DEFAULT

GiratinaAxis_EventScript_SaveFirstFinish::
	special Rift_MarkFirstFinish
	special SaveGame
	waitstate
	msgbox GiratinaAxis_Text_T9, MSGBOX_DEFAULT
	msgbox GiratinaAxis_Text_FirstFinish, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special Rift_StartFirstFinishCredits
	waitstate
	releaseall
	end

GiratinaAxis_EventScript_DeclineCrossing::
	msgbox GiratinaAxis_Text_CrossingDeclined, MSGBOX_DEFAULT
	releaseall
	end

GiratinaAxis_EventScript_SecondGame::
	delay 40
	playmoncry SPECIES_GIRATINA_ORIGIN, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox GiratinaAxis_Text_Giratina, MSGBOX_DEFAULT
	goto_if_set FLAG_GILDED_RIFT_ARCEUS_BATTLE_DONE, GiratinaAxis_EventScript_SecondFinish
	goto_if_set FLAG_GILDED_RIFT_GIRATINA_BATTLE_DONE, GiratinaAxis_EventScript_SecondGameArceus
	closemessage
	setwildbattle SPECIES_GIRATINA_ORIGIN, 90, ITEM_GRISEOUS_CORE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, GiratinaAxis_EventScript_GiratinaBattleDone
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GiratinaAxis_EventScript_GiratinaBattleDone
	goto GiratinaAxis_EventScript_Retry
	end

GiratinaAxis_EventScript_GiratinaBattleDone::
	setflag FLAG_GILDED_RIFT_GIRATINA_BATTLE_DONE
	special SaveGame
	waitstate
GiratinaAxis_EventScript_SecondGameArceus::
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox GiratinaAxis_Text_Arceus, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_ARCEUS, 90
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, GiratinaAxis_EventScript_ArceusBattleDone
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GiratinaAxis_EventScript_ArceusBattleDone
	goto GiratinaAxis_EventScript_Retry
	end

GiratinaAxis_EventScript_ArceusBattleDone::
	setflag FLAG_GILDED_RIFT_ARCEUS_BATTLE_DONE
GiratinaAxis_EventScript_SecondFinish::
	special Rift_MarkSecondFinishForScript
	special SaveGame
	waitstate
	msgbox GiratinaAxis_Text_ArceusCentre, MSGBOX_DEFAULT
	closemessage
	fadescreenspeed FADE_TO_WHITE, 4
	delay 30
	fadescreenspeed FADE_FROM_WHITE, 4
	msgbox GiratinaAxis_Text_ArceusQuiet, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setvar VAR_GILDED_FINALE, 1
	warp MAP_GOLDENROD_CITY_TV_ROOM_HNS, 3, 5
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

GiratinaAxis_Text_GiratinaFirst:
	.string "GIRATINA: Spun right. Next time,\n"
	.string "the other way.$"

GiratinaAxis_Text_ArceusOffer:
	.string "ARCEUS: I can carry three of your\n"
	.string "Pokémon across the Rift.$"

GiratinaAxis_Text_T5:
	.string "A fused Pokémon is holding its\n"
	.string "partner. Separate them first.$"

GiratinaAxis_Text_T6:
	.string "Some Pokémon are still in the\n"
	.string "other world's boxes.\p"
	.string "Move them into your own boxes\n"
	.string "before crossing.$"

GiratinaAxis_Text_T7:
	.string "Nothing you carry can cross the\n"
	.string "Rift. Held items go to your BAG.\p"
	.string "Your party and the DAY CARE stay\n"
	.string "here. Only Pokémon in your PC\p"
	.string "boxes will cross, and the three\n"
	.string "you choose will start anew.$"

GiratinaAxis_Text_T8:
	.string "{STR_VAR_1} Pokémon will cross.\n"
	.string "{STR_VAR_2} held items went to the BAG.$"

GiratinaAxis_Text_T8Lost:
	.string "{STR_VAR_3} items didn't fit and\n"
	.string "were left behind.$"

GiratinaAxis_Text_T9:
	.string "Your journey continues in the\n"
	.string "other world.\p"
	.string "Copy this save file to the other\n"
	.string "game and choose ARRIVE THROUGH\p"
	.string "THE RIFT on its title screen.\n"
	.string "Keep a backup copy, too.$"

GiratinaAxis_Text_FirstFinish:
	.string "GIRATINA: Spin it the other way.\n"
	.string "I want to see their faces.$"

GiratinaAxis_Text_InvalidAnchor:
	.string "That Pokémon cannot cross the\n"
	.string "Rift. Choose another.$"

GiratinaAxis_Text_CrossingDeclined:
	.string "The Rift will wait. Your journey\n"
	.string "is yours to choose.$"

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
