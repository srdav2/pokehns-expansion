MtSilver_Outside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_Outside_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtSilver_Outside_OnTransition: 
	callnative SetTimeBasedEncounters
	setflag FLAG_VISITED_MT_SILVER
	end

MtSilver_Outside_EventScript_Sign::
	msgbox MtSilver_Outside_Text_Sign, MSGBOX_SIGN
	end

MtSilver_Outside_Text_Sign:
	.string "MT. SILVER$"

MtSilver_Outside_EventScript_RecruiterMega::
	msgbox MtSilver_Outside_Text_RecruiterMega, MSGBOX_NPC
	end

MtSilver_Outside_EventScript_RecruiterCommittee::
	msgbox MtSilver_Outside_Text_RecruiterCommittee, MSGBOX_NPC
	end

MtSilver_Outside_Text_RecruiterMega:
	.string "MEGA: We want RED. Perfect hire.\n"
	.string "He never disagrees with us.$"

MtSilver_Outside_Text_RecruiterCommittee:
	.string "COMMITTEE: No, he is ours. He\n"
	.string "us. He never says anything.$"
