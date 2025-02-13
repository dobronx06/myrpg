/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** main
*/

#include "../include/my.h"

static void crow(game_t *game, int *i)
{
    if (game->collisions->debug)
        for (int i = 0; i < 27; ++i)
            sfRenderWindow_drawRectangleShape(game->window,
                game->collisions->rect[i].rect, NULL);
    sfRenderWindow_drawSprite(game->window, game->questmark, NULL);
    dialogue_crow(game, i);
    sfRenderWindow_display(game->window);
}

void draw_and_display(game_t *game, int *i)
{
    sfRenderWindow_clear(game->window, sfBlack);
    sfRenderWindow_drawSprite(game->window, game->background, NULL);
    sfRenderWindow_drawSprite(game->window, game->player, NULL);
    sfRenderWindow_drawSprite(game->window, game->mini_cake, NULL);
    sfRenderWindow_drawSprite(game->window, game->over, NULL);
    sfRenderWindow_drawSprite(game->window, game->textbox2, NULL);
    if (game->scene == 1)
        sfRenderWindow_drawSprite(game->window, game->narrator, NULL);
    for (int i = 0; i < 5; ++i)
        sfRenderWindow_drawRectangleShape(game->window,
            game->slots[i].shape, NULL);
    sfRenderWindow_drawSprite(game->window, game->inventory, NULL);
    sfRenderWindow_drawSprite(game->window, game->sprite, NULL);
    for (int i = 0; i < 3; ++i)
        sfRenderWindow_drawSprite(game->window, game->items[i].sprite, NULL);
    if (game->get_cake == 0)
        sfRenderWindow_drawSprite(game->window, game->items[3].sprite, NULL);
    crow(game, i);
}

static void update_animations(game_t *game, sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;
    sfIntRect rect;

    if (seconds > 0.5) {
        rect = sfSprite_getTextureRect(game->narrator);
        rect.left += 180;
        if (rect.left >= 720)
        rect.left = 0;
        sfSprite_setTextureRect(game->narrator, rect);
        sfClock_restart(clock);
    }
}

static void movement(sfEvent *event, game_t *game)
{
    if (event->key.code == sfKeyZ)
        move_rect_up(game, game->player);
    if (event->key.code == sfKeyS)
        move_rect_down(game, game->player);
    if (event->key.code == sfKeyD)
        move_rect_right(game, game->player);
    if (event->key.code == sfKeyQ)
        move_rect_left(game, game->player);
}

void events(sfRenderWindow *window, sfEvent *event, game_t *game, int *i)
{
    static int count = 0;

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event->type == sfEvtKeyPressed) {
        if (count == 0) {
            *i = 1;
            count++;
        } else
            *i = -1;
        sfText_setString(game->textsf, "");
        sfSprite_setPosition(game->dialogue_line, (sfVector2f){-1000, -1000});
        sfSprite_setPosition(game->textbox2, (sfVector2f){-1000, -1000});
        if (event->key.code == sfKeyEscape)
            sfRenderWindow_close(window);
        movement(event, game);
        if (event->key.code == sfKeyP)
            game->collisions->debug = !game->collisions->debug;
    }
}

void check_near_narrator(game_t *game, int *i)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player);
    sfVector2f narrator_pos = sfSprite_getPosition(game->narrator);

    if (custom_abs(player_pos.x - narrator_pos.x) < 150 &&
        custom_abs(player_pos.y - narrator_pos.y) < 150 &&
        game->get_cake == 1 && *i < 2) {
        if (sfKeyboard_isKeyPressed(sfKeyE))
            *i = 2;
        if (sfKeyboard_isKeyPressed(sfKeyEnter)){
            *i = 3;
            game->get_cake = 0;
        }
        return;
    }
    if (custom_abs(player_pos.x - narrator_pos.x) < 150 &&
        custom_abs(player_pos.y - narrator_pos.y) < 150 &&
        game->get_cake == 0) {
        if (sfKeyboard_isKeyPressed(sfKeyE)) {
            *i = 5;
            game->get_cake = 1;
        }
    }
}

void check_near_cake(game_t *game, int *i)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player);
    sfVector2f cake_pos = sfSprite_getPosition(game->mini_cake);

    if (custom_abs(player_pos.x - cake_pos.x) < 50 &&
        custom_abs(player_pos.y - cake_pos.y) < 50 && *i != 0
        && sfSprite_getPosition(game->mini_cake).x != -1000){
        if (sfKeyboard_isKeyPressed(sfKeyE)) {
            sfSprite_setPosition(game->mini_cake, (sfVector2f){-1000, -1000});
            game->get_cake = 0;
            *i = 4;
        }
    }
}

static void check_near_tv(game_t *game, int *i)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player);
    sfVector2f tv_pos = sfSprite_getPosition(game->narrator);

    if (custom_abs(player_pos.x - tv_pos.x) < 150 &&
        custom_abs(player_pos.y - tv_pos.y) < 150) {
        if (sfKeyboard_isKeyPressed(sfKeyE) && *i == 5) {
            sfSprite_setPosition(game->questmark, (sfVector2f){-1000, -1000});
            raycasting(game->window);
        }
    }
}

static void game_event_loop(game_t *game, int *i, item_t **dragging_item)
{
    if (game->scene == 1) {
        while (sfRenderWindow_pollEvent(game->window, &game->event)) {
            events(game->window, &game->event, game, i);
            handle_inventory(game, dragging_item);
            handle_drag_and_drop(game, dragging_item);
            check_near_narrator(game, i);
            check_near_cake(game, i);
        }
        check_near_tv(game, i);
        draw_and_display(game, i);
        update_animations(game, game->clock);
    }
}

int first_map(sfRenderWindow *window)
{
    const char *item_files[] =
        {"2D_map/assets/milk.png", "2D_map/assets/apple.png",
            "2D_map/assets/cheese.png", "2D_map/assets/cake.png"};
    const char *intro[] =
        {"Aang ...", "Reveille-toi", "OHHH"};
    game_t *game = malloc(sizeof(game_t));
    item_t *dragging_item = NULL;
    int i = 0;

    init_structs(game, item_files, window);
    set_col(game->collisions);
    while (sfRenderWindow_isOpen(game->window)) {
        if (game->scene == 0) {
            write_func(intro, 3, game, &game->scene);
            continue;
        }
        game_event_loop(game, &i, &dragging_item);
    }
    return 0;
}
