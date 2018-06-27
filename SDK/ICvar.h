#pragma once

class ConVar
{
public:
    
    float GetFloat()
    {
        typedef float (* oGetFloat)(void*);
        return getvfunc<oGetFloat>(this, 15)(this);
    }
    
    int GetInt()
    {
        typedef int (* oGetInt)(void*);
        return getvfunc<oGetInt>(this, 16)(this);
    }
    
    void SetValue(const char* value)
    {
        typedef void (* oSetValue)(void*, const char*);
        return getvfunc<oSetValue>(this, 17)(this, value);
    }
    
    void SetValue(float value)
    {
        typedef void (* oSetValue)(void*, float);
        return getvfunc<oSetValue>(this, 18)(this, value);
    }
    
    void SetValue(int value)
    {
        typedef void (* oSetValue)(void*, int);
        return getvfunc<oSetValue>(this, 19)(this, value);
    }
    
    void SetValue(Color value)
    {
        typedef void (* oSetValue)(void*, Color);
        return getvfunc<oSetValue>(this, 20)(this, value);
    }
    
    char    pad_0x0000[0x4];    //0x0000
    ConVar* pNext;              //0x0004
    int32_t bRegistered;        //0x0008
    char*   pszName;            //0x000C
    char*   pszHelpString;      //0x0010
    int32_t nFlags;             //0x0014
    char    pad_0x0018[0x4];    //0x0018
    ConVar* pParent;            //0x001C
    char*   pszDefaultValue;    //0x0020
    char*   strString;          //0x0024
    int32_t StringLength;       //0x0028
    float   fValue;             //0x002C
    int32_t nValue;             //0x0030
    int32_t bHasMin;            //0x0034
    float   fMinVal;            //0x0038
    int32_t bHasMax;            //0x003C
    float   fMaxVal;            //0x0040
    void*   fnChangeCallback;   //0x0044
    
};


class ICvar
{
public:
    
    ConVar* FindVar(const char *var)
    {
        typedef ConVar* (* oFindVar)(void*, const char*);
        return getvfunc<oFindVar>(this, 15)(this, var);
    }
    
    template <typename... Values>
    void ConsoleColorPrintf(const Color& MsgColor, const char* szMsgFormat, Values... Parameters)
    {
        typedef void (* oConsoleColorPrintf)(void*, const Color&, const char*, ...);
        return getvfunc<oConsoleColorPrintf>(this, 25)(this, MsgColor, szMsgFormat, Parameters...);
    }
    
    template <typename... Values>
    void ConsoleDPrintf(const char* szMsgFormat, Values... Parameters)
    {
        typedef void (* oConsoleDPrintf)(void*, const char*, ...);
        return getvfunc<oConsoleDPrintf>(this, 27)(this, szMsgFormat, Parameters...);
    }
    
};

#define FORCEINLINE_CVAR
#pragma region CVAR Flags
#define FCVAR_NONE                      0
#define FCVAR_UNREGISTERED              (1<<0)    // If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY           (1<<1)    // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL                   (1<<2)    // defined by the game DLL
#define FCVAR_CLIENTDLL                 (1<<3)  // defined by the client DLL
#define FCVAR_HIDDEN                    (1<<4)    // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

// ConVar only
#define FCVAR_PROTECTED                 (1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY                    (1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define   FCVAR_ARCHIVE                 (1<<7)    // set to cause it to be saved to vars.rc
#define   FCVAR_NOTIFY                  (1<<8)    // notifies players when changed
#define   FCVAR_USERINFO                (1<<9)    // changes the client's info string
#define FCVAR_CHEAT                     (1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define FCVAR_PRINTABLEONLY             (1<<10)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED                  (1<<11)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING           (1<<12)  // never try to print that cvar

// It's a ConVar that's shared between the client and the server.
// At signon, the values of all such ConVars are sent from the server to the client (skipped for local
//  client, of course )
// If a change is requested it must come from the console (i.e., no remote client changes)
// If a value is changed while a server is active, it's replicated to all connected clients
#define FCVAR_REPLICATED                (1<<13)   // server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_DEMO                      (1<<16)  // record this cvar when starting a demo file
#define FCVAR_DONTRECORD                (1<<17)  // don't record these command in demofiles

#define FCVAR_NOT_CONNECTED             (1<<22)   // cvar cannot be changed by a client that is connected to a server

#define FCVAR_ARCHIVE_XBOX              (1<<24) // cvar written to config.cfg on the Xbox

#define FCVAR_SERVER_CAN_EXECUTE        (1<<28)// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY       (1<<29)// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE     (1<<30)   // IVEngineClient::ClientCmd is allowed to execute this command.
#pragma endregion
