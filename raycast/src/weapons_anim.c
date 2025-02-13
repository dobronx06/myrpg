/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** weapons_anim.c
*/

#include "../include/my.h"

static void reset_sprite(weapon_t *weapon, sfIntRect rect)
{
    weapon->rect = rect;
    weapon->state = READY;
    sfClock_restart(weapon->clock);
}

static void animate_pistol(game_t *data)
{
    float seconds;
    weapon_t *pistol = data->current_weapon;

    if (pistol->state != FIRING)
        return;
    seconds = sfTime_asSeconds(sfClock_getElapsedTime(pistol->clock));
    if (seconds > 0)
        pistol->rect = (sfIntRect){60, 0, 80, 103};
    if (seconds > 0.10)
        pistol->rect = (sfIntRect){140, 0, 66, 103};
    if (seconds > 0.17)
        pistol->rect = (sfIntRect){210, 0, 62, 103};
    if (seconds > 0.24)
        pistol->rect = (sfIntRect){280, 0, 70, 103};
    if (seconds > 0.31)
        reset_sprite(pistol, (sfIntRect){0, 0, 60, 103});
    sfSprite_setTextureRect(pistol->sprite, pistol->rect);
}

static void animate_fist(game_t *data)
{
    float seconds;
    weapon_t *fist = data->current_weapon;

    if (fist->state != FIRING)
        return;
    seconds = sfTime_asSeconds(sfClock_getElapsedTime(fist->clock));
    if (seconds > 0)
        fist->rect = (sfIntRect){112, 0, 82, 75};
    if (seconds > 0.1)
        fist->rect = (sfIntRect){194, 0, 110, 75};
    if (seconds > 0.15)
        fist->rect = (sfIntRect) {302, 0, 150, 75};
    if (seconds > 0.3)
        reset_sprite(fist, (sfIntRect){0, 0, 112, 75});
    sfSprite_setTextureRect(fist->sprite, fist->rect);
}

static void animate_shotgun(game_t *data)
{
    float seconds;
    weapon_t *shotgun = data->current_weapon;

    if (shotgun->state != FIRING)
        return;
    seconds = sfTime_asSeconds(sfClock_getElapsedTime(shotgun->clock));
    if (seconds > 0)
        shotgun->rect = (sfIntRect){85, 0, 83, 150};
    if (seconds > 0.1)
        shotgun->rect = (sfIntRect){174, 0, 82, 150};
    if (seconds > 0.2)
        shotgun->rect = (sfIntRect){250, 0, 128, 150};
    if (seconds > 0.3)
        shotgun->rect = (sfIntRect){376, 0, 90, 150};
    if (seconds > 0.4)
        shotgun->rect = (sfIntRect){466, 0, 115, 150};
    if (seconds > 0.6)
        reset_sprite(shotgun, (sfIntRect){0, 0, 83, 150});
    sfSprite_setTextureRect(shotgun->sprite, shotgun->rect);
}

void update_anims(game_t *data)
{
    animate_mobs(data->engine);
    switch (data->current_weapon->type) {
        case PISTOL:
            animate_pistol(data);
            break;
        case SHOTGUN:
            animate_shotgun(data);
            break;
        case FIST:
            animate_fist(data);
            break;
        default:
            break;
    }
}
