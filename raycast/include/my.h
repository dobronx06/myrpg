/*
** EPITECH PROJECT, 2023
** B-PSU-100-MPL-1-1-sokoban-matteo.chapelle-esmel
** File description:
** my.h
*/

#pragma once

#include "dilema.h"
#include "quest.h"
#include "weapons.h"
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
#include <SFML/System.h>
#include <SFML/Audio.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>

#define SIDE_X 0
#define SIDE_Y 1

#define UDIV 1
#define VDIV 1
#define VMOVE 0.0
#define NB_TEXTURES 8
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define NUMSPRITES 4

typedef enum {
    PLAYING,
    DILEMMA,
    PAUSE,
    END
} game_state_t;

typedef struct mob_s {
    double x;
    double y;
    int texture;
    double dist;
    int id;
    int initial_health;
    int health;
    bool is_alive;
    bool is_visible;
    int stPosX;
    int stPosY;
    int ePosX;
    int ePosY;
    int dltX;
    int dltY;
    int spX;
    int spY;
    int error;
    int doubleError;
    double startX;
    double startY;
    sfIntRect rect;
    int offset;
    int offset_max;
    sfClock *clock;
    sfSprite *sprite;
    sfImage *image;
    sfSound *attack_sfx;
} mob_t;

typedef struct texture_s {
    sfImage *image;
} texture_t;

typedef struct engine_s {
    int wSizex;
    int wSizey;
    sfClock *clock;
    double cameraX;
    double rayDirX;
    double rayDirY;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double oldPlaneX;
    double oldDirX;
    double planeX;
    double planeY;
    double newX;
    double newY;
    double sideDistX;
    double sideDistY;
    double deltaDistY;
    double deltaDistX;
    sfVideoMode mode;
    sfRenderWindow *window;
    double mSpeed;
    double rSpeed;
    double invScreenWidth;
    double invScreenHeight;
    double perpWallDist;
    int mapX;
    int mapY;
    int stepX;
    int stepY;
    int hit;
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    sfColor color;
    sfVertex line[2];
    int worldMap[MAP_WIDTH][MAP_HEIGHT];
    texture_t *textures;
    sfUint8 *wPxl;
    sfUint8 *fcPxl;
    sfUint8 *pixels;
    sfUint8 *mob_pixels;
    sfTexture *texture;
    sfSprite *sprite;
    double dt;
    sfVector2i lastMousePos;
    double rotationAngle;
    sfSprite *crosshair;
    float rayDirX0;
    float rayDirY0;
    float rayDirX1;
    float rayDirY1;
    float floorStepX;
    float floorStepY;
    int cellX;
    int cellY;
    int tx;
    int ty;
    mob_t sprites[NUMSPRITES];
    double ZBuffer[SCREEN_WIDTH];
    int spriteOrder[NUMSPRITES];
    double spriteDistance[NUMSPRITES];
    double spriteX;
    double spriteY;
    double transformX;
    double transformY;
    long spriteScreenX;
    long vMoveScreen;
    long drawStartY;
    long drawEndY;
    long drawStartX;
    long drawEndX;
    int spriteHeight;
    int spriteWidth;
} engine_t;

typedef struct pause_s {
    char *title;
    sfText *title_tx;
    sfRectangleShape *background;
    bool open;
} pause_t;

typedef struct player_s {
    int health;
    int malus;
    sfRectangleShape* outline;
    sfRectangleShape* life_bar;
} player_t;

typedef struct game_s {
    sfEvent event;
    quest_t **quests;
    engine_t *engine;
    weapon_t **weapons;
    int index_weapon;
    weapon_t *current_weapon;
    player_t *player;
    dilema_t *dilema;
    pause_t *pause;
    game_state_t state;
} game_t;

typedef struct bullet_param_s {
    float posX;
    float posY;
    float dirX;
    float dirY;
    int mapX;
    int mapY;
    float sideDistX;
    float sideDistY;
    float deltaDistX;
    float deltaDistY;
    int stepX;
    int stepY;
    int hit;
} bullet_param_t;

char *int_to_char(int, int);
void calculate_step_and_side_dist(engine_t *);
void perform_dda(engine_t *);
void init_textures(engine_t *);
void init_struct(game_t *, sfRenderWindow *);
void init_struct3(engine_t *);
void clear_buffer(sfUint8 *, engine_t *);
void calculate_distance_and_draw_to_buffer(engine_t *, int);
void cast_floor_and_ceiling(engine_t *);
void events_rayc(game_t *);
void close_game(game_t *);
void handle_pistol(game_t *);
void handle_shotgun(game_t *);
void sort_sprites(engine_t *);
void sort_mobs(engine_t *, int);
mob_t *find_mob_coords(engine_t *, int, int);
void init_mobs(engine_t *);
void draw_sprites(engine_t *, quest_t *, player_t *, int *);
bool can_see_player(engine_t *, mob_t *);
void view_mobs(engine_t *, mob_t *, int);
void update_mobs(engine_t *, quest_t *, player_t *);
void already_killed(quest_t *, int);
sfColor apply_fog(sfColor c, float, int);
sfImage *sprite_to_img(sfSprite *);
void animate_mobs(engine_t *);
sfImage *sprite_to_image(sfSprite *, sfIntRect);
void handle_choice(game_t *);
void handle_pause(game_t *);
void update_mob_state(engine_t *data, int i);
void attack_mobs(engine_t *data, player_t *player, int i);
void already_killed(quest_t *quest, int id);
