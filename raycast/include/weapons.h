/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** weapons.h
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "my.h"

typedef struct game_s game_t;

typedef enum state_s {
    READY = 0,
    RELOADING,
    FIRING,
    NONE,
} state_t;

typedef enum types_s {
    SHOTGUN = 0,
    PISTOL,
    FIST,
} types_t;

typedef struct weapon_s {
    char *name;
    state_t state;
    types_t type;
    int damage;
    int ammo;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfClock *clock;
    sfTime time;
    sfSound *shot_sound;
} weapon_t;

typedef struct weapons_list_s {
    weapon_t *pistol;
    weapon_t *shotgun;
    weapon_t *fist;
} weapons_list_t;

void init_weapons(weapon_t **, game_t *);
void update_anims(game_t *);
