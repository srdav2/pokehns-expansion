GoldenrodCity_DepartmentStore_7F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_DepartmentStore_7F_OnTransition
	.byte 0

GoldenrodCity_DepartmentStore_7F_OnTransition:
	call_if_set FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetDay
	end

GoldenrodCity_DepartmentStore_7F_EventScript_SetNight::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT_HNS
	return

GoldenrodCity_DepartmentStore_7F_EventScript_SetDay::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7F_HNS
	return


GoldenrodDeptStore7_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Nerd::
	lock
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdOhWow, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROOF_NERD, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_ROOF_NERD
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROOF_NERD, DIR_SOUTH
	release
	end

GoldenrodDeptStore7_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Bugcatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_GildedBallShow::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_GildedBallShow, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodDeptStore7_EventScript_GildedBallShowYes
	setflag FLAG_GILDED_PRESSURE_PROMPT_BALL_SHOW
	msgbox GoldenrodDeptStore_Text_GildedBallShowNo, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_GildedBallShowYes::
	addvar VAR_PRESSURE_POINTS, 1
	setflag FLAG_GILDED_PRESSURE_PROMPT_BALL_SHOW
	msgbox GoldenrodDeptStore_Text_GildedBallShowYes, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_GildedBuckshot::
	trainerbattle_single TRAINER_COLONEL_BUCKSHOT_BALL_SHOW_HNS, GoldenrodDeptStore_Text_BuckshotSeen, GoldenrodDeptStore_Text_BuckshotBeaten
	msgbox GoldenrodDeptStore_Text_BuckshotAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodDeptStore_Text_RoofPokefanF:
    .string "Whew, I'm tired.\p"
    .string "I sometimes come up to the rooftop\n"
    .string "to take a break from shopping.$"

GoldenrodDeptStore_Text_RoofFisher:
    .string "Pardon? Who says an adult can't get\n"
    .string "into this?\p"
    .string "I'm going to be back every day to\n"
    .string "collect all the dolls!$"

GoldenrodDeptStore_Text_RoofTwin:
    .string "They have bargain sales here every\n"
    .string "so often.$"

GoldenrodDeptStore_Text_RoofSuperNerdOhWow:
    .string "Oh, wow!$"

GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe:
    .string "Will you quit bothering me?$"

GoldenrodDeptStore_Text_RoofPokefanM:
    .string "There's something I really want,\n"
    .string "but I don't have the necessary cash…\p"
    .string "Maybe I'll sell off the BERRIES I've\n"
    .string "collected…$"

GoldenrodDeptStore_Text_RoofTeacher:
    .string "Oh, everything is so cheap!\p"
    .string "I bought so much, my PACK's crammed!$"

GoldenrodDeptStore_Text_RoofBugCatcher:
    .string "My POKéMON always get paralyzed or\n"
    .string "poisoned when the chips are down…\p"
    .string "So I came to buy some FULL HEAL.\p"
    .string "I wonder if there's any left?$"

GoldenrodDeptStore_Text_GildedBallShow:
	.string "The N.R.A. Ball Show!\n"
	.string "Want to see our free display?$"

GoldenrodDeptStore_Text_GildedBallShowYes:
	.string "Catch-and-release, Colonel!\n"
	.string "No, just release.$"

GoldenrodDeptStore_Text_GildedBallShowNo:
	.string "No display? Your choice.\n"
	.string "No waiting period.$"

GoldenrodDeptStore_Text_BuckshotSeen:
	.string "A well-regulated PARTY is\n"
	.string "necessary for freedom!$"

GoldenrodDeptStore_Text_BuckshotBeaten:
	.string "This is why we need MORE\n"
	.string "POKé BALLS!$"

GoldenrodDeptStore_Text_BuckshotAfter:
	.string "The Ball Show continues!\n"
	.string "Catch-and-release!$"
