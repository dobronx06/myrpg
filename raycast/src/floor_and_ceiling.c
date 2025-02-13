/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** floor_and_ceiling.c
*/

#include "../include/my.h"

void calculate_ray_direction_floor(engine_t *game)
{
    game->rayDirX0 = game->dirX - game->planeX;
    game->rayDirY0 = game->dirY - game->planeY;
    game->rayDirX1 = game->dirX + game->planeX;
    game->rayDirY1 = game->dirY + game->planeY;
}

void calculate_floor_steps(engine_t *game, int y)
{
    int p = y - game->wSizey / 2;
    float posZ = 0.5 * game->wSizey;
    float rowDistance = posZ / p;

    game->floorStepX = rowDistance *
        (game->rayDirX1 - game->rayDirX0) / game->wSizex;
    game->floorStepY = rowDistance *
        (game->rayDirY1 - game->rayDirY0) / game->wSizex;
}

void calculate_texture_coordinates(engine_t *game, float floorX, float floorY)
{
    int texWidthMask = 63;
    int texHeightMask = 63;

    game->cellX = (int)(floorX);
    game->cellY = (int)(floorY);
    game->tx = (int)(64 * (floorX - game->cellX)) & texWidthMask;
    game->ty = (int)(64 * (floorY - game->cellY)) & texHeightMask;
}

static sfColor trunc_floor_ceiling(sfColor color)
{
    color.r = color.r / 2;
    color.g = color.g / 2;
    color.b = color.b / 2;
    return color;
}

void draw_floor_and_ceiling(engine_t *game, int x, int y)
{
    sfColor c;
    int ft = 1;
    int ct = 5;
    float distance = game->wSizey / (2.0 * y - game->wSizey);

    c = sfImage_getPixel(game->textures[ft].image, game->tx, game->ty);
    c = apply_fog(c, distance, 1);
    game->fcPxl[(y * game->wSizex + x) * 4 + 0] = c.r;
    game->fcPxl[(y * game->wSizex + x) * 4 + 1] = c.g;
    game->fcPxl[(y * game->wSizex + x) * 4 + 2] = c.b;
    game->fcPxl[(y * game->wSizex + x) * 4 + 3] = c.a;
    c = sfImage_getPixel(game->textures[ct].image, game->tx, game->ty);
    c = trunc_floor_ceiling(c);
    c = apply_fog(c, distance, 1);
    game->fcPxl[((game->wSizey - y - 1) * game->wSizex + x) * 4 + 0] = c.r;
    game->fcPxl[((game->wSizey - y - 1) * game->wSizex + x) * 4 + 1] = c.g;
    game->fcPxl[((game->wSizey - y - 1) * game->wSizex + x) * 4 + 2] = c.b;
    game->fcPxl[((game->wSizey - y - 1) * game->wSizex + x) * 4 + 3] = c.a;
}

void cast_floor_and_ceiling(engine_t *game)
{
    int w = game->wSizex;
    int h = game->wSizey;
    float floorY;
    float floorX;

    for (int y = 0; y < h; y++) {
        calculate_ray_direction_floor(game);
        calculate_floor_steps(game, y);
        floorX = game->posX + 0.5 * h * game->rayDirX0 / (y - h / 2);
        floorY = game->posY + 0.5 * h * game->rayDirY0 / (y - h / 2);
        for (int x = 0; x < w; ++x) {
            calculate_texture_coordinates(game, floorX, floorY);
            floorX += game->floorStepX;
            floorY += game->floorStepY;
            draw_floor_and_ceiling(game, x, y);
        }
    }
}
