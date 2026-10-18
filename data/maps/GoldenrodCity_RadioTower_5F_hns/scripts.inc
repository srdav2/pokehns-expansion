GoldenrodCity_RadioTower_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_5F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_5F_OnLoad::
	call_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_5F_MapScript_HidePetrel
	end

GoldenrodCity_RadioTower_5F_MapScript_HidePetrel::
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	return


@=======[OFFICE]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	lock
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_5F_EventScript_Director
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_DIRECTOR_OFFICE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	addobject LOCALID_PETREL_OFFICE
	applymovement LOCALID_PETREL_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BARRY_BLASTER_MAHOGANY_HNS, GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setvar VAR_GOLDENROD_CITY_STATE, 7
	clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth::
	end

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Director::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Text_FakeDirector1:
	.string "Y-you! You came to rescue me?$"

GoldenrodCity_RadioTower_5F_Text_FakeDirector2:
	.string "Everything you've heard is fake\n"
	.string "news. Except me. Trust me!\p"
	.string "I'm BARRY BLASTER, the voice of\n"
	.string "RAGE RADIO!\p"
	.string "Want to know where the real\n"
	.string "DIRECTOR is? Beat me first!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin:
	.string "All right! The real DIRECTOR is\n"
	.string "in the UNDERGROUND WAREHOUSE!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter:
	.string "The President stashed the DIRECTOR\n"
	.string "at the far end of the UNDERGROUND.\p"
	.string "Here, take the BASEMENT KEY.\n"
	.string "You might make good radio yet!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2:
	.string "The real DIRECTOR is at the far\n"
	.string "end of the UNDERGROUND.\p"
	.string "Use the BASEMENT KEY to get into\n"
	.string "the UNDERGROUND WAREHOUSE.$"

@=======[STUDIO]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single TRAINER_ARIANA_2_HNS GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_5F_EventScript_Archer::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRESIDENT_REX_GAUDY_RADIO_TOWER_HNS, GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossAfter, MSGBOX_DEFAULT
	delay 55
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	playse SE_EXIT
	setvar VAR_GOLDENROD_CITY_STATE, 10
	removeobject LOCALID_GOLDENROD_ARCHER
	removeobject LOCALID_GOLDENROD_ARIANA
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_PETREL_OFFICE
	addobject LOCALID_DIRECTOR_STUDIO
	playbgm MUS_HG_GOLDENROD, TRUE
	delay 120
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_WingTop
	goto_if_eq VAR_FACING, DIR_WEST, GoldenrodCity_RadioTower_5F_EventScript_WingMid
	goto_if_eq VAR_FACING, DIR_NORTH, GoldenrodCity_RadioTower_5F_EventScript_WingBot
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_WingTop::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveTop
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingMid::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveMid
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingBot::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveBot
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing::
	giveitem ITEM_SILVER_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing::
	giveitem ITEM_RAINBOW_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_Fakeout::
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_WEST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorLegendary, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_SOUTH
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorFakeout, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave2
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	removeobject LOCALID_DIRECTOR_STUDIO
	setvar VAR_MAHOGANY_TOWN_STATE, 17
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Trigger_NPCS::
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	setvar VAR_GOLDENROD_CITY_STATE, 11
	end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveTop:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end


GoldenrodCity_RadioTower_5F_Movement_LeaveMid:
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveBot:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave1:
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen:
	.string "Remember me from the HIDEOUT in\n"
	.string "MAHOGANY TOWN?\p"
	.string "My boss scolded me but I'm stronger.\p"
	.string "I lost then, but I won't this time.$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten:
	.string "This can't be happening!\p"
	.string "I fought hard, but I still lost…\p"
	.string "I'm so sorry GIOVANNI…$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After:
	.string "{PLAYER}, isn't it?\p"
	.string "A brat like you won't appreciate\n"
	.string "the magnificence of TEAM MEGA.\p"
	.string "That's too bad. I really admire\n"
	.string "your power.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen:
	.string "PRESIDENT GAUDY: You're too late!\p"
	.string "I alone can evolve your Magikarp!\p"
	.string "This is the greatest tower in\n"
	.string "history. My name is on it!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten:
	.string "I won. I won by a lot.\p"
	.string "That was a total win for me.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossAfter:
	.string "I'm disbanding TEAM MEGA to start\n"
	.string "a new, better party!\p"
	.string "This is the greatest exit in\n"
	.string "Radio Tower history!$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanks:
	.string "DIRECTOR: {PLAYER}, thank you!\p"
	.string "Your courageous actions have saved\n"
	.string "POKéMON nationwide.\p"
	.string "I know it's not much, but please\n"
	.string "take this.$"

GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation:
	.string "There used to be a tower right here\n"
	.string "in GOLDENROD CITY.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our RADIO\n"
	.string "TOWER.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of POKéMON\n"
	.string "lived in GOLDENROD in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "TIN TOWER in ECRUTEAK CITY…\p"
	.string "OK, I better go to my OFFICE.$"

GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation:
	.string "There used to be a tower right here\n"
	.string "in GOLDENROD CITY.\p"
	.string "But it was old and creaky.\p"
	.string "So we replaced it with our RADIO\n"
	.string "TOWER.\p"
	.string "We dug up that wing during\n"
	.string "construction.\p"
	.string "I heard that all sorts of POKéMON\n"
	.string "lived in GOLDENROD in the past.\p"
	.string "Perhaps…\p"
	.string "That wing has some connection to the\n"
	.string "WHIRL ISLANDS near CIANWOOD CITY…\p"
	.string "OK, I better go to my OFFICE.$"

GoldenrodCity_RadioTower_5F_Text_DirectorLegendary:
	.string "Ah!\p"
	.string "That reminds me…\p"
	.string "That wing I gave you... I think\n"
	.string "it's related to the LEGENDARY\l"
	.string "POKéMON.\p"
	.string "But! The LEGENDARY POKéMON won't\n"
	.string "appear with just that wing...\p"
	.string "Apparently there is something else\n"
	.string "you need... Or something like that.\p"
	.string "I wonder what it was...\p"
	.string "I can't remember.$"

GoldenrodCity_RadioTower_5F_Text_DirectorFakeout:
	.string "Are you expecting something?\n"
	.string "This is what they call FAKE OUT.\p"
	.string "I really must go back to my OFFICE\n"
	.string "this time. See ya!$"

GoldenrodCity_RadioTower_5F_Text_DirectorIntro:
	.string "DIRECTOR: Hello, {PLAYER}!\p"
	.string "You know, I love POKéMON.\p"
	.string "I built this RADIO TOWER so I could\n"
	.string "express my love of POKéMON.\p"
	.string "It would be nice if people enjoyed\n"
	.string "our programs.$"

GoldenrodCity_RadioTower_5F_Text_Ben:
	.string "BEN: Do you listen to our music?$"

GoldenrodCity_RadioTower_5F_Text_DirectorOfficeSign:
	.string "5F DIRECTOR'S   OFFICE$"

GoldenrodCity_RadioTower_5F_Text_Studio1Sign:
	.string "5F STUDIO 1$"
