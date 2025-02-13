/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dilema
*/

#pragma once

#include <SFML/Graphics.h>

typedef struct spec_s {
    int malus;
    char *desc;
    sfRectangleShape *hitbox;
} spec_t;

typedef struct dilema_s {
    char *title;
    sfTexture *texture;
    sfSprite *background;
    spec_t *spec_left;
    spec_t *spec_right;
} dilema_t;
