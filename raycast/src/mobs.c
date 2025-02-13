/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** mobs.c
*/

#include "../include/my.h"

static void which_texture(engine_t *data, int i, sfTexture **texture)
{
    if (data->sprites[i].texture == 1) {
        *texture =
            sfTexture_createFromFile("raycast/assets/mob1_base.png", NULL);
        sfSprite_setTexture(data->sprites[i].sprite, *texture, sfTrue);
    }
    if (data->sprites[i].texture == 2) {
        *texture =
            sfTexture_createFromFile("raycast/assets/mob3_base.png", NULL);
        sfSprite_setTexture(data->sprites[i].sprite, *texture, sfTrue);
    }
}

static void init_mobs2(engine_t *data)
{
    sfTexture *texture;
    sfSoundBuffer *buffer =
        sfSoundBuffer_createFromFile("raycast/assets/sounds/patate.ogg");

    for (int i = 0; i < NUMSPRITES; i++) {
        which_texture(data, i, &texture);
        sfSprite_setTextureRect(
            data->sprites[i].sprite, data->sprites[i].rect);
        data->sprites[i].image = sprite_to_img(data->sprites[i].sprite);
        data->spriteOrder[i] = i;
        data->spriteDistance[i] = 0;
        sfSound_setBuffer(data->sprites[i].attack_sfx, buffer);
    }
}

void init_mobs(engine_t *data)
{
    sfSound *sound = sfSound_create();

    data->sprites[0] = (mob_t){2.5, 21.5, 1, 0, 1, 100, 100, true,
    false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.5, 21.5,
        (sfIntRect){0, 0, 85, 100}, 100, 400, sfClock_create(),
            sfSprite_create(), NULL, sound};
    data->sprites[1] = (mob_t){5.5, 5.5, 2, 0, 2, 100, 100, true,
    false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.5, 5.5,
        (sfIntRect){0, 0, 85, 100}, 100, 400, sfClock_create(),
            sfSprite_create(), NULL, sound};
    data->sprites[2] = (mob_t){15, 12, 2, 0, 3, 100, 100, true,
    false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 12,
        (sfIntRect){0, 0, 85, 100}, 100, 400, sfClock_create(),
            sfSprite_create(), NULL, sound};
    data->sprites[3] = (mob_t){4, 15, 1, 0, 4, 100, 100, true,
    false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 15,
        (sfIntRect){0, 0, 85, 100}, 100, 400, sfClock_create(),
            sfSprite_create(), NULL, sound};
    init_mobs2(data);
}

mob_t *find_mob_coords(engine_t *data, int x, int y)
{
    for (int i = 0; i < NUMSPRITES; i++) {
        if ((int)data->sprites[i].x == x && (int)data->sprites[i].y == y)
            return &data->sprites[i];
    }
    return NULL;
}

void sort_sprites(engine_t *data)
{
    for (int i = 0; i < NUMSPRITES; i++) {
        data->spriteOrder[i] = i;
        data->spriteDistance[i] = ((data->posX - data->sprites[i].x) *
            (data->posX - data->sprites[i].x) + (data->posY -
                data->sprites[i].y) * (data->posY - data->sprites[i].y));
    }
}

static int partition(engine_t *data, int low, int high)
{
    mob_t *mobs = data->sprites;
    float pivot = mobs[data->spriteOrder[high]].dist;
    int temp;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (mobs[data->spriteOrder[j]].dist >= pivot) {
            i++;
            temp = data->spriteOrder[i];
            data->spriteOrder[i] = data->spriteOrder[j];
            data->spriteOrder[j] = temp;
        }
    }
    temp = data->spriteOrder[i + 1];
    data->spriteOrder[i + 1] = data->spriteOrder[high];
    data->spriteOrder[high] = temp;
    return i + 1;
}

static void quick_sort(engine_t *data, int low, int high)
{
    int pi;

    if (low < high) {
        pi = partition(data, low, high);
        quick_sort(data, low, pi - 1);
        quick_sort(data, pi + 1, high);
    }
}

void sort_mobs(engine_t *data, int amount)
{
    mob_t *mobs = data->sprites;
    mob_t sorted_mobs[NUMSPRITES];

    for (int i = 0; i < amount; i++) {
        mobs[i].dist = ((data->posX - mobs[i].x) * (data->posX - mobs[i].x) +
            (data->posY - mobs[i].y) * (data->posY - mobs[i].y));
        data->spriteOrder[i] = i;
    }
    quick_sort(data, 0, amount - 1);
    for (int i = 0; i < amount; i++) {
        data->spriteDistance[i] = mobs[data->spriteOrder[i]].dist;
        sorted_mobs[i] = mobs[data->spriteOrder[i]];
    }
    for (int i = 0; i < amount; i++)
        mobs[i] = sorted_mobs[i];
}
