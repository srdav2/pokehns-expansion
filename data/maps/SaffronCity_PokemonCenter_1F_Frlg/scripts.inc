SaffronCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SaffronCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY
	end

SaffronCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

SaffronCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_1F_EventScript_Youngster::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_SILPH_CO_11F, 1, SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone
	msgbox SaffronCity_PokemonCenter_1F_Text_GreatIfEliteFourCameBeatRockets
	release
	end

SaffronCity_PokemonCenter_1F_EventScript_YoungsterRocketsGone::
	msgbox SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff
	release
	end

SaffronCity_PokemonCenter_1F_Text_GrowthRatesDifferBySpecies::
	.string "POKéMON growth rates differ from\n"
	.string "species to species.$"

SaffronCity_PokemonCenter_1F_Text_SilphCoVictimOfFame::
	.string "SILPH CO. is widely known to all.\p"
	.string "It's a victim of its own fame - it\n"
#if IS_HNS
	.string "attracted TEAM MEGA.$"
#else
	.string "attracted TEAM ROCKET.$"
#endif

SaffronCity_PokemonCenter_1F_Text_GreatIfEliteFourCameBeatRockets::
	.string "Sigh…\n"
	.string "Wouldn't this be great?\p"
	.string "If the ELITE FOUR came and\n"
#if IS_HNS
	.string "stomped TEAM MEGA?$"
#else
	.string "stomped TEAM ROCKET?$"
#endif

SaffronCity_PokemonCenter_1F_Text_TeamRocketTookOff::
#if IS_HNS
	.string "TEAM MEGA took off!\n"
#else
	.string "TEAM ROCKET took off!\n"
#endif
	.string "We can go out safely again!\l"
	.string "That's great!$"

