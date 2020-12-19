#if defined opws_fix_included_
    #endinput
#endif

#define opws_fix_included_

#tryinclude <YSF>

#if !defined _YSF_included
    #include <Pawn.RakNet>
#endif

#if defined SendPlayerClientGameInit
    #define __YSF_DEFINED
#elseif defined PR_SendRPC
    #define __PAWN_RAKNET_DEFINED PR_SendRPC
#elseif defined BS_Send
    #define __PAWN_RAKNET_DEFINED BS_Send
#else
    #error opws_fix.inc needs SendPlayerClientGameInit (from YSF plugin), PR_SendRPC or BS_Send (from Pawn.RakNet plugin) to work. Update any of the 2 plugins!
#endif

static
#if defined __PAWN_RAKNET_DEFINED
    bool:__opws_fix_PlayerFixed[MAX_PLAYERS],
    __opws_fix_PlayerMarkers = PLAYER_MARKERS_MODE_GLOBAL,
    bool:__opws_fix_UsePlayerPedAnims = false,
    bool:__opws_fix_LimitChatRadius = false,
    bool:__opws_fix_StuntBonus = false,
    bool:__opws_fix_DisableEnterExits = false,
    bool:__opws_fix_ManualVehicles = false,
    bool:__opws_fix_ShowNameTags = true,
    Float:__opws_fix_NameTagDistance = 70.0,
    Float:__opws_fix_ChatRadius = 10000.0;
#else
    bool:__opws_fix_PlayerFixed[MAX_PLAYERS];
#endif

public OnPlayerConnect(playerid)
{
    __opws_fix_PlayerFixed[playerid] = false;

    #if defined opws_fix_OnPlayerConnect
        opws_fix_OnPlayerConnect(playerid);
    #endif
    return 1;
}

public OnPlayerSpawn(playerid)
{
    if (!__opws_fix_PlayerFixed[playerid])
    {
        __opws_fix_PlayerFixed[playerid] = true;

        #if defined __YSF_DEFINED
            SendPlayerClientGameInit(playerid, .lagcompmode = 0);
        #elseif defined __PAWN_RAKNET_DEFINED
            new BitStream:bs = BS_New(), hostname[50];

			GetConsoleVarAsString("hostname", hostname, sizeof(hostname));

            BS_WriteValue(bs,
                PR_CBOOL,   false,
                PR_CBOOL,   __opws_fix_UsePlayerPedAnims,
                PR_CBOOL,   true,
                PR_CBOOL,   __opws_fix_LimitChatRadius,
                PR_FLOAT,   __opws_fix_ChatRadius,
                PR_CBOOL,   __opws_fix_StuntBonus,
                PR_FLOAT,   __opws_fix_NameTagDistance,
                PR_CBOOL,   __opws_fix_DisableEnterExits,
                PR_CBOOL,   true,
                PR_CBOOL,   __opws_fix_ManualVehicles,
                PR_INT32,   0,
                PR_UINT16,  playerid,
                PR_CBOOL,   __opws_fix_ShowNameTags,
                PR_INT32,   __opws_fix_PlayerMarkers,
                PR_UINT8,   12,
                PR_UINT8,   10,
                PR_FLOAT,   0.008,
                PR_CBOOL,   !!GetConsoleVarAsInt("lanmode"),
                PR_INT32,   0,
                PR_CBOOL,   false,
                PR_INT32,   GetConsoleVarAsInt("onfoot_rate"),
                PR_INT32,   GetConsoleVarAsInt("incar_rate"),
                PR_INT32,   GetConsoleVarAsInt("weapon_rate"),
                PR_INT32,   10,
				PR_UINT8,   0,

				PR_UINT8,   0,
				PR_UINT8,   0,
				PR_UINT8,   0,
                
				PR_UINT8,   strlen(hostname),
                PR_STRING,  hostname,
				PR_UINT8,   strlen(hostname)
            );

            __PAWN_RAKNET_DEFINED(bs, playerid, 139, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);
            BS_Delete(bs);
        #endif

        TogglePlayerSpectating(playerid, true);
        TogglePlayerSpectating(playerid, false);
        return 1;
    }

    #if defined opws_fix_OnPlayerSpawn
        opws_fix_OnPlayerSpawn(playerid);
    #endif
    return 1;
}

