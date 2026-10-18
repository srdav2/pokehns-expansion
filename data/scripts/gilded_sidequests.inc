@ P2-14: side quests

Gilded_YardSign_29::
	lock
	msgbox Gilded_YardSign_29_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_29_No
	setvar VAR_0x8004, 0
	special GildedYardSignRemove
	removeobject 22
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_29_No::
	release
	end

Gilded_YardSign_29_Text:
	.string "GAUDY FOR REGION\nHe'd make it great.$"

Gilded_YardSign_30::
	lock
	msgbox Gilded_YardSign_30_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_30_No
	setvar VAR_0x8004, 1
	special GildedYardSignRemove
	removeobject 27
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_30_No::
	release
	end

Gilded_YardSign_30_Text:
	.string "MEGA: Freedom is\nmandatory.$"

Gilded_YardSign_31::
	lock
	msgbox Gilded_YardSign_31_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_31_No
	setvar VAR_0x8004, 2
	special GildedYardSignRemove
	removeobject 23
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_31_No::
	release
	end

Gilded_YardSign_31_Text:
	.string "SLOWPOKE-T: Not a tail.\nA statement.$"

Gilded_YardSign_32::
	lock
	msgbox Gilded_YardSign_32_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_32_No
	setvar VAR_0x8004, 3
	special GildedYardSignRemove
	removeobject 40
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_32_No::
	release
	end

Gilded_YardSign_32_Text:
	.string "SIGN THIS OR ELSE...\nit's an offer.$"

Gilded_YardSign_34::
	lock
	msgbox Gilded_YardSign_34_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_34_No
	setvar VAR_0x8004, 4
	special GildedYardSignRemove
	removeobject 36
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_34_No::
	release
	end

Gilded_YardSign_34_Text:
	.string "HONK IF YOU AGREE.\nWE WILL NOT HONK BACK.$"

Gilded_YardSign_35::
	lock
	msgbox Gilded_YardSign_35_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_35_No
	setvar VAR_0x8004, 5
	special GildedYardSignRemove
	removeobject 23
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_35_No::
	release
	end

Gilded_YardSign_35_Text:
	.string "VOTE EARLY, VOTE OFTEN\n(Paid for by nobody).$"

Gilded_YardSign_36::
	lock
	msgbox Gilded_YardSign_36_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_36_No
	setvar VAR_0x8004, 6
	special GildedYardSignRemove
	removeobject 22
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_36_No::
	release
	end

Gilded_YardSign_36_Text:
	.string "TAXES: OFF. TOLLS: ON.$"

Gilded_YardSign_37::
	lock
	msgbox Gilded_YardSign_37_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_37_No
	setvar VAR_0x8004, 7
	special GildedYardSignRemove
	removeobject 19
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_37_No::
	release
	end

Gilded_YardSign_37_Text:
	.string "I BRAKE FOR GRINDWELLS.$"

Gilded_YardSign_38::
	lock
	msgbox Gilded_YardSign_38_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_38_No
	setvar VAR_0x8004, 8
	special GildedYardSignRemove
	removeobject 20
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_38_No::
	release
	end

Gilded_YardSign_38_Text:
	.string "THE REGION HAS A PLAN.\nIt's on the sign.$"

Gilded_YardSign_39::
	lock
	msgbox Gilded_YardSign_39_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_39_No
	setvar VAR_0x8004, 9
	special GildedYardSignRemove
	removeobject 21
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_39_No::
	release
	end

Gilded_YardSign_39_Text:
	.string "RED CAPS FOR ALL.\nSizes not included.$"

Gilded_YardSign_42::
	lock
	msgbox Gilded_YardSign_42_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_42_No
	setvar VAR_0x8004, 10
	special GildedYardSignRemove
	removeobject 20
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_42_No::
	release
	end

Gilded_YardSign_42_Text:
	.string "BUILD THE WALL...\nAround this sign.$"

Gilded_YardSign_43::
	lock
	msgbox Gilded_YardSign_43_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_43_No
	setvar VAR_0x8004, 11
	special GildedYardSignRemove
	removeobject 19
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_43_No::
	release
	end

Gilded_YardSign_43_Text:
	.string "D.O.G.E. SAVED YOU\n0 POKéDOLLARS.$"

Gilded_YardSign_44::
	lock
	msgbox Gilded_YardSign_44_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_44_No
	setvar VAR_0x8004, 12
	special GildedYardSignRemove
	removeobject 28
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_44_No::
	release
	end

