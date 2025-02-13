/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** bullets.c
*/

#include "../include/my.h"

static int check_one_mob(game_t *game, bullet_param_t *raycastData, int i)
{
    mob_t *mob = NULL;

    if ((int)game->engine->sprites[i].x == raycastData->mapX &&
        (int)game->engine->sprites[i].y == raycastData->mapY) {
        mob = find_mob_coords(game->engine, raycastData->mapX,
            raycastData->mapY);
        if (mob == NULL || mob->health <= 0)
            return -1;
        mob->health -= (game->current_weapon->damage +
            game->player->malus);
        return 1;
    }
    return -1;
}

static int check_bullet_collision_with_mobs(game_t *game,
    bullet_param_t *raycastData)
{
    for (int i = 0; i < NUMSPRITES; i++) {
        if (check_one_mob(game, raycastData, i) == 1)
            return 1;
    }
    return 0;
}

static void perform_raycast_and_check_hit(game_t *game,
    bullet_param_t *raycastData)
{
    while (raycastData->hit < 2) {
        if (raycastData->sideDistX < raycastData->sideDistY) {
            raycastData->sideDistX += raycastData->deltaDistX;
            raycastData->mapX += raycastData->stepX;
        } else {
            raycastData->sideDistY += raycastData->deltaDistY;
            raycastData->mapY += raycastData->stepY;
        }
        if (game->engine->worldMap[raycastData->mapX][raycastData->mapY] > 0)
            raycastData->hit = 2;
        if (check_bullet_collision_with_mobs(game, raycastData) == 1)
            raycastData->hit += 1;
    }
}

static void initialize_bullet_params(game_t *game, bullet_param_t *raycastData)
{
    raycastData->posX = game->engine->posX;
    raycastData->posY = game->engine->posY;
    raycastData->dirX = game->engine->dirX;
    raycastData->dirY = game->engine->dirY;
    raycastData->mapX = (int)raycastData->posX;
    raycastData->mapY = (int)raycastData->posY;
    raycastData->deltaDistX = fabs(1 / raycastData->dirX);
    raycastData->deltaDistY = fabs(1 / raycastData->dirY);
    raycastData->stepX = (raycastData->dirX < 0) ? -1 : 1;
    raycastData->stepY = (raycastData->dirY < 0) ? -1 : 1;
    raycastData->hit = 0;
}

static void calculate_step_and_side_dist_bullet(bullet_param_t *raycastData)
{
    if (raycastData->dirX < 0)
        raycastData->sideDistX = (raycastData->posX - raycastData->mapX) *
            raycastData->deltaDistX;
    else
        raycastData->sideDistX = (raycastData->mapX + 1.0 - raycastData->posX)
            * raycastData->deltaDistX;
    if (raycastData->dirY < 0)
        raycastData->sideDistY = (raycastData->posY - raycastData->mapY) *
            raycastData->deltaDistY;
    else
        raycastData->sideDistY = (raycastData->mapY + 1.0 - raycastData->posY)
            * raycastData->deltaDistY;
}

void handle_pistol(game_t *game)
{
    bullet_param_t bullet;

    initialize_bullet_params(game, &bullet);
    calculate_step_and_side_dist_bullet(&bullet);
    perform_raycast_and_check_hit(game, &bullet);
}

void handle_shotgun(game_t *game)
{
    bullet_param_t bullets[3];

    for (int i = 0; i < 3; i++) {
        initialize_bullet_params(game, &bullets[i]);
        if (i == 0) {
            bullets[i].posX -= 1;
            bullets[i].posY -= 1;
        }
        if (i == 2) {
            bullets[i].posX += 1;
            bullets[i].posY += 1;
        }
        calculate_step_and_side_dist_bullet(&bullets[i]);
        perform_raycast_and_check_hit(game, &bullets[i]);
    }
}
