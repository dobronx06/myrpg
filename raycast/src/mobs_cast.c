/*
** EPITECH PROJECT, 2024
** MyRPG_forked
** File description:
** mobs_cast.c
*/

#include "../include/my.h"

static void calculate_sprite_position_and_transformation(engine_t *game, int i)
{
    double invDet = 1.0 / (game->planeX * game->dirY -
        game->dirX * game->planeY);

    game->spriteX = game->sprites[game->spriteOrder[i]].x - game->posX;
    game->spriteY = game->sprites[game->spriteOrder[i]].y - game->posY;
    game->transformX = invDet * (game->dirY * game->spriteX - game->dirX *
        game->spriteY);
    game->transformY = invDet * (-game->planeY * game->spriteX + game->planeX *
        game->spriteY);
    game->spriteScreenX = (long)((game->wSizex / 2) * (1 + game->transformX /
        game->transformY));
    game->vMoveScreen = (long)(VMOVE / game->transformY);
}

static void calculate_sprite_dimensions_and_drawing(engine_t *game)
{
    game->spriteHeight = abs((int)(game->wSizey / (game->transformY))) / VDIV;
    game->drawStartY = -game->spriteHeight / 2 + game->wSizey / 2 +
        game->vMoveScreen;
    if (game->drawStartY < 0)
        game->drawStartY = 0;
    game->drawEndY = game->spriteHeight / 2 + game->wSizey / 2 +
        game->vMoveScreen;
    if (game->drawEndY >= game->wSizey)
        game->drawEndY = game->wSizey - 1;
    game->spriteWidth = abs((int)(game->wSizey / (game->transformY))) / UDIV;
    game->drawStartX = -game->spriteWidth / 2 + game->spriteScreenX;
    if (game->drawStartX < 0)
        game->drawStartX = 0;
    game->drawEndX = game->spriteWidth / 2 + game->spriteScreenX;
    if (game->drawEndX >= game->wSizex)
        game->drawEndX = game->wSizex;
}

sfColor get_sprite_color(engine_t *game, long texX, long texY, int i)
{
    sfImage *image = game->sprites[game->spriteOrder[i]].image;

    return sfImage_getPixel(image, texX % 99, texY % 99);
}

void draw_sprite_stripe(engine_t *game, long stripe, long texX, int i)
{
    long d;
    long texY;
    sfColor color;
    float distance = sqrt(
        pow(game->sprites[game->spriteOrder[i]].x - game->posX, 2) +
            pow(game->sprites[game->spriteOrder[i]].y - game->posY, 2));

    for (long y = game->drawStartY; y < game->drawEndY; y++) {
        d = (y - game->vMoveScreen) * 256 - game->wSizey * 128 +
            game->spriteHeight * 128;
        texY = ((d * 99) / game->spriteHeight) / 256;
        color = get_sprite_color(game, texX, texY, i);
        color = apply_fog(color, distance, 0);
        if ((color.r != 0 || color.g != 0 || color.b != 0)) {
            game->mob_pixels[(y * game->wSizex + stripe) * 4] = color.r;
            game->mob_pixels[(y * game->wSizex + stripe) * 4 + 1] = color.g;
            game->mob_pixels[(y * game->wSizex + stripe) * 4 + 2] = color.b;
            game->mob_pixels[(y * game->wSizex + stripe) * 4 + 3] = color.a;
        }
    }
}

void draw_sprite(engine_t *game, int i)
{
    long texX;

    for (long stripe = game->drawStartX; stripe < game->drawEndX; stripe++) {
        texX = (long)(256 * (stripe - (-game->spriteWidth / 2 +
            game->spriteScreenX)) * 99 / game->spriteWidth) / 256;
        if (game->transformY > 0 && stripe < game->wSizex && game->transformY
            < game->ZBuffer[stripe]) {
            draw_sprite_stripe(game, stripe, texX, i);
        }
    }
}

void draw_sprites(engine_t *engine, quest_t *quest, player_t *player,
    int *quest_id)
{
    *quest_id = quest->end_ojb;
    update_mobs(engine, quest, player);
    sort_sprites(engine);
    sort_mobs(engine, quest->end_ojb);
    for (int i = 0; i < quest->end_ojb; i++) {
        if (!engine->sprites[i].is_alive){
            already_killed(quest, engine->sprites[i].id);
            continue;
        }
        calculate_sprite_position_and_transformation(engine, i);
        calculate_sprite_dimensions_and_drawing(engine);
        draw_sprite(engine, i);
    }
    sfTexture_updateFromPixels(engine->texture, engine->mob_pixels,
        engine->wSizex, engine->wSizey, 0, 0);
    sfRenderWindow_drawSprite(engine->window, engine->sprite, NULL);
}
