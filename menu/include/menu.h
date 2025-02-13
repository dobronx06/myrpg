/*
** EPITECH PROJECT, 2023
** B-PSU-100-MPL-1-1-sokoban-matteo.chapelle-esmel
** File description:
** my.h
*/

#pragma once

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <SFML/Graphics.h>
#include <stdbool.h>
#include <SFML/Window.h>
#include <math.h>
#include <pthread.h>
#include <SFML/Audio.h>

typedef struct bouton_s {
    sfSprite *spriteBouton;
    sfTexture *textureBouton;
    sfTexture *textureSecondBouton;
    sfVector2f textPos;
    sfVector2f posBouton;
    sfVector2f sizeBouton;
    sfFloatRect boundsBouton;
    int id;
    struct bouton_s *nextbouton;
} bouton_t;

typedef struct menu_s {
    bouton_t *button_menu;
    bouton_t *button_settings;
    bouton_t *button_credits;
    bouton_t *button_pause;
    int current_scene;
    bouton_t *cur_buttons;
    sfSprite *spriteBg;
    sfTexture *textureBg;
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    int wSizeX;
    int wSizeY;
    sfVector2u windowSize;
    float bgScaleX;
    float bgScaleY;
    sfMusic *music;
    sfSprite *spriteSlider;
    sfTexture *textureSlider;
    sfRectangleShape *knob;
    sfBool isPressed;
    sfUint32 style;
} menu_t;

void display_buttons(sfRenderWindow *, bouton_t *, menu_t *);
void create_and_add_button(bouton_t **head,
    sfVector2f pos, sfVector2f size, char *text);
bouton_t *create_button(void);
void add_button(bouton_t **head, bouton_t *new_button);
bouton_t *init_bouton(bouton_t *new_button, const char *texturePathPrefix,
    sfVector2f pos, sfVector2f size);
void create_all_button(menu_t *menu);
void handle_event(sfEvent *event, menu_t *menu);
void resize(menu_t *menu, sfEvent *event);
void create_button_reglage(menu_t *menu);
void init_slider(menu_t *menu);
int first_map(sfRenderWindow *window);
