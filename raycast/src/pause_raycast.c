/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** pause_raycast
*/

#include "../include/my.h"

void display_pause(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->engine->window,
        game->pause->background, NULL);
    sfRenderWindow_drawText(game->engine->window, game->pause->title_tx, NULL);
}

void handle_pause3(game_t *game, bool *pause_off)
{
    if (game->event.type == sfEvtKeyPressed)
        if (game->pause->open == true && sfKeyboard_isKeyPressed(sfKeyP))
            *pause_off = true;
}

void handle_pause2(game_t *game, bool *pause_off)
{
    while (sfRenderWindow_pollEvent(game->engine->window, &game->event)) {
        if (game->event.type == sfEvtClosed){
            sfRenderWindow_close(game->engine->window);
            *pause_off = true;
            return;
        }
    }
    handle_pause3(game, pause_off);
}

void handle_pause(game_t *game)
{
    bool pause_off = false;

    game->pause->open = true;
    display_pause(game);
    sfRenderWindow_display(game->engine->window);
    while (!pause_off)
        handle_pause2(game, &pause_off);
    game->state = PLAYING;
    game->pause->open = false;
    sfRenderWindow_setMouseCursorVisible(game->engine->window, sfFalse);
}
