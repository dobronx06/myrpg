/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** init_weapons.c
*/

#include "../include/my.h"

static void init_pistol_properties(weapon_t *weapons)
{
    weapons->name = strdup("Pistol");
    weapons->state = READY;
    weapons->type = PISTOL;
    weapons->damage = 30;
    weapons->ammo = 20;
    weapons->clock = sfClock_create();
    weapons->shot_sound = sfSound_create();
    sfSound_setBuffer(weapons->shot_sound,
        sfSoundBuffer_createFromFile("raycast/assets/sounds/pistol_shot.wav"));
}

static void init_pistol_sprite(weapon_t *weapons, game_t *data)
{
    sfVector2u windowSize = sfRenderWindow_getSize(data->engine->window);
    sfVector2f spritePosition;
    sfFloatRect spriteBounds;

    weapons->sprite = sfSprite_create();
    weapons->texture =
        sfTexture_createFromFile("raycast/assets/gun_default.png", NULL);
    weapons->rect = (sfIntRect){0, 0, 57, 103};
    sfSprite_setTexture(weapons->sprite,
        weapons->texture, sfTrue);
    sfSprite_setTextureRect(weapons->sprite, weapons->rect);
    sfSprite_setScale(weapons->sprite, (sfVector2f){2.5 * windowSize.x / 1920,
        2.5 * windowSize.x / 1920});
    spriteBounds = sfSprite_getGlobalBounds(weapons->sprite);
    spritePosition = (sfVector2f){(windowSize.x - spriteBounds.width) / 2,
        (windowSize.y - spriteBounds.height)};
    sfSprite_setPosition(weapons->sprite, spritePosition);
}

static void init_fist_sprite(weapon_t *weapons, game_t *data)
{
    sfVector2u windowSize = sfRenderWindow_getSize(data->engine->window);
    sfVector2f spritePosition;
    sfFloatRect spriteBounds;

    weapons->sprite = sfSprite_create();
    weapons->texture =
        sfTexture_createFromFile("raycast/assets/fist_default.png", NULL);
    weapons->rect = (sfIntRect){0, 0, 112, 75};
    sfSprite_setTexture(weapons->sprite,
        weapons->texture, sfTrue);
    sfSprite_setTextureRect(weapons->sprite, weapons->rect);
    sfSprite_setScale(weapons->sprite, (sfVector2f){2.5 * windowSize.x / 1920,
        2.5 * windowSize.x / 1920});
    spriteBounds = sfSprite_getGlobalBounds(weapons->sprite);
    spritePosition = (sfVector2f){(windowSize.x - spriteBounds.width) / 2 + 80,
        (windowSize.y - spriteBounds.height)};
    sfSprite_setPosition(weapons->sprite, spritePosition);
}

static void init_fist_properties(weapon_t *weapons)
{
    weapons->name = strdup("Fist");
    weapons->state = READY;
    weapons->type = FIST;
    weapons->damage = 10;
    weapons->ammo = 0;
    weapons->clock = sfClock_create();
    weapons->shot_sound = sfSound_create();
    sfSound_setBuffer(weapons->shot_sound,
        sfSoundBuffer_createFromFile("raycast/assets/sounds/fist_hit.wav"));
}

static void init_shotgun_properties(weapon_t *weapons)
{
    weapons->name = strdup("Shotgun");
    weapons->state = READY;
    weapons->type = SHOTGUN;
    weapons->damage = 50;
    weapons->ammo = 10;
    weapons->clock = sfClock_create();
    weapons->shot_sound = sfSound_create();
    sfSound_setBuffer(weapons->shot_sound,
        sfSoundBuffer_createFromFile
        ("raycast/assets/sounds/shotgun_shot.wav"));
}

static void init_shotgun_sprite(weapon_t *weapons, game_t *data)
{
    sfVector2u windowSize = sfRenderWindow_getSize(data->engine->window);
    sfVector2f spritePosition;
    sfFloatRect spriteBounds;

    weapons->sprite = sfSprite_create();
    weapons->texture =
        sfTexture_createFromFile("raycast/assets/shotgun_default.png", NULL);
    weapons->rect = (sfIntRect){0, 0, 82, 150};
    sfSprite_setTexture(weapons->sprite,
        weapons->texture, sfTrue);
    sfSprite_setTextureRect(weapons->sprite, weapons->rect);
    sfSprite_setScale(weapons->sprite, (sfVector2f){2.5 * windowSize.x / 1920,
        2.5 * windowSize.x / 1920});
    spriteBounds = sfSprite_getGlobalBounds(weapons->sprite);
    spritePosition = (sfVector2f){(windowSize.x - spriteBounds.width) / 2,
        (windowSize.y - spriteBounds.height)};
    sfSprite_setPosition(weapons->sprite, spritePosition);
}

void init_weapons(weapon_t **weapons, game_t *data)
{
    data->index_weapon = 0;
    weapons[0] = malloc(sizeof(weapon_t));
    weapons[1] = malloc(sizeof(weapon_t));
    weapons[2] = malloc(sizeof(weapon_t));
    init_fist_properties(weapons[0]);
    init_fist_sprite(weapons[0], data);
    init_pistol_properties(weapons[1]);
    init_pistol_sprite(weapons[1], data);
    init_shotgun_properties(weapons[2]);
    init_shotgun_sprite(weapons[2], data);
}
