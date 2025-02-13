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
#include "../../menu/include/menu.h"

#define NUM_ITEMS 4
#define NUM_SLOTS 30

typedef struct slot_s {
    sfRectangleShape *shape;
    int occupied;
} slot_t;

typedef struct item_s {
    sfSprite *sprite;
    sfVector2f original_position;
    int being_dragged;
} item_t;

typedef struct {
    sfRectangleShape *rect;
    sfVector2f position;
    sfVector2f size;
} rectangle_t;

typedef struct {
    rectangle_t *rect;
    int debug;
} collisions_t;

typedef struct text_s {
    sfFont *font;
    sfText *texts[3];
    sfClock *clock;
    float delay;
    const char *strings[3];
    char currentTexts[3][256];
    size_t currentLengths[3];
    int activeText;
    int nbrtext;
} text_t;

typedef struct game_s {
    sfView *view;
    sfEvent event;
    sfSprite *player;
    sfSprite *narrator;
    sfTexture *texture_narrator;
    sfTexture *texture_player;
    item_t *items;
    slot_t slots[30];
    sfIntRect rect_down;
    sfIntRect rect_up;
    sfIntRect rect_right;
    sfIntRect rect_left;
    collisions_t *collisions;
    sfRenderWindow *window;
    sfVideoMode mode;
    sfClock *clock;
    sfText *textsf;
    int scene;
    text_t *text;
    sfFont *font;
    sfSprite *sprite;
    sfSprite *inventory;
    sfSprite *background;
    sfTexture *texture_sprite;
    sfTexture *texture_inventory;
    sfTexture *texture_background;
    sfSprite *dialogue_line;
    sfTexture *texture_dialogue_line;
    sfSprite *mini_cake;
    sfTexture *texture_mini_cake;
    int get_cake;
    sfSprite *questmark;
    sfTexture *texture_questmark;
    sfSprite *over;
    sfTexture *texture_over;
    menu_t *menu;
    sfSprite *textbox2;
    sfTexture *texture_textbox2;
} game_t;

void handle_inventory(game_t *game, item_t **dragging_item);
void handle_drag_and_drop(game_t *game, item_t **dragging_item);
void init_structs(game_t *game, const char *item_files[],
    sfRenderWindow *window);
void move_rect_down(game_t *data, sfSprite *sprite);
void move_rect_up(game_t *data, sfSprite *sprite);
void move_rect_right(game_t *data, sfSprite *sprite);
void move_rect_left(game_t *data, sfSprite *sprite);
void set_col(collisions_t *col);
bool check_collisions(collisions_t *col, sfSprite *player);
float custom_abs(float x);
int write_func(const char **strings, int nbrtext, game_t *data,
    int *scene);
void outside_map(game_t *game, sfRenderWindow *window);
void draw_and_display(game_t *game, int *i);
void draw_text(game_t *data, sfText *text, const char *strings[3], int i);
double custom_sqrt(double x);
float custom_pow(float x, float y);
float custom_abs(float x);
float calculate_distance(sfVector2i mouse_pos, sfVector2f slot_pos);
void evt_button_pressed(game_t *game, item_t **dragging_item,
    sfVector2f *offset, int *previous_slot);
void evt_button_released(game_t *game, item_t **dragging_item,
    int *previous_slot);
void dialogue_crow(game_t *game, int *i);
void draw_text(game_t *data, sfText *text, const char *strings[3], int i);
int raycasting(sfRenderWindow *window);
void draw_pause(game_t *data);
