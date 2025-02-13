/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** events_inputs.c
*/

#include "../include/my.h"

static void handle_weapon(game_t *data)
{
    switch (data->current_weapon->type) {
        case PISTOL:
            handle_pistol(data);
            break;
        case SHOTGUN:
            handle_shotgun(data);
            break;
        case FIST:
            break;
        default:
            break;
    }
}

static void handle_weapon_switch(game_t *data, sfEvent *event)
{
    if (event->mouseWheelScroll.delta > 0 && data->index_weapon == 2) {
        data->index_weapon = 0;
        return;
    }
    if (event->mouseWheelScroll.delta < 0 && data->index_weapon == 0) {
        data->index_weapon = 2;
        return;
    }
    if (event->mouseWheelScroll.delta > 0 && data->index_weapon < 2) {
        data->index_weapon++;
        return;
    }
    if (event->mouseWheelScroll.delta < 0 && data->index_weapon > 0)
        data->index_weapon--;
}

void handle_mouse(game_t *data, sfEvent *event)
{
    if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft) {
        if (data->current_weapon->state != READY)
            return;
        data->current_weapon->state = FIRING;
        sfSound_play(data->current_weapon->shot_sound);
        sfClock_restart(data->current_weapon->clock);
        handle_weapon(data);
    }
    if (event->type == sfEvtMouseWheelScrolled) {
        handle_weapon_switch(data, event);
        data->current_weapon = data->weapons[data->index_weapon];
    }
}

static void handle_keyboard3(game_t *vars, sfEvent *event)
{
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyBackspace))
        sfRenderWindow_close(vars->engine->window);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyE) {
        if (vars->engine->worldMap[(int) (vars->engine->posX +
            vars->engine->dirX)][(int) vars->engine->posY] == 8)
            vars->engine->worldMap[(int) (vars->engine->posX +
            vars->engine->dirX)][(int) vars->engine->posY] = 0;
        if (vars->engine->worldMap[(int) vars->engine->posX]
            [(int) (vars->engine->posY + vars->engine->dirY)] == 8)
            vars->engine->worldMap[(int) vars->engine->posX]
            [(int) (vars->engine->posY + vars->engine->dirY)] = 0;
    }
    handle_mouse(vars, event);
}

static void handle_keyboard2(game_t *game)
{
    engine_t *eng = game->engine;

    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        eng->newX = eng->posX - eng->planeX * eng->mSpeed / 1.2 * eng->dt;
        eng->newY = eng->posY - eng->planeY * eng->mSpeed / 1.2 * eng->dt;
        if (eng->worldMap[(int) eng->newX][(int) eng->posY] == 0)
            eng->posX = eng->newX;
        if (eng->worldMap[(int) eng->posX][(int) eng->newY] == 0)
            eng->posY = eng->newY;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        eng->newX = eng->posX + eng->planeX * eng->mSpeed / 1.2 * eng->dt;
        eng->newY = eng->posY + eng->planeY * eng->mSpeed / 1.2 * eng->dt;
        if (eng->worldMap[(int) eng->newX][(int) eng->posY] == 0)
            eng->posX = eng->newX;
        if (eng->worldMap[(int) eng->posX][(int) eng->newY] == 0)
            eng->posY = eng->newY;
    }
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        game->state = PAUSE;
}

static void handle_keyboard(game_t *game)
{
    engine_t *eng = game->engine;

    eng->mSpeed = sfKeyboard_isKeyPressed(sfKeyLShift) ? 3 : 2;
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        eng->newX = eng->posX - eng->dirX * eng->rSpeed * 1500 * eng->dt;
        eng->newY = eng->posY - eng->dirY * eng->rSpeed * 1500 * eng->dt;
        if (eng->worldMap[(int) eng->newX][(int) eng->posY] == 0)
            eng->posX = eng->newX;
        if (eng->worldMap[(int) eng->posX][(int) eng->newY] == 0)
            eng->posY = eng->newY;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        eng->newX = eng->posX + eng->dirX * eng->mSpeed * eng->dt;
        eng->newY = eng->posY + eng->dirY * eng->mSpeed * eng->dt;
        if (eng->worldMap[(int) eng->newX][(int) eng->posY] == 0)
            eng->posX = eng->newX;
        if (eng->worldMap[(int) eng->posX][(int) eng->newY] == 0)
            eng->posY = eng->newY;
    }
    handle_keyboard2(game);
}

static void update_rotation(engine_t *engine, int dx)
{
    double ra;

    engine->rotationAngle = dx * engine->rSpeed * engine->dt;
    ra = engine->rotationAngle * -1;
    ra /= 2;
    engine->oldDirX = engine->dirX;
    engine->dirX = engine->dirX * cos(ra) - engine->dirY * sin(ra);
    engine->dirY = engine->oldDirX * sin(ra) + engine->dirY * cos(ra);
    engine->oldPlaneX = engine->planeX;
    engine->planeX = engine->planeX * cos(ra) - engine->planeY * sin(ra);
    engine->planeY = engine->oldPlaneX * sin(ra) + engine->planeY * cos(ra);
}

void handle_input(game_t *vars)
{
    engine_t *engine = vars->engine;
    int dx = sfMouse_getPositionRenderWindow(engine->window).x -
        sfRenderWindow_getSize(engine->window).x / 2;

    while (sfRenderWindow_pollEvent(engine->window, &vars->event)) {
        if (vars->event.type == sfEvtMouseMoved)
            update_rotation(engine, dx);
        handle_keyboard3(vars, &vars->event);
    }
    if (sfRenderWindow_hasFocus(engine->window) == sfTrue)
        sfMouse_setPosition((sfVector2i){sfRenderWindow_getSize(
        engine->window).x / 2, sfRenderWindow_getSize(engine->window).y / 2},
        (sfWindow *)engine->window);
}

void events_rayc(game_t *data)
{
    handle_input(data);
    handle_keyboard(data);
    data->current_weapon = data->weapons[data->index_weapon];
}
