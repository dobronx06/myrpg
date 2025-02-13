/*
** EPITECH PROJECT, 2024
** raycast
** File description:
** sprites.c
*/

#include "../include/my.h"

sfImage *create_image(char *filepath)
{
    sfImage *image = sfImage_createFromFile(filepath);

    return image;
}

void init_textures(engine_t *buff)
{
    buff->textures = malloc(sizeof(texture_t) * NB_TEXTURES);
    buff->textures[0].image = create_image("raycast/assets/wall4.png");
    buff->textures[1].image = create_image("raycast/assets/floor2.png");
    buff->textures[2].image = create_image("raycast/assets/muress.png");
    buff->textures[3].image = create_image("raycast/assets/purplestone.png");
    buff->textures[4].image = create_image("raycast/assets/mossy.png");
    buff->textures[5].image = create_image("raycast/assets/plafond.jpg");
    buff->textures[6].image = create_image("raycast/assets/colorstone.png");
    buff->textures[7].image = create_image("raycast/assets/portress.png");
}
