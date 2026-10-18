SproutTower_1F_hns_MapScripts::
	.byte 0

SproutTower_1F_EventScript_SageChow::
	trainerbattle_single TRAINER_CHOW_HNS, SproutTower_Text_SageChow_Seen, SproutTower_Text_SageChow_Beaten
	msgbox SproutTower_Text_SageChow_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Sage1::
	trainerbattle_single TRAINER_PASTOR_GROWTH_1_HNS, SproutTower_1F_Text_PastorSeen, SproutTower_1F_Text_PastorBeaten
	msgbox SproutTower_1F_Text_PastorAfter, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Sage2::
	trainerbattle_single TRAINER_PASTOR_GROWTH_2_HNS, SproutTower_1F_Text_PastorSeen, SproutTower_1F_Text_PastorBeaten
	msgbox SproutTower_1F_Text_PastorAfter, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Granny::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_ItemParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

SproutTower_1F_EventScript_SeedFaith::
	lock
	faceplayer
	goto_if_set FLAG_GILDED_PRESSURE_PROMPT_SPROUT_TOWER, SproutTower_1F_EventScript_SeedFaithAfter
	msgbox SproutTower_1F_Text_SeedFaithAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SproutTower_1F_EventScript_SeedFaithNo
	checkmoney 1000
	goto_if_eq VAR_RESULT, FALSE, SproutTower_1F_EventScript_SeedFaithNoMoney
	removemoney 1000
	addvar VAR_PRESSURE_POINTS, 1
	setflag FLAG_GILDED_PRESSURE_PROMPT_SPROUT_TOWER
	msgbox SproutTower_1F_Text_SeedFaithYes, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_SeedFaithNo::
	setflag FLAG_GILDED_PRESSURE_PROMPT_SPROUT_TOWER
	msgbox SproutTower_1F_Text_SeedFaithNo, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_SeedFaithNoMoney::
	msgbox SproutTower_1F_Text_SeedFaithNoMoney, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_SeedFaithAfter::
	msgbox SproutTower_1F_Text_SeedFaithAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_Text_SeedFaithAsk:
	.string "Bellsprout Ministries offers\n"
	.string "Seed Faith. Donate 1000?$"

SproutTower_1F_Text_SeedFaithYes:
	.string "Your Bellsprout will evolve…\n"
	.string "spiritually.$"

SproutTower_1F_Text_SeedFaithNo:
	.string "The offering plate stays\n"
	.string "empty. No hard feelings.$"

SproutTower_1F_Text_SeedFaithAfter:
	.string "Your faith is between you\n"
	.string "and the Bellsprout.$"

SproutTower_1F_Text_SeedFaithNoMoney:
	.string "You need 1000. The offer\n"
	.string "plate will wait.$"

SproutTower_1F_Text_PastorSeen:
	.string "Invest in yourself!\n"
	.string "My Bellsprout says so!$"

SproutTower_1F_Text_PastorBeaten:
	.string "My growth chart was\n"
	.string "upside down!$"

SproutTower_1F_Text_PastorAfter:
	.string "The tower's budget is\n"
	.string "mostly plant food.$"

SproutTower_Text_SageChow_Seen:
	.string "We stand guard in this tower.\p"
	.string "Here, we express our gratitude\n"
	.string "to honor all POKéMON.$"

SproutTower_Text_SageChow_Beaten:
	.string "Th-Thank you!$"

SproutTower_Text_SageChow_AfterBattle:
	.string "All living beings coexist\n"
	.string "through cooperation.\p"
	.string "We must always be thankful\n"
	.string "for this.$"

SproutTower_Text_1F_Sage1:
	.string "Only if you reach the top will\n"
	.string "you obtain an HM.$"

SproutTower_Text_1F_Sage2:
	.string "SPROUT TOWER now hosts\n"
	.string "BELLSPROUT MINISTRIES.$"

SproutTower_Text_1F_Granny:
	.string "A BELLSPROUT over 100 feet\n"
	.string "tall…\p"
	.string "People say that it became the\n"
	.string "center pillar here.$"

SproutTower_Text_1F_Teacher:
	.string "See the pillar shaking?\p"
	.string "People are training upstairs.$"

SproutTower_Text_1F_Statue:
	.string "A POKéMON statue…\p"
	.string "It looks very distinguished.$"
