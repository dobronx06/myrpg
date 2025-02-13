/*
** EPITECH PROJECT, 2024
** raycast
** File description:
** raycast_funcs.c
*/

#include "../include/my.h"

sfColor apply_fog(sfColor originalColor, float distance, int mode)
{
    float fogStrength = 0.05f;
    float fogLimit = 1.0f;
    float fogMinDist = 5.0f;
    float fogAmount = (distance > fogMinDist) ? fogStrength *
        (distance - fogMinDist) : 0;

    if (mode == 1)
        fogAmount = fogStrength * (distance - fogMinDist);
    fogAmount = (fogAmount > fogLimit) ? fogLimit : fogAmount;
    originalColor.r = (sfUint8)(originalColor.r * (1 - fogAmount));
    originalColor.g = (sfUint8)(originalColor.g * (1 - fogAmount));
    originalColor.b = (sfUint8)(originalColor.b * (1 - fogAmount));
    return originalColor;
}

void clear_buffer(sfUint8 *pixels, engine_t *data)
{
    for (int i = 0; i < data->wSizex * data->wSizey * 4; i += 4) {
        pixels[i] = 0;
        pixels[i + 1] = 0;
        pixels[i + 2] = 0;
        pixels[i + 3] = 0;
    }
}

void calculate_step_and_side_dist(engine_t *game)
{
    game->mapX = (int)game->posX;
    game->mapY = (int)game->posY;
    game->deltaDistX = fabs(1 / game->rayDirX);
    game->deltaDistY = fabs(1 / game->rayDirY);
    game->hit = 0;
    if (game->rayDirX < 0) {
        game->stepX = -1;
        game->sideDistX = (game->posX - game->mapX) * game->deltaDistX;
    } else {
        game->stepX = 1;
        game->sideDistX = (game->mapX + 1.0 - game->posX) * game->deltaDistX;
    }
    if (game->rayDirY < 0) {
        game->stepY = -1;
        game->sideDistY = (game->posY - game->mapY) * game->deltaDistY;
    } else {
        game->stepY = 1;
        game->sideDistY = (game->mapY + 1.0 - game->posY) * game->deltaDistY;
    }
}

void perform_dda(engine_t *game)
{
    while (!game->hit) {
        if (game->sideDistX < game->sideDistY) {
            game->sideDistX += game->deltaDistX;
            game->mapX += game->stepX;
            game->side = SIDE_X;
        } else {
            game->sideDistY += game->deltaDistY;
            game->mapY += game->stepY;
            game->side = SIDE_Y;
        }
        if (game->worldMap[game->mapX][game->mapY] > 0)
            game->hit = 1;
    }
}

static void calculate_perpendicular_distance(engine_t *game)
{
    if (game->side == 0)
        game->perpWallDist = (game->mapX - game->posX + (1 - game->stepX) / 2)
            / game->rayDirX;
    else
        game->perpWallDist = (game->mapY - game->posY + (1 - game->stepY) / 2)
            / game->rayDirY;
}

static void calculate_line_height_and_draw_limits(engine_t *game)
{
    game->lineHeight = (int)(game->wSizey / game->perpWallDist);
    game->drawStart = -game->lineHeight / 2 + game->wSizey / 2;
    game->drawStart = (game->drawStart < 0) ? 0 : game->drawStart;
    game->drawEnd = game->lineHeight / 2 + game->wSizey / 2;
    if (game->drawEnd >= game->wSizey)
        game->drawEnd = game->wSizey - 1;
}

static void calculate_wall_hit_point(engine_t *game, double *wallX)
{
    if (game->side == 0)
        *wallX = game->posY + game->perpWallDist * game->rayDirY;
    else
        *wallX = game->posX + game->perpWallDist * game->rayDirX;
    *wallX -= floor(*wallX);
}

static void draw_vertical_line(engine_t *game, int x, double wallX, int texNum)
{
    int texX;
    int texY;
    long long d;
    sfColor color;

    texX = (int)(wallX * (double)64);
    if (game->side == 0 && game->rayDirX > 0)
        texX = 64 - texX - 1;
    if (game->side == 1 && game->rayDirY < 0)
        texX = 64 - texX - 1;
    for (int y = game->drawStart; y < game->drawEnd; y++) {
        d = y * 256 - game->wSizey * 128 + game->lineHeight * 128;
        texY = ((d * 64) / game->lineHeight) / 256;
        color = sfImage_getPixel(game->textures[texNum].image, texX, texY);
        color = apply_fog(color, game->perpWallDist, 0);
        game->wPxl[(y * game->wSizex + x) * 4 + 0] = color.r;
        game->wPxl[(y * game->wSizex + x) * 4 + 1] = color.g;
        game->wPxl[(y * game->wSizex + x) * 4 + 2] = color.b;
        game->wPxl[(y * game->wSizex + x) * 4 + 3] = color.a;
    }
}

void calculate_distance_and_draw_to_buffer(engine_t *game, int x)
{
    int texNum;
    double wallX;

    calculate_perpendicular_distance(game);
    calculate_line_height_and_draw_limits(game);
    calculate_wall_hit_point(game, &wallX);
    texNum = game->worldMap[game->mapX][game->mapY] - 1;
    draw_vertical_line(game, x, wallX, texNum);
}
