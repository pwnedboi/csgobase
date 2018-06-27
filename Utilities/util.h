/*
 *  util.h
 */
#pragma once

#define ARRSIZE(arr)            (sizeof(arr) / sizeof(*arr))
#define IMPL_HOOK(hook)          static bool o; if(!o) { print(string(hook) + " hooked", Color::Orange()); o = true; }

struct box_t
{
    int x, y, w, h;
};

void print(string str, Color col = Color::PastelPink(), string prefix = "debug");

bool WorldToScreen(Vector& in, Vector& out);

bool IsPointVisible(Vector point);
bool IsPlayerVisible(C_BasePlayer* entity);
bool IsHitboxVisible(C_BasePlayer* player, int hitbox);

bool get_box(C_BaseEntity* pEntity, box_t& box);

long get_timestamp();

Color ImVecToColor(ImVec4 col, bool alpha = false);

string GetWeaponName(C_BaseCombatWeapon* weapon);

C_BaseCombatWeapon* GetActiveWeapon(C_BasePlayer* player);

