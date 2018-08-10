/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//
//  cdll_int.h
//
// 4-23-98  
// JOHN:  client dll interface declarations
//

#ifndef CDLL_INT_H
#define CDLL_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "const.h"

// this file is included by both the engine and the client-dll,
// so make sure engine declarations aren't done twice

typedef int HSPRITE;	// handle to a graphic

#define SCRINFO_SCREENFLASH 1
#define SCRINFO_STRETCHED	2

typedef struct
{
	int		iSize;
	int		iWidth;
	int		iHeight;
	int		iFlags;
	int		iCharHeight;
	short	charWidths[256];
} SCREENINFO;


typedef struct client_data_s
{
	// fields that cannot be modified  (ie. have no effect if changed)
	vec3_t origin;

	// fields that can be changed by the cldll
	vec3_t viewangles;
	int		iWeaponBits;
	float	fov;	// field of view
} client_data_t;

typedef struct client_sprite_s
{
	char szName[64];
	char szSprite[64];
	int hspr;
	int iRes;
	wrect_t rc;
} client_sprite_t;

typedef struct
{
	int		effect;
	byte	r1, g1, b1, a1;		// 2 colors for effects
	byte	r2, g2, b2, a2;
	float	x;
	float	y;
	float	fadein;
	float	fadeout;
	float	holdtime;
	float	fxtime;
	const char *pName;
	const char *pMessage;
} client_textmessage_t;

typedef struct
{
	char *name;
	short ping;
	byte thisplayer;  // TRUE if this is the calling player

  // stuff that's unused at the moment,  but should be done
	byte spectator;
	byte packetloss;

	char *model;
	short topcolor;
	short bottomcolor;

} hud_player_info_t;


