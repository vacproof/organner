#define U_HUD_Redraw		1
#define U_HUD_PlayerMove	2
#define U_CL_CreateMove		3
#define U_HUD_AddEntity		4
#define U_HUD_PostRunCmd	5
#define U_HUD_Key_Event		6
#define U_HUD_TempEntUpdate 7

#include "Engine.h"

void HUD_Redraw ( float x, int y );
void PreV_CalcRefdef(struct ref_params_s *pparams);
void CL_CreateMove (float frametime, struct usercmd_s *cmd, int active);
void HUD_PlayerMove (struct playermove_s *a, int b);
void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed);
void HUD_TempEntUpdate(double *pframetime, double *pclient_time, double *pcl_gravity, TEMPENTITY*** pppTempEntFree, TEMPENTITY*** pppTempEntActive, int( **pCallback_AddVisibleEntity )( cl_entity_t *pEntity ), void( **pCallback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ) );
void HUD_AddEntity (int type, struct cl_entity_s *ent, const char *modelname);
void HUD_Key_Event( int eventcode, int keynum, const char *pszCurrentBinding );