Gilded_YardSign_44_Text:
	.string "FREEDOM TOLL AHEAD.\nCash only.$"

Gilded_YardSign_45::
	lock
	msgbox Gilded_YardSign_45_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_45_No
	setvar VAR_0x8004, 13
	special GildedYardSignRemove
	removeobject 27
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_45_No::
	release
	end

Gilded_YardSign_45_Text:
	.string "MAKE THE ROUTE\nSLIPPERY AGAIN.$"

Gilded_YardSign_46::
	lock
	msgbox Gilded_YardSign_46_Text, MSGBOX_DEFAULT
	msgbox Gilded_YardSign_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_YardSign_46_No
	setvar VAR_0x8004, 14
	special GildedYardSignRemove
	removeobject 14
	msgbox Gilded_YardSign_Removed, MSGBOX_DEFAULT
	release
	end

Gilded_YardSign_46_No::
	release
	end

Gilded_YardSign_46_Text:
	.string "GAUDY: BIGGER SIGNS,\nSMALLER TRUTHS.$"

Gilded_YardSignHideOnly::
	special GildedYardSignHide
	end

Gilded_YardSign_Ask:
	.string "A yard sign. Remove it?$"

Gilded_YardSign_Removed:
	.string "You pulled up the sign.\n"
	.string "The lawn sighs with relief.$"

Route29_EventScript_LawnRanger::
	lock
	faceplayer
	special GildedYardSignCount
	copyvar VAR_0x8008, VAR_RESULT
	msgbox Gilded_LawnRanger_Intro, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	msgbox Gilded_LawnRanger_Count, MSGBOX_DEFAULT
	goto_if_lt VAR_0x8008, 5, Gilded_LawnRanger_End
	setvar VAR_0x8004, 0
	special GildedQuestBitTest
	goto_if_eq VAR_RESULT, TRUE, Gilded_LawnRanger_Check10
	setvar VAR_0x8004, 0
	special GildedQuestBitSet
	msgbox Gilded_LawnRanger_Reward1, MSGBOX_DEFAULT
	giveitem ITEM_LEFTOVERS
Gilded_LawnRanger_Check10::
	goto_if_lt VAR_0x8008, 10, Gilded_LawnRanger_End
	setvar VAR_0x8004, 1
	special GildedQuestBitTest
	goto_if_eq VAR_RESULT, TRUE, Gilded_LawnRanger_Check15
	setvar VAR_0x8004, 1
	special GildedQuestBitSet
	msgbox Gilded_LawnRanger_Reward2, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG
Gilded_LawnRanger_Check15::
	goto_if_lt VAR_0x8008, 15, Gilded_LawnRanger_End
	setvar VAR_0x8004, 2
	special GildedQuestBitTest
	goto_if_eq VAR_RESULT, TRUE, Gilded_LawnRanger_End
	setvar VAR_0x8004, 2
	special GildedQuestBitSet
	msgbox Gilded_LawnRanger_Reward3, MSGBOX_DEFAULT
	giveitem ITEM_ABILITY_CAPSULE
Gilded_LawnRanger_End::
	release
	end

Gilded_LawnRanger_Intro:
	.string "LAWN RANGER: Those yard signs are\n"
	.string "everywhere. Pull them up, please.$"

Gilded_LawnRanger_Count:
	.string "Signs removed so far: {STR_VAR_1}\n"
	.string "Rewards at 5, 10 and 15.$"

Gilded_LawnRanger_Reward1:
	.string "Five already! Take these\n"
	.string "LEFTOVERS.$"

Gilded_LawnRanger_Reward2:
	.string "Ten! The lawn thanks you.\n"
	.string "Here, a LUCKY EGG.$"

Gilded_LawnRanger_Reward3:
	.string "All fifteen! You're a hero.\n"
	.string "Take this ABILITY CAPSULE.$"

Gilded_DebateBro1::
	lock
	faceplayer
	goto_if_defeated TRAINER_DEBATE_BRO_1_HNS, Gilded_DebateBro1_Done
	msgbox Gilded_Debate1_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_Debate1_No
	msgbox Gilded_Debate_Yes, MSGBOX_DEFAULT
	goto Gilded_Debate1_Fight
Gilded_Debate1_No::
	msgbox Gilded_Debate_No, MSGBOX_DEFAULT
Gilded_Debate1_Fight::
	trainerbattle_no_intro TRAINER_DEBATE_BRO_1_HNS, Gilded_Debate_Lost
