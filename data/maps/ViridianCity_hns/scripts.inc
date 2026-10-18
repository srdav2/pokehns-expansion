ViridianCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ViridianCity_OnFrame
	.byte 0

ViridianCity_EventScript_CityEnter::
	setflag FLAG_VISITED_VIRIDIAN_CITY
	goto_if_unset FLAG_HIDE_CINNABAR_BLUE, ViridianCity_EventScript_RallyHide
	goto_if_defeated TRAINER_PRESIDENT_REX_GAUDY_COMEBACK_RALLY_HNS, ViridianCity_EventScript_RallyHide
	clearflag FLAG_TEMP_5
	end

ViridianCity_EventScript_RallyHide::
	setflag FLAG_TEMP_5
	end

ViridianCity_OnFrame::
	map_script_2 VAR_OAK_MT_SILVER_CALL, 1, ViridianCity_EventScript_OakCall
	.2byte 0

ViridianCity_EventScript_OakCall::
	lock
	setspeaker ViridianCity_Text_OakName
	pokenavcall ViridianCity_Text_OakCall
	waitmessage
	delay 30
	setvar VAR_OAK_MT_SILVER_CALL, 2
	release
	end

ViridianCity_Text_OakName:
	.string "OAK$"

ViridianCity_Text_OakCall:
	.string "OAK: Ah, {PLAYER}!\p"
	.string "Come and see my at my\n"
	.string "LAB in PALLET TOWN\l"
	.string "when you get the chance.$"

ViridianCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox ViridianCity_Text_CoffeeGramps_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_EventScript_GrampsDoubted
	msgbox ViridianCity_Text_CoffeeGramps_Believed, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_EventScript_GrampsDoubted::
	msgbox ViridianCity_Text_CoffeeGramps_Doubted, MSGBOX_DEFAULT
	closemessage
	release
	end

VirianCity_EventScript_GymGramps::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_Text_GrampsNearGym, MSGBOX_NPC
	end

VirianCity_EventScript_GymGrampsBlue::
	msgbox ViridianCity_Text_GrampsNearGym_BlueReturned, MSGBOX_NPC
	end

ViridianCity_EventScript_Fisher::
	goto_if_set FLAG_GOT_VIRIDIAN_TM_DREAM_EATER, ViridianCity_EventScript_FisherAfter
	msgbox ViridianCity_Text_DreamEaterFisher, MSGBOX_NPC
	giveitem ITEM_TM_DREAM_EATER
	setflag FLAG_GOT_VIRIDIAN_TM_DREAM_EATER
	end

ViridianCity_EventScript_FisherAfter::
	msgbox ViridianCity_Text_DreamEaterFisher_GotTM, MSGBOX_NPC
	end

ViridianCity_EventScript_Youngster::
	msgbox ViridianCity_Text_Youngster, MSGBOX_NPC
	end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_WelcomeSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_CitySign2::
	msgbox ViridianCity_Text_Sign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_Text_CoffeeGramps_Question:
	.string "Hey, kid! I just had a double shot\n"
	.string "of espresso, and I am wired!\p"
	.string "I need to talk to someone, so you'll\n"
	.string "have to do!\p"
	.string "I might not look like much now, but\n"
	.string "I was an expert at catching POKéMON.\p"
	.string "Do you believe me?$"

ViridianCity_Text_CoffeeGramps_Believed:
	.string "Good, good. Yes, I was something\n"
	.string "out of the ordinary, let me tell\l"
	.string "you!$"

ViridianCity_Text_CoffeeGramps_Doubted:
	.string "What? You little whelp!\p"
	.string "If I were just a bit younger, I'd\n"
	.string "show you a thing or two. Humph!$"

ViridianCity_Text_GrampsNearGym:
	.string "This GYM didn't have a LEADER\n"
	.string "until recently.\p"
	.string "A young man from PALLET became\n"
	.string "the LEADER, but he's often away.$"

ViridianCity_Text_GrampsNearGym_BlueReturned:
	.string "Are you going to battle the\n"
	.string "LEADER?\p"
	.string "Good luck to you. You'll need it.$"

ViridianCity_Text_DreamEaterFisherNew:
	.string "…Zzzzz…\p" 
	.string "Yawn!\p"
	.string "I must have dozed off in the sun.\p"
	.string "What? I remind you of somebody?\p"
	.string "I don't know, here, have this.$"


ViridianCity_Text_DreamEaterFisher_GotTM::
	.string "…Zzzzz…$"

