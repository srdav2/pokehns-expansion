SaffronCity_SilphCo_hns_MapScripts::
	.byte 0

SaffronCity_SilphCo_EventScript_Steven::
	lock 
	msgbox SaffronCity_SilphCo_Text_Steven1, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	delay 20
	playse SE_PIN
	applymovement LOCALID_SILPHCO_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SILPHCO_STEVEN
SaffronCity_SilphCo_EventScript_StevenChooseStone::
	message SaffronCity_SilphCo_Text_Steven2
	waitmessage
	multichoice 20, 0, MULTI_HOENN_STARTERS, FALSE
	switch VAR_RESULT
	case 0, SaffronCity_SilphCo_EventScript_TreeckoChosen
	case 1, SaffronCity_SilphCo_EventScript_TorchicChosen
	case 2, SaffronCity_SilphCo_EventScript_MudkipChosen
	case MULTI_B_PRESSED, SaffronCity_SilphCo_EventScript_Refused

SaffronCity_SilphCo_EventScript_Refused::
	msgbox SaffronCity_SilphCo_Text_Refused, MSGBOX_DEFAULT
	turnobject LOCALID_SILPHCO_STEVEN, DIR_NORTH
	closemessage
	release
	end

SaffronCity_SilphCo_Text_Refused:
	.string "Oh...$"

SaffronCity_SilphCo_EventScript_TreeckoChosen::
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TREECKO
	bufferspeciesname STR_VAR_1, SPECIES_TREECKO
	msgbox SaffronCity_SilphCo_Text_Steven3, MSGBOX_DEFAULT
	givemon SPECIES_TREECKO, 5
	call Common_EventScript_GiftMon
	goto SaffronCity_SilphCo_EventScript_AfterStarterGiven
SaffronCity_SilphCo_EventScript_TorchicChosen::
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TORCHIC
	bufferspeciesname STR_VAR_1, SPECIES_TORCHIC
	msgbox SaffronCity_SilphCo_Text_Steven3, MSGBOX_DEFAULT
	givemon SPECIES_TORCHIC, 5
	call Common_EventScript_GiftMon
	goto SaffronCity_SilphCo_EventScript_AfterStarterGiven
SaffronCity_SilphCo_EventScript_MudkipChosen::
	closemessage
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MUDKIP
	bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
	msgbox SaffronCity_SilphCo_Text_Steven3, MSGBOX_DEFAULT
	givemon SPECIES_MUDKIP, 5
	call Common_EventScript_GiftMon
	goto SaffronCity_SilphCo_EventScript_AfterStarterGiven

SaffronCity_SilphCo_EventScript_AfterStarterGiven::
	msgbox SaffronCity_SilphCo_Text_Steven4, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, SaffronCity_SilphCo_EventScript_PlayerMove
	applymovement LOCALID_SILPHCO_STEVEN, SaffronCity_SilphCo_Movement_StevenLeave
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_GOT_HOENN_STARTER
	removeobject LOCALID_SILPHCO_STEVEN
	release
	end

SaffronCity_SilphCo_EventScript_PlayerMove:
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	return

SaffronCity_SilphCo_Movement_StevenLeave:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end


SaffronCity_SilphCo_Text_Steven1:
	.string "Hello...\n"
	.string "You're breaking up...\l"
	.string "I think it depends on my dad.\l"
	.string "I see...\n"
	.string "I'll be on my way. See you soon.$"
SaffronCity_SilphCo_Text_Steven2:
	.string "STEVEN: You are... I remember your\n"
	.string "eyes.\p"
	.string "When I see a trainer whose eyes\n"
	.string "twinkle, I always remember.\p"
	.string "You have a POKéDEX! So you are\n"
	.string "also in search of POKéMON!\l"
	.string "Let me see...\p"
	.string "I think I can help you with that.\p"
	.string "Let's say that you have stones in\n"
	.string "front of you. Which color would\l"
	.string " you pick?$"
SaffronCity_SilphCo_Text_Steven3:
	.string "You chose correctly! I'll give you\n"
	.string "{STR_VAR_1}!$"
SaffronCity_SilphCo_Text_Steven4:
	.string "Take good care of it. Your caring\n"
	.string "for it will make me very happy.$"

SaffronCity_SilphCo_EventScript_Receptionist::
	msgbox SilphCo_Text_Receptionist, MSGBOX_NPC
	end
SaffronCity_SilphCo_EventScript_Officer::
	goto_if_set FLAG_GOT_UP_GRADE, SaffronCity_SilphCo_EventScript_OfficerAfter
	msgbox SilphCo_Text_Officer, MSGBOX_NPC
	giveitem ITEM_UP_GRADE
	setflag FLAG_GOT_UP_GRADE
SaffronCity_SilphCo_EventScript_OfficerAfter::
	msgbox SilphCo_Text_Officer_GotUpGrade, MSGBOX_NPC
	end

SaffronCity_SilphCo_EventScript_Sign1::
	msgbox SilphCo_Text_Sign1, MSGBOX_SIGN
	end

