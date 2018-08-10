#include <Windows.h>
#include "Client.h"
#include "Engine.h"
#include "xEngine.h"

//CXEngine xEngine;

VOID UnHookFunction( int iFunction );
//================================================================================
void HUD_Redraw ( float x, int y )
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_Redraw );
}
//================================================================================
void CL_CreateMove (float frametime, struct usercmd_s *cmd, int active)
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_CL_CreateMove );
}
//================================================================================
void HUD_PlayerMove (struct playermove_s *a, int b)
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_PlayerMove );
}
//================================================================================
void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_PostRunCmd );
}
//================================================================================
void HUD_TempEntUpdate(double *pframetime, double *pclient_time, double *pcl_gravity, TEMPENTITY*** pppTempEntFree, TEMPENTITY*** pppTempEntActive, int( **pCallback_AddVisibleEntity )( cl_entity_t *pEntity ), void( **pCallback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ) ) 
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_TempEntUpdate );
}
//================================================================================
void HUD_AddEntity (int type, struct cl_entity_s *ent, const char *modelname)
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_AddEntity );
}
//================================================================================
void HUD_Key_Event( int eventcode, int keynum, const char *pszCurrentBinding )
{
	/*
		Your Code Here
	*/

	UnHookFunction( U_HUD_Key_Event );
}
//================================================================================
