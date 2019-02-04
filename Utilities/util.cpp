/*      util.cpp
 *
 *
 *
 */
#include "main.h"
#include "util.h"
#include "util_math.h"

void print(string str, Color col, string prefix)
{
    if(!pCvar)
        return;
    
    prefix = "[" + prefix + "] ";
    pCvar->ConsoleColorPrintf(col, prefix.c_str());
    pCvar->ConsoleDPrintf("%s\n", str.c_str());
}

bool world_to_screen(Vector& in, Vector& out)
{
    return !pOverlay->ScreenPosition(in, out);
}

bool is_point_visible(Vector point)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::localplayer;
    
    ray.Init(Global::localplayer->GetEyePosition(), point);
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.fraction > 0.97f);
}

bool is_player_visible(C_BasePlayer* entity)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::localplayer;
    
    ray.Init(Global::localplayer->GetEyePosition(), entity->GetEyePosition());
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

bool is_hitbox_visible(C_BasePlayer* player, int hitbox)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::localplayer;
    
    ray.Init(Global::localplayer->GetEyePosition(), get_hitbox_position(player, hitbox));
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == player || trace.fraction > 0.99f);
}

// Credit's to dude719 & keybode
bool get_box(C_BaseEntity* pEntity, box_t& box)
{
    if (!pEntity)
        return false;
    
    Vector vOrigin = pEntity->GetVecOrigin();
    Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] =
    {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(max.x, max.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(min.x, min.y, max.z),
        Vector(max.x, min.y, max.z)
    };
    
    Vector flb; // flb = front-left-bottom
    Vector brt; // brt = back-right-top
    Vector blb; // blb = back-left-bottom
    Vector frt; // frt = front-right-top
    Vector frb; // frb = front-right-bottom
    Vector brb; // brb = back-right-bottom
    Vector blt; // blt = back-left-top
    Vector flt; // flt = front-left-top
    
    
    if (!world_to_screen(points[0], blb) || !world_to_screen(points[1], brb) || !world_to_screen(points[2], frb) || !world_to_screen(points[3], flb) ||
        !world_to_screen(points[4], frt) || !world_to_screen(points[5], brt) || !world_to_screen(points[6], blt) || !world_to_screen(points[7], flt))
        return false;
    
    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left   = flb.x;   // left
    float top    = flb.y;   // top
    float right  = flb.x;   // right
    float bottom = flb.y;   // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    box.x = left;
    box.y = top;
    box.w = right - left;
    box.h = bottom - top;
    return true;
}

long timestamp()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

Color imvec_to_color(ImVec4 col, bool alpha)
{
    return Color(col.x * 255, col.y * 255, col.z * 255, alpha ? col.w * 255 : 255);
}

C_BaseCombatWeapon* get_active_weapon(C_BasePlayer* player)
{
    void* weaponHandle = player->GetActiveWeapon();
    
    if (!weaponHandle)
        return nullptr;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(weaponHandle);
}

/*
 *  get_weapon_name
 *  Returns the name of the given weapon
 */
string get_weapon_name(C_BaseCombatWeapon* weapon)
{
    if(!weapon)
        return "Knife";
    
    int id = *weapon->GetItemDefinitionIndex();
    
    if(!id)
        return "Error";
    
    switch (id)
    {
            /* pistols */
        case 4:
            return "Glock";
        case 2:
            return "Dualies";
        case 36:
            return "P250";
        case 30:
            return "Tec 9";
        case 1:
            return "Deagle";
        case 32:
            return "P2000";
        case 3:
            return "Five Seven";
        case 64:
            return "Revolver";
        case 63:
            return "CZ75";
        case 61:
            return "USP";
            
            /*heavy*/
        case 35:
            return "Nova";
        case 25:
            return "XM1014";
        case 29:
            return "Sawed Off";
        case 14:
            return "M249";
        case 28:
            return "Negev";
        case 27:
            return "Mag 7";
            
            /*smgs*/
        case 17:
            return "Mac 10";
        case 33:
            return "MP7";
        case 23:
            return "MP5";
        case 24:
            return "UMP45";
        case 19:
            return "P90";
        case 26:
            return "Bizon";
        case 34:
            return "MP9";
            
            /*rifles*/
        case 10:
            return "Famas";
        case 16:
            return "M4A1";
        case 40:
            return "Scout";
        case 8:
            return "AUG";
        case 9:
            return "AWP";
        case 38:
            return "Scar 20";
        case 13:
            return "Galil";
        case 7:
            return "AK47";
        case 39:
            return "SG553";
        case 11:
            return "G3SG1";
        case 60:
            return "M4A1-S";
            
            /*grenades*/
        case 46:
        case 48:
            return "Molotov";
        case 44:
            return "Grenade";
        case 43:
            return "Flash";
        case 45:
            return "Smoke";
        case 47:
            return "Decoy";
            
            /*other*/
        case 31:
            return "Zeus";
        case 49:
            return "Bomb";
        default:
            return "Knife";
    }
}

char* C_BasePlayer::GetName()
{
    player_info_t info;
    pEngine->GetPlayerInfo(this->GetIndex(), &info);
    return (char*)info.name;
}