Gilded_DebateBro1_Done::
	msgbox Gilded_Debate1_After, MSGBOX_DEFAULT
	release
	end

Gilded_DebateBro2::
	lock
	faceplayer
	goto_if_defeated TRAINER_DEBATE_BRO_2_HNS, Gilded_DebateBro2_Done
	msgbox Gilded_Debate2_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_Debate2_No
	msgbox Gilded_Debate_Yes, MSGBOX_DEFAULT
	goto Gilded_Debate2_Fight
Gilded_Debate2_No::
	msgbox Gilded_Debate_No, MSGBOX_DEFAULT
Gilded_Debate2_Fight::
	trainerbattle_no_intro TRAINER_DEBATE_BRO_2_HNS, Gilded_Debate_Lost
Gilded_DebateBro2_Done::
	msgbox Gilded_Debate2_After, MSGBOX_DEFAULT
	release
	end

Gilded_DebateBro3::
	lock
	faceplayer
	goto_if_defeated TRAINER_DEBATE_BRO_3_HNS, Gilded_DebateBro3_Done
	msgbox Gilded_Debate3_Ask, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gilded_Debate3_No
	msgbox Gilded_Debate_Yes, MSGBOX_DEFAULT
	goto Gilded_Debate3_Fight
Gilded_Debate3_No::
	msgbox Gilded_Debate_No, MSGBOX_DEFAULT
Gilded_Debate3_Fight::
	trainerbattle_no_intro TRAINER_DEBATE_BRO_3_HNS, Gilded_Debate_Lost
Gilded_DebateBro3_Done::
	goto_if_not_defeated TRAINER_DEBATE_BRO_1_HNS, Gilded_Debate3_Early
	goto_if_not_defeated TRAINER_DEBATE_BRO_2_HNS, Gilded_Debate3_Early
	setvar VAR_0x8004, 3
	special GildedQuestBitTest
	goto_if_eq VAR_RESULT, TRUE, Gilded_Debate3_Given
	setvar VAR_0x8004, 3
	special GildedQuestBitSet
	msgbox Gilded_Debate3_Reward, MSGBOX_DEFAULT
	giveitem ITEM_CHOICE_SPECS
Gilded_Debate3_Given::
	msgbox Gilded_Debate3_After, MSGBOX_DEFAULT
	release
	end

Gilded_Debate3_Early::
	msgbox Gilded_Debate3_EarlyText, MSGBOX_DEFAULT
	release
	end

Gilded_Debate1_Ask:
	.string "DEBATER: Hot take. Pineapple on\n"
	.string "a POKé BALL. Do you agree?$"

Gilded_Debate2_Ask:
	.string "DEBATER: Hot take. Sleep is just\n"
	.string "laziness. Agree?$"

Gilded_Debate3_Ask:
	.string "DEBATER: Hot take. Weather is\n"
	.string "fake. Agree?$"

Gilded_Debate_Yes:
	.string "DEBATER: Wow. No push-back?\n"
	.string "Then you lose the debate!$"

Gilded_Debate_No:
	.string "DEBATER: Cope. Seethe.\n"
	.string "Fine, let's settle this.$"

Gilded_Debate_Lost:
	.string "That was a bad-faith argument.$"

Gilded_Debate1_After:
	.string "DEBATER: I yield. Ask my buddy.$"

Gilded_Debate2_After:
	.string "DEBATER: Fine. You win.\n"
	.string "I'm not tired though.$"

Gilded_Debate3_EarlyText:
	.string "DEBATER: Beat my two buddies\n"
	.string "first. It's debate club rules.$"

Gilded_Debate3_Reward:
	.string "DEBATER: You beat us all.\n"
	.string "Take these CHOICE SPECS.$"

Gilded_Debate3_After:
	.string "DEBATER: Facts don't care\n"
	.string "about your feelings. Neither do I.$"

Gilded_TariffClerkNpc::
	msgbox Gilded_TariffClerk_Text, MSGBOX_NPC
	end

Gilded_TariffClerk_Text:
	.string "Clerk: The port's tariffs make\n"
	.string "stock impossible. Try the docks.$"

Gilded_TariffDealer::
	lock
	faceplayer
	msgbox Gilded_TariffDealer_Text, MSGBOX_DEFAULT
	pokemart Gilded_TariffMart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Gilded_TariffDealer_Text:
	.string "Psst. Off the books. Normal\n"
	.string "prices. No questions.$"

	.align 2
Gilded_TariffMart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end
