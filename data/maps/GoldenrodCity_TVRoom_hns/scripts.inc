GoldenrodCity_TVRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodCity_TVRoom_OnFrame
	.byte 0

GoldenrodCity_TVRoom_OnFrame::
	map_script_2 VAR_GILDED_FINALE, 1, GoldenrodCity_TVRoom_EventScript_Scene
	.2byte 0

GoldenrodCity_TVRoom_EventScript_Scene::
	lockall
	setvar VAR_GILDED_FINALE, 2
	delay 30
	msgbox GiratinaAxis_Text_Crossfire, MSGBOX_DEFAULT
	goto_if_eq VAR_PRESSURE_POINTS, 0, GoldenrodCity_TVRoom_EventScript_None
	goto_if_le VAR_PRESSURE_POINTS, 5, GoldenrodCity_TVRoom_EventScript_Some
	msgbox GiratinaAxis_Text_EpilogueMany, MSGBOX_DEFAULT
	goto GoldenrodCity_TVRoom_EventScript_Out

GoldenrodCity_TVRoom_EventScript_None::
	msgbox GiratinaAxis_Text_EpilogueNone, MSGBOX_DEFAULT
	goto GoldenrodCity_TVRoom_EventScript_Out

GoldenrodCity_TVRoom_EventScript_Some::
	msgbox GiratinaAxis_Text_EpilogueSome, MSGBOX_DEFAULT
	goto GoldenrodCity_TVRoom_EventScript_Out

GoldenrodCity_TVRoom_EventScript_Out::
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_ROUTE29_HNS, 30, 16
	waitstate
	releaseall
	end