ViridianCity_Text_DreamEaterFisher:
	.string "Yawn!\p"
	.string "I must have dozed off in the sun.\p"
	.string "…I had this dream about a DROWZEE\n"
	.string "eating my dream. Weird, huh?\p"
	.string "Huh? What's this?\p"
	.string "Where did this TM come from?\p"
	.string "This is spooky! Here, you can have\n"
	.string "this TM.$"

ViridianCity_Text_DreamEaterFisher_GotDreamEater:
	.string "TM42 contains DREAM EATER…\p"
	.string "…Zzzzz…$"

ViridianCity_Text_Youngster:
	.string "I heard that there are many items\n"
	.string "on the ground in VIRIDIAN FOREST.$"

ViridianCity_Text_Sign:
	.string "THE COMEBACK RALLY\n"
	.string "BIGGER THAN EVER$"

ViridianCity_Text_GymSign:
	.string "VIRIDIAN CITY POKéMON GYM\n"
	.string "LEADER: …\p"
	.string "The rest of the text is illegible…$"

ViridianCity_Text_WelcomeSign:
	.string "WELCOME TO VIRIDIAN CITY,\p"
	.string "THE GATEWAY TO INDIGO PLATEAU$"

ViridianCity_Text_TrainerHouseSign:
	.string "TRAINER HOUSE\p"
	.string "The Club for Top Trainer Battles$"

ViridianCity_EventScript_Rally::
	lockall
	goto_if_unset FLAG_HIDE_CINNABAR_BLUE, ViridianCity_EventScript_RallyOff
	goto_if_defeated TRAINER_PRESIDENT_REX_GAUDY_COMEBACK_RALLY_HNS, ViridianCity_EventScript_RallyOff
	msgbox ViridianCity_Text_RallyCrowd, MSGBOX_DEFAULT
	applymovement 25, Common_Movement_FaceOriginalDirection
	msgbox ViridianCity_Text_RallySilver, MSGBOX_DEFAULT
	msgbox ViridianCity_Text_RallyGaudyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PRESIDENT_REX_GAUDY_COMEBACK_RALLY_HNS, ViridianCity_Text_RallyGaudyDefeat
	msgbox ViridianCity_Text_RallyGaudyExit, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 24
	removeobject 26
	removeobject 27
	removeobject 28
	setflag FLAG_TEMP_5
	fadescreen FADE_FROM_BLACK
	msgbox ViridianCity_Text_RallyDisband, MSGBOX_DEFAULT
	releaseall
	end

ViridianCity_EventScript_RallyOff::
	releaseall
	end

ViridianCity_EventScript_RallyGaudy::
	msgbox ViridianCity_Text_RallyGaudyTalk, MSGBOX_NPC
	end

ViridianCity_EventScript_RallySilver::
	msgbox ViridianCity_Text_RallySilverTalk, MSGBOX_NPC
	end

ViridianCity_EventScript_RallyCrowd::
	msgbox ViridianCity_Text_RallyCrowdTalk, MSGBOX_NPC
	end

ViridianCity_Text_RallyCrowd:
	.string "CROWD: COME-BACK! COME-BACK!\n"
	.string "Make VIRIDIAN great again!$"

ViridianCity_Text_RallySilver:
	.string "SILVER: Everyone's cheering for a\n"
	.string "man who sold the whole region.\p"
	.string "Quiet. Let me handle this.\n"
	.string "{PLAYER}, you're up.$"

ViridianCity_Text_RallyGaudyIntro:
	.string "REX GAUDY: A comeback! Bigger,\n"
	.string "bolder, and fully tax-deductible!\p"
	.string "The crowd came for a winner.\n"
	.string "Let's give them one!$"

ViridianCity_Text_RallyGaudyDefeat:
	.string "Unbelievable. A loss. On camera.$"

ViridianCity_Text_RallyGaudyExit:
	.string "REX GAUDY: Fine. I'm retiring to\n"
	.string "a very big, very beautiful island.\p"
	.string "The rest of you can keep the\n"
	.string "region. It's in great shape!$"

ViridianCity_Text_RallyDisband:
	.string "TEAM MEGA has disbanded.\n"
	.string "The crowd went home to nap.$"

ViridianCity_Text_RallyGaudyTalk:
	.string "REX GAUDY: Tonight, VIRIDIAN!\n"
	.string "Tomorrow, everything else!$"

ViridianCity_Text_RallySilverTalk:
	.string "SILVER: Don't look at me.\n"
	.string "I only came for the fight.$"

ViridianCity_Text_RallyCrowdTalk:
	.string "I don't know what he's selling,\n"
	.string "but I'm already in!$"