// this is by no means complete,  or even accurate
// FIX BY RetarT - all engfunc typedefs changed to _cdecl
typedef struct cl_enginefuncs_s
{
	// sprite handlers
	HSPRITE						( _cdecl *pfnSPR_Load )			( const char *szPicName );
	int							( _cdecl *pfnSPR_Frames )			( HSPRITE hPic );
	int							( _cdecl *pfnSPR_Height )			( HSPRITE hPic, int frame );
	int							( _cdecl *pfnSPR_Width )			( HSPRITE hPic, int frame );
	void						( _cdecl *pfnSPR_Set )				( HSPRITE hPic, int r, int g, int b );
	void						( _cdecl *pfnSPR_Draw )			( int frame, int x, int y, const wrect_t *prc );
	void						( _cdecl *pfnSPR_DrawHoles )		( int frame, int x, int y, const wrect_t *prc );
	void						( _cdecl *pfnSPR_DrawAdditive )	( int frame, int x, int y, const wrect_t *prc );
	void						( _cdecl *pfnSPR_EnableScissor )	( int x, int y, int width, int height );
	void						( _cdecl *pfnSPR_DisableScissor )	( void );
	client_sprite_t				*( _cdecl *pfnSPR_GetList )			( char *psz, int *piCount );

	// screen handlers
	void						( _cdecl *pfnFillRGBA )			( int x, int y, int width, int height, int r, int g, int b, int a );
	int							( _cdecl *pfnGetScreenInfo ) 		( SCREENINFO *pscrinfo );
	void						( _cdecl *pfnSetCrosshair )		( HSPRITE hspr, wrect_t rc, int r, int g, int b );

	// cvar handlers
	struct cvar_s				*( _cdecl *pfnRegisterVariable )	( char *szName, char *szValue, int flags );
	float						( _cdecl *pfnGetCvarFloat )		( char *szName );
	char*						( _cdecl *pfnGetCvarString )		( char *szName );

	// command handlers
	int							( _cdecl *pfnAddCommand )			( char *cmd_name, void (*function)(void) );
	int							( _cdecl *pfnHookUserMsg )			( char *szMsgName, pfnUserMsgHook pfn );
	int							( _cdecl *pfnServerCmd )			( char *szCmdString );
	int							( _cdecl *pfnClientCmd )			( char *szCmdString );

	void						( _cdecl *pfnGetPlayerInfo )		( int ent_num, hud_player_info_t *pinfo );

	// sound handlers
	void						( _cdecl *pfnPlaySoundByName )		( char *szSound, float volume );
	void						( _cdecl *pfnPlaySoundByIndex )	( int iSound, float volume );

	// vector helpers
	void			 			( _cdecl *pfnAngleVectors )		( const float * vecAngles, float * forward, float * right, float * up );

	// text message system
	client_textmessage_t		*( _cdecl *pfnTextMessageGet )		( const char *pName );
	int							( _cdecl *pfnDrawCharacter )		( int x, int y, int number, int r, int g, int b );
	int							( _cdecl *pfnDrawConsoleString )	( int x, int y, char *string );
	void						( _cdecl *pfnDrawSetTextColor )	( float r, float g, float b );
	void						( _cdecl *pfnDrawConsoleStringLen )(  const char *string, int *length, int *height );

	void						( _cdecl *pfnConsolePrint )		( const char *string );
	void						( _cdecl *pfnCenterPrint )			( const char *string );


// Added for user input processing
	int							( _cdecl *GetWindowCenterX )		( void );
	int							( _cdecl *GetWindowCenterY )		( void );
	void						( _cdecl *GetViewAngles )			( float * );
	void						( _cdecl *SetViewAngles )			( float * );
	int							( _cdecl *GetMaxClients )			( void );
	void						( _cdecl *Cvar_SetValue )			( char *cvar, float value );

	int       					(_cdecl *Cmd_Argc)					(void);	
	char						*( _cdecl *Cmd_Argv )				( int arg );
	void						( _cdecl *Con_Printf )				( char *fmt, ... );
	void						( _cdecl *Con_DPrintf )			( char *fmt, ... );
	void						( _cdecl *Con_NPrintf )			( int pos, char *fmt, ... );
	void						( _cdecl *Con_NXPrintf )			( struct con_nprint_s *info, char *fmt, ... );

	const char					*( _cdecl *PhysInfo_ValueForKey )	( const char *key );
	const char					*( _cdecl *ServerInfo_ValueForKey )( const char *key );
	float						( _cdecl *GetClientMaxspeed )		( void );
	int							( _cdecl *CheckParm )				( char *parm, char **ppnext );
	void						( _cdecl *Key_Event )				( int key, int down );
	void						( _cdecl *GetMousePosition )		( int *mx, int *my );
	int							( _cdecl *IsNoClipping )			( void );

	struct cl_entity_s			*( _cdecl *GetLocalPlayer )		( void );
	struct cl_entity_s			*( _cdecl *GetViewModel )			( void );
	struct cl_entity_s			*( _cdecl *GetEntityByIndex )		( int idx );

	float						( _cdecl *GetClientTime )			( void );
	void						( _cdecl *V_CalcShake )			( void );
	void						( _cdecl *V_ApplyShake )			( float *origin, float *angles, float factor );

	int							( _cdecl *PM_PointContents )		( float *point, int *truecontents );
	int							( _cdecl *PM_WaterEntity )			( float *p );
	struct pmtrace_s			*( _cdecl *PM_TraceLine )			( float *start, float *end, int flags, int usehull, int ignore_pe );

	struct model_s				*( _cdecl *CL_LoadModel )			( const char *modelname, int *index );
	int							( _cdecl *CL_CreateVisibleEntity )	( int type, struct cl_entity_s *ent );

	const struct model_s *		( _cdecl *GetSpritePointer )		( HSPRITE hSprite );
	void						( _cdecl *pfnPlaySoundByNameAtLocation )	( char *szSound, float volume, float *origin );

	unsigned short				( _cdecl *pfnPrecacheEvent )		( int type, const char* psz );
	void						( _cdecl *pfnPlaybackEvent )		( int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
	void						( _cdecl *pfnWeaponAnim )			( int iAnim, int body );
	float						( _cdecl *pfnRandomFloat )			( float flLow, float flHigh );
	long						( _cdecl *pfnRandomLong )			( long lLow, long lHigh );
	void						( _cdecl *pfnHookEvent )			( char *name, void ( *pfnEvent )( struct event_args_s *args ) );
	int							(_cdecl *Con_IsVisible)			();
	const char					*( _cdecl *pfnGetGameDirectory )	( void );
	struct cvar_s				*( _cdecl *pfnGetCvarPointer )		( const char *szName );
	const char					*( _cdecl *Key_LookupBinding )		( const char *pBinding );
	const char					*( _cdecl *pfnGetLevelName )		( void );
	void						( _cdecl *pfnGetScreenFade )		( struct screenfade_s *fade );
	void						( _cdecl *pfnSetScreenFade )		( struct screenfade_s *fade );
	void                        *( _cdecl *VGui_GetPanel )         ( );
	void                         ( _cdecl *VGui_ViewportPaintBackground ) (int extents[4]);

	byte*						(_cdecl *COM_LoadFile)				( char *path, int usehunk, int *pLength );
	char*						(_cdecl *COM_ParseFile)			( char *data, char *token );
	void						(_cdecl *COM_FreeFile)				( void *buffer );
		
	struct triangleapi_s		*pTriAPI;
	struct efx_api_s			*pEfxAPI;
	struct event_api_s			*pEventAPI;
	struct demo_api_s			*pDemoAPI;
	struct net_api_s			*pNetAPI;
	struct IVoiceTweak_s		*pVoiceTweak;

	// returns 1 if the client is a spectator only (connected to a proxy), 0 otherwise or 2 if in dev_overview mode
	int							( _cdecl *IsSpectateOnly ) ( void );
	struct model_s				*( _cdecl *LoadMapSprite )			( const char *filename );

	// file search functions
	void						( _cdecl *COM_AddAppDirectoryToSearchPath ) ( const char *pszBaseDir, const char *appName );
	int							( _cdecl *COM_ExpandFilename)				 ( const char *fileName, char *nameOutBuffer, int nameOutBufferSize );

	// User info
	// playerNum is in the range (1, MaxClients)
	// returns NULL if player doesn't exit
	// returns "" if no value is set
	const char					*( _cdecl *PlayerInfo_ValueForKey )( int playerNum, const char *key );
	void						( _cdecl *PlayerInfo_SetValueForKey )( const char *key, const char *value );

	// Gets a unique ID for the specified player. This is the same even if you see the player on a different server.
	// iPlayer is an entity index, so client 0 would use iPlayer=1.
	// Returns false if there is no player on the server in the specified slot.
	qboolean					(_cdecl *GetPlayerUniqueID)(int iPlayer, char playerID[16]);

	// TrackerID access
	int							(_cdecl *GetTrackerIDForPlayer)(int playerSlot);
	int							(_cdecl *GetPlayerForTrackerID)(int trackerID);

	// Same as pfnServerCmd, but the message goes in the unreliable stream so it can't clog the net stream
	// (but it might not get there).
	int							( _cdecl *pfnServerCmdUnreliable )( char *szCmdString );
} cl_enginefunc_t;
/*typedef struct cl_enginefuncs_s
{
	// sprite handlers
	HSPRITE						( *pfnSPR_Load )			( const char *szPicName );
	int							( *pfnSPR_Frames )			( HSPRITE hPic );
	int							( *pfnSPR_Height )			( HSPRITE hPic, int frame );
	int							( *pfnSPR_Width )			( HSPRITE hPic, int frame );
	void						( *pfnSPR_Set )				( HSPRITE hPic, int r, int g, int b );
	void						( *pfnSPR_Draw )			( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_DrawHoles )		( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_DrawAdditive )	( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_EnableScissor )	( int x, int y, int width, int height );
	void						( *pfnSPR_DisableScissor )	( void );
	client_sprite_t				*( *pfnSPR_GetList )			( char *psz, int *piCount );

	// screen handlers
	void						( *pfnFillRGBA )			( int x, int y, int width, int height, int r, int g, int b, int a );
	int							( *pfnGetScreenInfo ) 		( SCREENINFO *pscrinfo );
	void						( *pfnSetCrosshair )		( HSPRITE hspr, wrect_t rc, int r, int g, int b );

	// cvar handlers
	struct cvar_s				*( *pfnRegisterVariable )	( char *szName, char *szValue, int flags );
	float						( *pfnGetCvarFloat )		( char *szName );
	char*						( *pfnGetCvarString )		( char *szName );

	// command handlers
	int							( *pfnAddCommand )			( char *cmd_name, void (*function)(void) );
	int							( *pfnHookUserMsg )			( char *szMsgName, pfnUserMsgHook pfn );
	int							( *pfnServerCmd )			( char *szCmdString );
	int							( *pfnClientCmd )			( char *szCmdString );

	void						( *pfnGetPlayerInfo )		( int ent_num, hud_player_info_t *pinfo );

	// sound handlers
	void						( *pfnPlaySoundByName )		( char *szSound, float volume );
	void						( *pfnPlaySoundByIndex )	( int iSound, float volume );

	// vector helpers
	void			 			( *pfnAngleVectors )		( const float * vecAngles, float * forward, float * right, float * up );

	// text message system
	client_textmessage_t		*( *pfnTextMessageGet )		( const char *pName );
	int							( *pfnDrawCharacter )		( int x, int y, int number, int r, int g, int b );
	int							( *pfnDrawConsoleString )	( int x, int y, char *string );
	void						( *pfnDrawSetTextColor )	( float r, float g, float b );
	void						( *pfnDrawConsoleStringLen )(  const char *string, int *length, int *height );

	void						( *pfnConsolePrint )		( const char *string );
	void						( *pfnCenterPrint )			( const char *string );


// Added for user input processing
	int							( *GetWindowCenterX )		( void );
	int							( *GetWindowCenterY )		( void );
	void						( *GetViewAngles )			( float * );
	void						( *SetViewAngles )			( float * );
	int							( *GetMaxClients )			( void );
	void						( *Cvar_SetValue )			( char *cvar, float value );

	int       					(*Cmd_Argc)					(void);	
	char						*( *Cmd_Argv )				( int arg );
	void						( *Con_Printf )				( char *fmt, ... );
	void						( *Con_DPrintf )			( char *fmt, ... );
	void						( *Con_NPrintf )			( int pos, char *fmt, ... );
	void						( *Con_NXPrintf )			( struct con_nprint_s *info, char *fmt, ... );

	const char					*( *PhysInfo_ValueForKey )	( const char *key );
	const char					*( *ServerInfo_ValueForKey )( const char *key );
	float						( *GetClientMaxspeed )		( void );
	int							( *CheckParm )				( char *parm, char **ppnext );
	void						( *Key_Event )				( int key, int down );
	void						( *GetMousePosition )		( int *mx, int *my );
	int							( *IsNoClipping )			( void );

	struct cl_entity_s			*( *GetLocalPlayer )		( void );
	struct cl_entity_s			*( *GetViewModel )			( void );
	struct cl_entity_s			*( *GetEntityByIndex )		( int idx );

	float						( *GetClientTime )			( void );
	void						( *V_CalcShake )			( void );
	void						( *V_ApplyShake )			( float *origin, float *angles, float factor );

	int							( *PM_PointContents )		( float *point, int *truecontents );
	int							( *PM_WaterEntity )			( float *p );
	struct pmtrace_s			*( *PM_TraceLine )			( float *start, float *end, int flags, int usehull, int ignore_pe );

	struct model_s				*( *CL_LoadModel )			( const char *modelname, int *index );
	int							( *CL_CreateVisibleEntity )	( int type, struct cl_entity_s *ent );

	const struct model_s *		( *GetSpritePointer )		( HSPRITE hSprite );
	void						( *pfnPlaySoundByNameAtLocation )	( char *szSound, float volume, float *origin );

	unsigned short				( *pfnPrecacheEvent )		( int type, const char* psz );
	void						( *pfnPlaybackEvent )		( int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
	void						( *pfnWeaponAnim )			( int iAnim, int body );
	float						( *pfnRandomFloat )			( float flLow, float flHigh );
	long						( *pfnRandomLong )			( long lLow, long lHigh );
	void						( *pfnHookEvent )			( char *name, void ( *pfnEvent )( struct event_args_s *args ) );
	int							(*Con_IsVisible)			();
	const char					*( *pfnGetGameDirectory )	( void );
	struct cvar_s				*( *pfnGetCvarPointer )		( const char *szName );
	const char					*( *Key_LookupBinding )		( const char *pBinding );
	const char					*( *pfnGetLevelName )		( void );
	void						( *pfnGetScreenFade )		( struct screenfade_s *fade );
	void						( *pfnSetScreenFade )		( struct screenfade_s *fade );
	void                        *( *VGui_GetPanel )         ( );
	void                         ( *VGui_ViewportPaintBackground ) (int extents[4]);

	byte*						(*COM_LoadFile)				( char *path, int usehunk, int *pLength );
	char*						(*COM_ParseFile)			( char *data, char *token );
	void						(*COM_FreeFile)				( void *buffer );
		
	struct triangleapi_s		*pTriAPI;
	struct efx_api_s			*pEfxAPI;
	struct event_api_s			*pEventAPI;
	struct demo_api_s			*pDemoAPI;
	struct net_api_s			*pNetAPI;
	struct IVoiceTweak_s		*pVoiceTweak;

	// returns 1 if the client is a spectator only (connected to a proxy), 0 otherwise or 2 if in dev_overview mode
	int							( *IsSpectateOnly ) ( void );
	struct model_s				*( *LoadMapSprite )			( const char *filename );

	// file search functions
	void						( *COM_AddAppDirectoryToSearchPath ) ( const char *pszBaseDir, const char *appName );
	int							( *COM_ExpandFilename)				 ( const char *fileName, char *nameOutBuffer, int nameOutBufferSize );

	// User info
	// playerNum is in the range (1, MaxClients)
	// returns NULL if player doesn't exit
	// returns "" if no value is set
	const char					*( *PlayerInfo_ValueForKey )( int playerNum, const char *key );
	void						( *PlayerInfo_SetValueForKey )( const char *key, const char *value );

	// Gets a unique ID for the specified player. This is the same even if you see the player on a different server.
	// iPlayer is an entity index, so client 0 would use iPlayer=1.
	// Returns false if there is no player on the server in the specified slot.
	qboolean					(*GetPlayerUniqueID)(int iPlayer, char playerID[16]);

	// TrackerID access
	int							(*GetTrackerIDForPlayer)(int playerSlot);
	int							(*GetPlayerForTrackerID)(int trackerID);

	// Same as pfnServerCmd, but the message goes in the unreliable stream so it can't clog the net stream
	// (but it might not get there).
	int							( *pfnServerCmdUnreliable )( char *szCmdString );
} cl_enginefunc_t;*/

#ifndef IN_BUTTONS_H
#include "in_buttons.h"
#endif

#define CLDLL_INTERFACE_VERSION		7

extern void ClientDLL_Init( void ); // from cdll_int.c
extern void ClientDLL_Shutdown( void );
extern void ClientDLL_HudInit( void );
extern void ClientDLL_HudVidInit( void );
extern void	ClientDLL_UpdateClientData( void );
extern void ClientDLL_Frame( double time );
extern void ClientDLL_HudRedraw( int intermission );
extern void ClientDLL_MoveClient( struct playermove_s *ppmove );
extern void ClientDLL_ClientMoveInit( struct playermove_s *ppmove );
extern char ClientDLL_ClientTextureType( char *name );

extern void ClientDLL_CreateMove( float frametime, struct usercmd_s *cmd, int active );
extern void ClientDLL_ActivateMouse( void );
extern void ClientDLL_DeactivateMouse( void );
extern void ClientDLL_MouseEvent( int mstate );
extern void ClientDLL_ClearStates( void );
extern int ClientDLL_IsThirdPerson( void );
extern void ClientDLL_GetCameraOffsets( float *ofs );
extern int ClientDLL_GraphKeyDown( void );
extern struct kbutton_s *ClientDLL_FindKey( const char *name );
extern void ClientDLL_CAM_Think( void );
extern void ClientDLL_IN_Accumulate( void );
extern void ClientDLL_CalcRefdef( struct ref_params_s *pparams );
extern int ClientDLL_AddEntity( int type, struct cl_entity_s *ent );
extern void ClientDLL_CreateEntities( void );

extern void ClientDLL_DrawNormalTriangles( void );
extern void ClientDLL_DrawTransparentTriangles( void );
extern void ClientDLL_StudioEvent( const struct mstudioevent_s *event, const struct cl_entity_s *entity );
extern void ClientDLL_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
extern void ClientDLL_TxferLocalOverrides( struct entity_state_s *state, const struct clientdata_s *client );
extern void ClientDLL_ProcessPlayerState( struct entity_state_s *dst, const struct entity_state_s *src );
extern void ClientDLL_TxferPredictionData ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd );
extern void ClientDLL_ReadDemoBuffer( int size, unsigned char *buffer );
extern int ClientDLL_ConnectionlessPacket( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
extern int ClientDLL_GetHullBounds( int hullnumber, float *mins, float *maxs );

extern void ClientDLL_VGui_ConsolePrint(const char* text);

extern int ClientDLL_Key_Event( int down, int keynum, const char *pszCurrentBinding );
extern void ClientDLL_TempEntUpdate( double ft, double ct, double grav, struct tempent_s **ppFreeTE, struct tempent_s **ppActiveTE, int ( *addTEntity )( struct cl_entity_s *pEntity ), void ( *playTESound )( struct tempent_s *pTemp, float damp ) );
extern struct cl_entity_s *ClientDLL_GetUserEntity( int index );
extern void ClientDLL_VoiceStatus(int entindex, qboolean bTalking);
extern void ClientDLL_DirectorEvent(unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags);


#ifdef __cplusplus
}
#endif

#endif // CDLL_INT_H
