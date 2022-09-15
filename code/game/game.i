%module game
%{
#include "g_local.h"
%}

%ignore Hunk_AllocDebug;
%ignore Q_acos;
%ignore Com_RandomBytes;
%ignore UseHoldableItem;
%ignore PrecacheItem;
%ignore SetRespawn;
%ignore Think_Weapon;
%ignore ArmorIndex;
%ignore G_InvulnerabilityEffect;
%ignore TossClientCubes;
%ignore CheckObeliskAttack;
%ignore g_obeliskHealth;
%ignore g_obeliskRegenPeriod;
%ignore g_obeliskRegenAmount;
%ignore g_obeliskRespawnDelay;
%ignore g_cubeTimeout;
%ignore g_redteam;
%ignore g_blueteam;
%ignore g_enableDust;
%ignore g_enableBreath;
%ignore g_singlePlayer;
%ignore g_proxMineTimeout;
%ignore trap_Args;

#define Q3_VM
%include "../qcommon/q_platform.h"
%include "../qcommon/q_shared.h"
#undef MAX_GENTITIES
#define MAX_GENTITIES 1024

%include "g_local.h"
