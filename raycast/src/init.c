/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init
*/

#include "../include/my.h"

static pause_t *init_pause(sfVideoMode *desktop_size)
{
    pause_t *pause = malloc(sizeof(pause_t));
    sfVector2f pos = {(desktop_size->width - 1280) / 2 * 2.5,
        (desktop_size->height - 720) / 2 * 1.5};

    pause->title = "Quest";
    pause->title_tx = sfText_create();
    sfText_setString(pause->title_tx, pause->title);
    sfText_setFont(pause->title_tx,
        sfFont_createFromFile("raycast/assets/arial.ttf"));
    sfText_setCharacterSize(pause->title_tx, 50);
    sfText_setPosition(pause->title_tx, pos);
    pause->background = sfRectangleShape_create();
    sfRectangleShape_setSize(pause->background, (sfVector2f){1280, 720});
    sfRectangleShape_setFillColor(pause->background, sfBlack);
    sfRectangleShape_setPosition(pause->background,
        (sfVector2f){(desktop_size->width - 1280) / 2,
            (desktop_size->height - 720) / 2});
    return pause;
}

static void type_boost2(spec_t *spec, char *type, sfVideoMode *desktop_size)
{
    sfVector2f hitbox_size = {200, 180};
    sfVector2f pos = {(desktop_size->width + 200 * 0.85) / 2,
        (desktop_size->height - 200) / 2};

    if (strcmp(type, "health") == 0) {
        spec->malus = 2;
        spec->desc = "Less health";
        spec->hitbox = sfRectangleShape_create();
        sfRectangleShape_setSize(spec->hitbox, hitbox_size);
        sfRectangleShape_setFillColor(spec->hitbox, sfTransparent);
        sfRectangleShape_setOutlineColor(spec->hitbox, sfTransparent);
        sfRectangleShape_setOutlineThickness(spec->hitbox, 2);
        sfRectangleShape_setPosition(spec->hitbox, pos);
    }
}

static void type_boost(spec_t *spec, char *type, sfVideoMode *desktop_size)
{
    sfVector2f hitbox_size = {150, 210};
    sfVector2f pos = {(desktop_size->width - 210 * 2.5) / 2,
        (desktop_size->height - 230) / 2};

    if (strcmp(type, "dmg") == 0) {
        spec->malus = 10;
        spec->desc = "Less damage";
        spec->hitbox = sfRectangleShape_create();
        sfRectangleShape_setSize(spec->hitbox, hitbox_size);
        sfRectangleShape_setFillColor(spec->hitbox, sfTransparent);
        sfRectangleShape_setOutlineColor(spec->hitbox, sfTransparent);
        sfRectangleShape_setOutlineThickness(spec->hitbox, 2);
        sfRectangleShape_setPosition(spec->hitbox, pos);
    }
    type_boost2(spec, type, desktop_size);
}

static spec_t *init_spec(char *type, sfVideoMode *desktop_size)
{
    spec_t *spec = malloc(sizeof(spec_t));

    type_boost(spec, type, desktop_size);
    return spec;
}

dilema_t *init_dilema(void)
{
    dilema_t *dilema = malloc(sizeof(dilema_t));
    sfVideoMode desktop_size = sfVideoMode_getFullscreenModes(NULL)[0];

    dilema->texture =
        sfTexture_createFromFile("raycast/assets/dilemma.png", NULL);
    dilema->background = sfSprite_create();
    sfSprite_setTexture(dilema->background, dilema->texture, sfTrue);
    sfSprite_setScale(dilema->background, (sfVector2f){2.5, 2.5});
    sfSprite_setPosition(dilema->background, (sfVector2f){
        (desktop_size.width - 469 * 2.5) / 2,
        (desktop_size.height - 266 * 2.5) / 2});
    dilema->spec_left = init_spec("dmg", &desktop_size);
    dilema->spec_right = init_spec("health", &desktop_size);
    return dilema;
}

player_t *init_player_rayc(void)
{
    player_t *player = malloc(sizeof(player_t));

    player->health = 100;
    player->malus = 0;
    player->outline = sfRectangleShape_create();
    player->life_bar = sfRectangleShape_create();
    sfRectangleShape_setSize(
        player->life_bar, (sfVector2f){player->health * 3, 20});
    sfRectangleShape_setFillColor(player->life_bar, sfRed);
    sfRectangleShape_setPosition(player->life_bar, (sfVector2f){1600, 10});
    sfRectangleShape_setSize(
            player->outline, (sfVector2f){player->health * 3, 20});
    sfRectangleShape_setFillColor(player->outline, sfTransparent);
    sfRectangleShape_setOutlineColor(player->outline, sfBlack);
    sfRectangleShape_setOutlineThickness(player->outline, 2);
    sfRectangleShape_setPosition(player->outline, (sfVector2f){1600, 10});
    return player;
}

static void init_struct2(engine_t *buff, sfRenderWindow *window)
{
    sfVector2u wsize;
    sfVector2f crosshairSize;
    sfVideoMode mode = {1920, 1080, 32};

    buff->clock = sfClock_create();
    buff->crosshair = sfSprite_create();
    sfSprite_setTexture(buff->crosshair,
        sfTexture_createFromFile("raycast/assets/crosshair.png", NULL),
        sfTrue);
    buff->mode = mode;
    buff->window = window;
    wsize = sfRenderWindow_getSize(buff->window);
    sfSprite_setScale(buff->sprite, (sfVector2f) {mode.width /
        buff->wSizex, mode.height / buff->wSizey});
    sfSprite_setPosition(buff->sprite, (sfVector2f){0, 0});
    crosshairSize = (sfVector2f){sfSprite_getGlobalBounds(
        buff->crosshair).width / 2, sfSprite_getGlobalBounds(
            buff->crosshair).height / 2};
    sfSprite_setPosition(buff->crosshair, (sfVector2f){
            wsize.x / 2 - crosshairSize.x, wsize.y / 2 - crosshairSize.y});
}

static void init_engine(game_t *data)
{
    data->engine->wSizex = SCREEN_WIDTH;
    data->engine->wSizey = SCREEN_HEIGHT;
    data->engine->posX = 2;
    data->engine->posY = 2;
    data->engine->dirX = -1;
    data->engine->dirY = 0;
    data->engine->planeX = 0;
    data->engine->planeY = 0.7;
    data->engine->mSpeed = 2;
    data->engine->rSpeed = 0.001;
    data->engine->invScreenWidth = 1.0 / data->engine->wSizex;
    data->engine->rotationAngle = 0;
    data->engine->dt = 0;
    data->engine->texture = sfTexture_create(data->engine->wSizex,
        data->engine->wSizey);
    data->engine->invScreenHeight = 1.0 / data->engine->wSizey;
}

void init_struct(game_t *data, sfRenderWindow *window)
{
    const sfView *view = sfRenderWindow_getDefaultView(window);

    sfRenderWindow_setView(window, view);
    data->engine = malloc(sizeof(engine_t));
    data->weapons = malloc(sizeof(weapons_list_t));
    init_textures(data->engine);
    init_engine(data);
    data->quests = init_quests_st();
    init_mobs(data->engine);
    init_struct3(data->engine);
    init_struct2(data->engine, window);
    init_weapons(data->weapons, data);
    data->current_weapon = data->weapons[data->index_weapon];
    data->player = init_player_rayc();
    data->dilema = init_dilema();
    data->pause = init_pause(&data->engine->mode);
}