SaffronCity_SilphCo_EventScript_Sign2::
	msgbox SilphCo_Text_Sign2, MSGBOX_SIGN
	end

SilphCo_Text_Sign1:
	.string "D.O.G.E. HEADQUARTERS\n"
	.string "Dept. Of Gym Efficiency$"

SilphCo_Text_Sign2:
	.string "D.O.G.E.: ELEVATOR REMOVED\n"
	.string "(Saved 4 jobs. Cost 40 jobs.)$"

SilphCo_Text_Receptionist:
	.string "Welcome. This is SILPH CO.'s HEAD\n"
	.string "OFFICE BUILDING.$"

SilphCo_Text_Officer:
	.string "Only employees are permitted to\n"
	.string "go upstairs.\p"
	.string "But since you came such a long\n"
	.string "way,\p"
	.string "have this neat little souvenir.$"

SilphCo_Text_Officer_GotUpGrade:
	.string "It's SILPH CO.'s latest product.\p"
	.string "It's not for sale anywhere yet.$"

SaffronCity_SilphCo_EventScript_Auditor1::
	trainerbattle_single TRAINER_DOGE_AUDITOR_1_HNS, SaffronCity_SilphCo_Text_AuditSeen1, SaffronCity_SilphCo_Text_AuditBeaten1
	msgbox SaffronCity_SilphCo_Text_AuditAfter1, MSGBOX_AUTOCLOSE
	end

SaffronCity_SilphCo_EventScript_Auditor2::
	trainerbattle_single TRAINER_DOGE_AUDITOR_2_HNS, SaffronCity_SilphCo_Text_AuditSeen2, SaffronCity_SilphCo_Text_AuditBeaten2
	msgbox SaffronCity_SilphCo_Text_AuditAfter2, MSGBOX_AUTOCLOSE
	end

SaffronCity_SilphCo_EventScript_Auditor3::
	trainerbattle_single TRAINER_DOGE_AUDITOR_3_HNS, SaffronCity_SilphCo_Text_AuditSeen3, SaffronCity_SilphCo_Text_AuditBeaten3
	msgbox SaffronCity_SilphCo_Text_AuditAfter3, MSGBOX_AUTOCLOSE
	end

SaffronCity_SilphCo_EventScript_EmailPrompt::
	lock
	faceplayer
	goto_if_set FLAG_GILDED_PRESSURE_PROMPT_SAFFRON, SaffronCity_SilphCo_EventScript_EmailDone
	msgbox SaffronCity_SilphCo_Text_Email, MSGBOX_YESNO
	setflag FLAG_GILDED_PRESSURE_PROMPT_SAFFRON
	goto_if_eq VAR_RESULT, YES, SaffronCity_SilphCo_EventScript_EmailYes
	msgbox SaffronCity_SilphCo_Text_EmailNo, MSGBOX_DEFAULT
	release
	end

SaffronCity_SilphCo_EventScript_EmailYes::
	addvar VAR_PRESSURE_POINTS, 1
	msgbox SaffronCity_SilphCo_Text_EmailYes, MSGBOX_DEFAULT
	release
	end

SaffronCity_SilphCo_EventScript_EmailDone::
	msgbox SaffronCity_SilphCo_Text_EmailDone, MSGBOX_DEFAULT
	release
	end

SaffronCity_SilphCo_Text_AuditSeen1:
	.string "Audit time. Justify your\n"
	.string "existence in five POKéMON.$"

SaffronCity_SilphCo_Text_AuditBeaten1:
	.string "Efficiency: 0%.$"

SaffronCity_SilphCo_Text_AuditAfter1:
	.string "We made the gym trainers\n"
	.string "efficient. They're gone.$"

SaffronCity_SilphCo_Text_AuditSeen2:
	.string "This floor is under review.\n"
	.string "So are you.$"

SaffronCity_SilphCo_Text_AuditBeaten2:
	.string "Review complete. Painful.$"

SaffronCity_SilphCo_Text_AuditAfter2:
	.string "We cut costs by cutting\n"
	.string "everything. Even the lights.$"

SaffronCity_SilphCo_Text_AuditSeen3:
	.string "Reply with five things you did\n"
	.string "this week. Or battle.$"

SaffronCity_SilphCo_Text_AuditBeaten3:
	.string "That was my five things.$"

SaffronCity_SilphCo_Text_AuditAfter3:
	.string "SABRINA replied with her mind.\n"
	.string "We're still confused.$"

SaffronCity_SilphCo_Text_Email:
	.string "D.O.G.E. EMAIL: Reply with 5\n"
	.string "things you did this week.$"

SaffronCity_SilphCo_Text_EmailYes:
	.string "Thank you. You're fired from a\n"
	.string "job you never had.$"

SaffronCity_SilphCo_Text_EmailNo:
	.string "No reply. Noted. Efficient.$"

SaffronCity_SilphCo_Text_EmailDone:
	.string "Your reply has been\n"
	.string "forwarded to nobody.$"
