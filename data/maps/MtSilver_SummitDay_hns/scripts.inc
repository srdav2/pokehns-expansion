MtSilver_SummitDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_SummitDay_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MtSilver_SummitDay_OnFrame
	.byte 0

MtSilver_SummitDay_OnFrame::
	map_script_2 VAR_TEMP_MTSILVER_RESUME_BLIZZARD_SE, 0, MtSilver_SummitDay_Blizzard
	.2byte 0

MtSilver_SummitDay_Blizzard::
	playse SE_M_BLIZZARD
	setvar VAR_TEMP_MTSILVER_RESUME_BLIZZARD_SE, 1
	end

MtSilver_SummitDay_OnTransition:
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	end

MtSilver_SummitDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_NIGHT_HNS
	return

MtSilver_SummitDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_DAY_HNS
	return

MtSilver_SummitDay_EventScript_Red::
	lock
	faceplayer
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	closemessage
	goto_if_set FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_RedNotRetry
	goto_if_defeated TRAINER_RED_HNS, MtSilver_SummitDay_EventScript_GoAxis
	goto_if_defeated TRAINER_RED_POSTOBC_HNS, MtSilver_SummitDay_EventScript_GoAxis
MtSilver_SummitDay_EventScript_RedNotRetry::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, MtSilver_SummitDay_EventScript_RedStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, MtSilver_SummitDay_EventScript_RedPostOBC

MtSilver_SummitDay_EventScript_RedStandard::
	trainerbattle_no_intro TRAINER_RED_HNS, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedPostOBC::
	trainerbattle_no_intro TRAINER_RED_POSTOBC_HNS, MtSilver_SummitDay_Text_RedBeaten
	goto MtSilver_SummitDay_EventScript_RedOnDefeat

MtSilver_SummitDay_EventScript_RedOnDefeat::
	playse SE_M_BLIZZARD
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	msgbox MtSilver_SummitDay_Text_Red, MSGBOX_DEFAULT
	special GivePartyMonLandRibbon
	closemessage
	goto_if_unset FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_GoAxis
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_MTSILVER_RED
	removeobject LOCALID_MTSILVER_RED
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 180
	goto_if_set FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_RedSkipFinaleDialogue
	msgbox MtSilver_SummitDay_Text_Giratina, MSGBOX_DEFAULT
	msgbox MtSilver_SummitDay_Text_Arceus, MSGBOX_DEFAULT
MtSilver_SummitDay_EventScript_RedSkipFinaleDialogue::
	fadescreenspeed FADE_TO_BLACK, 24
	setflag FLAG_DEFEATED_RED
	setflag FLAG_END_NUZLOCKE
	clearflag FLAG_HIDE_MTSILVER_RED
	special GameClear
	waitstate
	releaseall
	end

MtSilver_SummitDay_EventScript_GoAxis::
	playse SE_M_BLIZZARD
	fadescreenspeed FADE_TO_BLACK, 8
	warp MAP_GIRATINA_AXIS_HNS, 10, 18
	waitstate
	end

MtSilver_SummitDay_Text_Red:
	.string ".........................\n"
	.string ".........................$"

MtSilver_SummitDay_Text_RedBeaten:
	.string "...!$"

MtSilver_SummitDay_Text_Giratina:
	.string "GIRATINA: You've seen it spun\n"
	.string "left. You've seen it spun right.\p"
	.string "Aren't they fun?$"

MtSilver_SummitDay_Text_Arceus:
	.string "ARCEUS: Enough. The world is\n"
	.string "not a top.$"
