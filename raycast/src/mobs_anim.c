/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** mobs_anim.c
*/

#include "../include/my.h"

void animate_mobs(engine_t *data)
{
    float seconds;

    for (int i = 0; i < NUMSPRITES; i++) {
        if (!data->sprites[i].is_alive)
            continue;
        seconds = sfTime_asSeconds(
            sfClock_getElapsedTime(data->sprites[i].clock));
        if (seconds > 0.2) {
            data->sprites[i].rect.top += data->sprites[i].offset;
            data->sprites[i].rect.top =
                (data->sprites[i].rect.top >= data->sprites[i].offset_max) ? 0
                    : data->sprites[i].rect.top;
            sfSprite_setTextureRect(data->sprites[i].sprite,
                data->sprites[i].rect);
            data->sprites[i].image =
                sprite_to_image(data->sprites[i].sprite,
                data->sprites[i].rect);
            sfClock_restart(data->sprites[i].clock);
        }
    }
}

sfImage *sprite_to_image(sfSprite *sprite, sfIntRect textureRect)
{
    sfColor color;
    const sfTexture *texture = sfSprite_getTexture(sprite);
    sfImage *fullImage = sfTexture_copyToImage(texture);
    sfImage *rectImage = sfImage_create(textureRect.width, textureRect.height);

    for (int i = 0; i < textureRect.width; i++) {
        for (int j = 0; j < textureRect.height; j++) {
            color = sfImage_getPixel(fullImage,
                textureRect.left + i, textureRect.top + j);
            sfImage_setPixel(rectImage, i, j, color);
        }
    }
    sfImage_destroy(fullImage);
    return rectImage;
}

sfImage *sprite_to_img(sfSprite *sprite)
{
    const sfTexture *texture = sfSprite_getTexture(sprite);
    sfImage *image = sfTexture_copyToImage(texture);

    return image;
}

sfSprite *img_to_sprite(sfImage *image)
{
    sfTexture *texture = sfTexture_createFromImage(image, NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}
