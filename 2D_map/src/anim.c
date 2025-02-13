/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** anim
*/

#include "../include/my.h"

void move_rect_down(game_t *game, sfSprite *sprite)
{
    if (game->rect_down.left >= 325)
        game->rect_down.left = 0;
    else
        game->rect_down.left += 150;
    sfSprite_setTextureRect(sprite, game->rect_down);
    sfSprite_move(game->player, (sfVector2f){0, 5});
    if (!check_collisions(game->collisions, game->player))
        sfSprite_move(game->player, (sfVector2f){0, -5});
}

void move_rect_up(game_t *game, sfSprite *sprite)
{
    if (game->rect_up.left >= 325)
        game->rect_up.left = 0;
    else
        game->rect_up.left += 150;
    sfSprite_setTextureRect(sprite, game->rect_up);
    sfSprite_move(game->player, (sfVector2f){0, -5});
    if (!check_collisions(game->collisions, game->player))
        sfSprite_move(game->player, (sfVector2f){0, 5});
}

void move_rect_right(game_t *game, sfSprite *sprite)
{
    if (game->rect_right.left >= 325)
        game->rect_right.left = 0;
    else
        game->rect_right.left += 150;
    sfSprite_setTextureRect(sprite, game->rect_right);
    sfSprite_move(game->player, (sfVector2f){5, 0});
    if (!check_collisions(game->collisions, game->player))
        sfSprite_move(game->player, (sfVector2f){-5, 0});
}

void move_rect_left(game_t *game, sfSprite *sprite)
{
    if (game->rect_left.left >= 325)
        game->rect_left.left = 0;
    else
        game->rect_left.left += 150;
    sfSprite_setTextureRect(sprite, game->rect_left);
    sfSprite_move(game->player, (sfVector2f){-5, 0});
    if (!check_collisions(game->collisions, game->player))
        sfSprite_move(game->player, (sfVector2f){5, 0});
}