#if defined __PAWN_RAKNET_DEFINED
    stock opws_fix_SetWeather(weatherid)
    {
        __opws_fix_Weather = weatherid;
        return SetWeather(weatherid);
    }

    stock opws_fix_ShowPlayerMarkers(mode)
    {
        __opws_fix_PlayerMarkers = mode;
        return ShowPlayerMarkers(mode);
    }

    stock opws_fix_ShowNameTags(show)
    {
        __opws_fix_ShowNameTags = !!show;
        return ShowNameTags(show);
    }

    stock opws_fix_ManualVehEngAndLights()
    {
        __opws_fix_ManualVehicles = true;
        return ManualVehicleEngineAndLights();
    }

    stock opws_fix_DisableIntEnterExits()
    {
        __opws_fix_DisableEnterExits = true;
        return DisableInteriorEnterExits();
    }

    stock opws_fix_EnableStuntBonusForAll(enable)
    {
        __opws_fix_StuntBonus = !!enable;
        return EnableStuntBonusForAll(enable);
    }

    stock opws_fix_UsePlayerPedAnims()
    {
        __opws_fix_UsePlayerPedAnims = true;
        return UsePlayerPedAnims();
    }

    stock opws_fix_LimitGlobalChatRadius(Float:chat_radius)
    {
        __opws_fix_LimitChatRadius = true;
        __opws_fix_ChatRadius = chat_radius;
        return LimitGlobalChatRadius(chat_radius);
    }

    #if defined _ALS_SetWeather
        #undef SetWeather
    #else
        #define _ALS_SetWeather
    #endif

    #define SetWeather opws_fix_SetWeather

    #if defined _ALS_ShowPlayerMarkers
        #undef ShowPlayerMarkers
    #else
        #define _ALS_ShowPlayerMarkers
    #endif

    #define ShowPlayerMarkers opws_fix_ShowPlayerMarkers

    #if defined _ALS_ManualVehEngineAndLights
        #undef ManualVehicleEngineAndLights
    #else
        #define _ALS_ManualVehEngineAndLights
    #endif

    #define ManualVehicleEngineAndLights opws_fix_ManualVehEngAndLights

    #if defined _ALS_ShowNameTags
        #undef ShowNameTags
    #else
        #define _ALS_ShowNameTags
    #endif

    #define ShowNameTags opws_fix_ShowNameTags

    #if defined _ALS_DisableInteriorEnterExits
        #undef DisableInteriorEnterExits
    #else
        #define _ALS_DisableInteriorEnterExits
    #endif

    #define DisableInteriorEnterExits opws_fix_DisableIntEnterExits

    #if defined _ALS_EnableStuntBonusForAll
        #undef EnableStuntBonusForAll
    #else
        #define _ALS_EnableStuntBonusForAll
    #endif

    #define EnableStuntBonusForAll opws_fix_EnableStuntBonusForAll

    #if defined _ALS_UsePlayerPedAnims
        #undef UsePlayerPedAnims
    #else
        #define _ALS_UsePlayerPedAnims
    #endif

    #define UsePlayerPedAnims opws_fix_UsePlayerPedAnims

    #if defined _ALS_LimitGlobalChatRadius
        #undef LimitGlobalChatRadius
    #else
        #define _ALS_LimitGlobalChatRadius
    #endif

    #define LimitGlobalChatRadius opws_fix_LimitGlobalChatRadius
#endif

#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn opws_fix_OnPlayerSpawn

#if defined opws_fix_OnPlayerSpawn
    forward opws_fix_OnPlayerSpawn();
#endif

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect opws_fix_OnPlayerConnect

#if defined opws_fix_OnPlayerConnect
    forward opws_fix_OnPlayerConnect();
#endif