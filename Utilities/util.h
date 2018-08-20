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

bool world_to_screen(Vector& in, Vector& out);

bool is_point_visible(Vector point);
bool is_player_visible(C_BasePlayer* player);
bool is_hitbox_visible(C_BasePlayer* player, int hitbox);

bool get_box(C_BaseEntity* pEntity, box_t& box);

long timestamp();

Color imvec_to_color(ImVec4 col, bool alpha = false);

string get_weapon_name(C_BaseCombatWeapon* weapon);

C_BaseCombatWeapon* get_active_weapon(C_BasePlayer* player);

