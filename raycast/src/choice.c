/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** choice
*/

#include "../include/my.h"

void display_choice(game_t *game)
{
    sfTexture *texture = sfTexture_create(1920, 1080);
    sfSprite *screen = sfSprite_create();

    sfTexture_updateFromRenderWindow(texture, game->engine->window, 0, 0);
    sfSprite_setTexture(screen, texture, sfTrue);
    sfSprite_setPosition(screen, (sfVector2f){0, 0});
    sfRenderWindow_clear(game->engine->window, sfBlack);
    sfRenderWindow_drawSprite(game->engine->window, screen, NULL);
    sfRenderWindow_drawSprite(game->engine->window,
        game->dilema->background, NULL);
    sfRenderWindow_drawRectangleShape(game->engine->window,
        game->dilema->spec_left->hitbox, NULL);
    sfRenderWindow_drawRectangleShape(game->engine->window,
        game->dilema->spec_right->hitbox, NULL);
}

void handle_choice3(game_t *game, sfVector2i mouse, bool *choice_made)
{
    sfFloatRect rect_left =
        sfRectangleShape_getGlobalBounds(game->dilema->spec_left->hitbox);
    sfFloatRect rect_right =
        sfRectangleShape_getGlobalBounds(game->dilema->spec_right->hitbox);

    if (game->event.type == sfEvtMouseButtonPressed &&
        game->event.mouseButton.button == sfMouseLeft) {
        if (sfFloatRect_contains(&rect_left, mouse.x, mouse.y)) {
            game->player->malus -= (game->player->malus >= 10) ?
            game->dilema->spec_left->malus : 0;
            *choice_made = true;
        }
        if (sfFloatRect_contains(&rect_right, mouse.x, mouse.y)) {
            game->player->health /= (game->player->health > 0) ?
            game->dilema->spec_right->malus : 1;
            *choice_made = true;
        }
    }
}

void handle_choice2(game_t *game, sfVector2i mouse, bool *choice_made)
{
    while (sfRenderWindow_pollEvent(game->engine->window, &game->event)) {
        if (game->event.type == sfEvtClosed){
            sfRenderWindow_close(game->engine->window);
            *choice_made = true;
            return;
        }
        handle_choice3(game, mouse, choice_made);
    }
}

void handle_choice(game_t *game)
{
    sfVector2i mouse;
    bool choice_made = false;

    display_choice(game);
    sfRenderWindow_display(game->engine->window);
    sfRenderWindow_setMouseCursorVisible(game->engine->window, sfTrue);
    while (!choice_made) {
        mouse = sfMouse_getPositionRenderWindow(game->engine->window);
        handle_choice2(game, mouse, &choice_made);
    }
    game->state = PLAYING;
    sfRenderWindow_setMouseCursorVisible(game->engine->window, sfFalse);
}
