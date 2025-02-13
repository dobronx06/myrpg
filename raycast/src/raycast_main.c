/*
** EPITECH PROJECT, 2024
** raycast
** File description:
** main.c
*/

#include "../include/my.h"
#include "../include/map.h"

static void destroy_textures(engine_t *buff)
{
    for (int i = 0; i < NB_TEXTURES; i++)
        sfImage_destroy(buff->textures[i].image);
    free(buff->textures);
}

void close_game(game_t *data)
{
    sfSprite_destroy(data->engine->sprite);
    sfTexture_destroy(data->engine->texture);
    sfClock_destroy(data->engine->clock);
    sfSprite_destroy(data->engine->crosshair);
    free(data->engine->wPxl);
    free(data->engine->fcPxl);
    free(data->engine->pixels);
    destroy_textures(data->engine);
    free(data->engine);
    free(data);
}

void init_struct3(engine_t *buff)
{
    buff->wPxl = malloc(buff->wSizex * buff->wSizey * 4 * sizeof(sfUint8));
    buff->pixels = malloc(buff->wSizex * buff->wSizey * 4 * sizeof(sfUint8));
    buff->fcPxl = malloc(buff->wSizex * buff->wSizey * 4 * sizeof(sfUint8));
    buff->mob_pixels = malloc(buff->wSizex *
        buff->wSizey * 4 * sizeof(sfUint8));
    buff->sprite = sfSprite_create();
    sfSprite_setTexture(buff->sprite, buff->texture, sfTrue);
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++)
            buff->worldMap[i][j] = worldMap[i][j];
}

static void manipulate_pixels_and_draw(engine_t *game)
{
    for (int i = 0; i < game->wSizex * game->wSizey * 4; i += 4) {
        if (game->wPxl[i + 3] != 0) {
            game->pixels[i] = game->wPxl[i];
            game->pixels[i + 1] = game->wPxl[i + 1];
            game->pixels[i + 2] = game->wPxl[i + 2];
            game->pixels[i + 3] = game->wPxl[i + 3];
        } else {
            game->pixels[i] = game->fcPxl[i];
            game->pixels[i + 1] = game->fcPxl[i + 1];
            game->pixels[i + 2] = game->fcPxl[i + 2];
            game->pixels[i + 3] = game->fcPxl[i + 3];
        }
    }
    sfTexture_updateFromPixels(game->texture, game->pixels, game->wSizex,
        game->wSizey, 0, 0);
    sfRenderWindow_drawSprite(game->window, game->sprite, NULL);
}

static void every_mob_alive(game_t *game, int quest_id)
{
    for (int i = 0; i < NUMSPRITES; i++){
        game->engine->sprites[i].health = 100;
        game->engine->sprites[i].is_alive = true;
        game->engine->sprites[i].x = game->engine->sprites[i].startX;
        game->engine->sprites[i].y = game->engine->sprites[i].startY;
    }
    if (quest_id != 4)
        game->state = DILEMMA;
    else
        game->state = END;
}

static void quests_checker(game_t *game, quest_t *current_quest,
    int *quest_id)
{
    if (strcmp(current_quest->name_quest, "Quete 1") == 0){
        draw_sprites(game->engine, current_quest, game->player, quest_id);
        if (current_quest->ojb_progress == current_quest->end_ojb)
            every_mob_alive(game, 1);
    }
    if (strcmp(current_quest->name_quest, "Quete 2") == 0){
        draw_sprites(game->engine, current_quest, game->player, quest_id);
        if (current_quest->ojb_progress == current_quest->end_ojb)
            every_mob_alive(game, 2);
    }
    if (strcmp(current_quest->name_quest, "Quete 3") == 0){
        draw_sprites(game->engine, current_quest, game->player, quest_id);
        if (current_quest->ojb_progress == current_quest->end_ojb)
            every_mob_alive(game, 3);
    }
    if (strcmp(current_quest->name_quest, "Quete 4") == 0){
        draw_sprites(game->engine, current_quest, game->player, quest_id);
        if (current_quest->ojb_progress == current_quest->end_ojb)
            every_mob_alive(game, 4);
    }
}

void spawn_mobs_based_on_quest(game_t *game, quest_t **quests, int *quest_id)
{
    quest_t *current_quest = NULL;
    char *progress = NULL;

    for (int i = 0; quests[i] != NULL; i++) {
        if (quests[i]->ojb_progress < quests[i]->end_ojb) {
            current_quest = quests[i];
            break;
        }
    }
    if (current_quest == NULL)
        return;
    quests_checker(game, current_quest, quest_id);
    progress = int_to_char(current_quest->ojb_progress,
        current_quest->end_ojb);
    sfRenderWindow_drawText(game->engine->window, current_quest->name_text(
        current_quest->name_quest), NULL);
    sfRenderWindow_drawText(game->engine->window, current_quest->desc_text(
        current_quest->description), NULL);
    sfRenderWindow_drawText(game->engine->window, current_quest->progress_text(
        progress), NULL);
}

void raycast(engine_t *game, game_t *data, int *quest_id)
{
    clear_buffer(game->pixels, game);
    clear_buffer(game->wPxl, game);
    clear_buffer(game->fcPxl, game);
    clear_buffer(game->mob_pixels, game);
    for (int x = 0; x < game->wSizex; x++) {
        game->cameraX = 2 * x * game->invScreenWidth - 1;
        game->rayDirX = game->dirX + game->planeX * game->cameraX;
        game->rayDirY = game->dirY + game->planeY * game->cameraX;
        calculate_step_and_side_dist(game);
        perform_dda(game);
        calculate_distance_and_draw_to_buffer(game, x);
        game->ZBuffer[x] = game->perpWallDist;
    }
    cast_floor_and_ceiling(game);
    manipulate_pixels_and_draw(game);
    spawn_mobs_based_on_quest(data, data->quests, quest_id);
    update_anims(data);
    sfRenderWindow_drawSprite(game->window, data->current_weapon->sprite,
        NULL);
    sfRenderWindow_drawSprite(game->window, game->crosshair, NULL);
}

static void state_game(game_t *data, int quest_id, sfTime time)
{
    if (data->player->health <= 0)
        data->state = END;
    if (data->state == DILEMMA)
        handle_choice(data);
    if (data->state == PLAYING){
        events_rayc(data);
        sfRenderWindow_clear(data->engine->window, sfWhite);
        raycast(data->engine, data, &quest_id);
        sfRectangleShape_setSize(data->player->life_bar,
            (sfVector2f){data->player->health * 3, 20});
        sfRenderWindow_drawRectangleShape(data->engine->window,
            data->player->life_bar, NULL);
        sfRenderWindow_drawRectangleShape(data->engine->window,
            data->player->outline, NULL);
        sfRenderWindow_display(data->engine->window);
        time = sfClock_getElapsedTime(data->engine->clock);
        data->engine->dt = time.microseconds / 1000000.0f;
    }
    if (data->state == PAUSE)
        handle_pause(data);
}

int raycasting(sfRenderWindow *window)
{
    game_t *data = calloc(1, sizeof(game_t));
    sfTime time;
    int quest_id = 0;

    sfRenderWindow_setSize(window, (sfVector2u){1920, 1080});
    init_struct(data, window);
    data->state = PLAYING;
    sfRenderWindow_setMouseCursorVisible(data->engine->window, sfFalse);
    while (sfRenderWindow_isOpen(data->engine->window) && data->state != END) {
        sfClock_restart(data->engine->clock);
        state_game(data, quest_id, time);
    }
    if (data->player->health <= 0)
        return raycasting(window);
    close_game(data);
    return 0;
}
