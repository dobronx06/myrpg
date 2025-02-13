/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** init
*/

#include "../include/my.h"

void init_col(game_t *game)
{
    game->collisions = malloc(sizeof(collisions_t));
    game->collisions->rect = malloc(sizeof(rectangle_t) * 27);
    for (int i = 0; i < 27; ++i) {
        game->collisions->rect[i].rect = sfRectangleShape_create();
        game->collisions->rect[i].size = (sfVector2f){125, 125};
        sfRectangleShape_setSize(game->collisions->rect[i].rect,
        game->collisions->rect[i].size);
        game->collisions->rect[i].position =
        (sfVector2f){625 + (i % 6) * 150, 93 + (i / 6) * 145};
        sfRectangleShape_setPosition(game->collisions->rect[i].rect,
        game->collisions->rect[i].position);
        game->collisions->debug = 0;
    }
}

void init_narrator(game_t *game)
{
    game->texture_narrator =
    sfTexture_createFromFile("2D_map/assets/crow_idle.png", NULL);
    game->narrator = sfSprite_create();
    game->view = sfView_create();
    sfView_setSize(game->view, (sfVector2f){1850, 1017});
    sfView_setCenter(game->view, (sfVector2f){920, 510});
    sfRenderWindow_setView(game->window, game->view);
    game->over = sfSprite_create();
    game->texture_over =
    sfTexture_createFromFile("2D_map/assets/over.png", NULL);
    sfSprite_setTexture(game->over, game->texture_over, sfTrue);
    sfSprite_setPosition(game->over, (sfVector2f){-5, 0});
    sfSprite_setTexture(game->narrator, game->texture_narrator, sfTrue);
    sfSprite_setTextureRect(game->narrator, (sfIntRect){0, 0, 200, 200});
    sfSprite_setPosition(game->narrator, (sfVector2f){0, 850});
}

void init_text(game_t *game)
{
    game->text = malloc(sizeof(text_t));
    game->text->font =
        sfFont_createFromFile("2D_map/assets/kongtext.ttf");
    game->text->texts[0] = sfText_create();
    game->text->texts[1] = sfText_create();
    game->text->texts[2] = sfText_create();
    game->text->clock = sfClock_create();
    game->text->delay = 0.1;
    game->text->activeText = 0;
    game->text->nbrtext = 3;
    for (int i = 0; i < 3; ++i) {
        game->text->currentLengths[i] = 0;
        game->text->currentTexts[i][0] = '\0';
    }
}

void init_player(game_t *game)
{
    game->texture_player =
    sfTexture_createFromFile("2D_map/assets/little_aang.png", NULL);
    game->player = sfSprite_create();
    sfSprite_setTexture(game->player, game->texture_player, sfTrue);
    game->rect_down = (sfIntRect){0, 300, 75, 75};
    game->rect_up = (sfIntRect){0, 375, 75, 75};
    game->rect_right = (sfIntRect){0, 450, 75, 75};
    game->rect_left = (sfIntRect){0, 525, 75, 75};
    sfSprite_setTextureRect(game->player, game->rect_down);
    sfSprite_setPosition(game->player, (sfVector2f){1500, 900});
    sfSprite_setScale(game->player, (sfVector2f){1.5, 1.5});
    init_narrator(game);
    init_col(game);
    init_text(game);
}

static void init_game_texture(game_t *game)
{
    game->inventory = sfSprite_create();
    game->texture_inventory =
    sfTexture_createFromFile("2D_map/assets/inventory.png", NULL);
    game->sprite = sfSprite_create();
    game->texture_sprite =
    sfTexture_createFromFile("2D_map/assets/aang.png", NULL);
    game->background = sfSprite_create();
    game->texture_background =
    sfTexture_createFromFile("2D_map/assets/map.png", NULL);
    game->dialogue_line = sfSprite_create();
    game->texture_dialogue_line =
    sfTexture_createFromFile("2D_map/assets/box.png", NULL);
    game->mini_cake = sfSprite_create();
    game->texture_mini_cake =
    sfTexture_createFromFile("2D_map/assets/mini_cake.png", NULL);
    game->questmark = sfSprite_create();
    game->texture_questmark =
    sfTexture_createFromFile("2D_map/assets/questmark.png", NULL);
}

static void init_game_struct(game_t *game, sfRenderWindow *window)
{
    game->mode = (sfVideoMode){1920, 1080, 32};
    game->window = window;
    game->clock = sfClock_create();
    game->textsf = sfText_create();
    game->textbox2 = sfSprite_create();
    game->texture_textbox2 =
    sfTexture_createFromFile("2D_map/assets/box_narrator.png", NULL);
    sfSprite_setTexture(game->textbox2, game->texture_textbox2, sfTrue);
    sfSprite_setPosition(game->textbox2, (sfVector2f){-1000, -1000});
    game->font = sfFont_createFromFile("2D_map/assets/kongtext.ttf");
    init_game_texture(game);
    game->scene = 0;
    game->get_cake = 1;
}

static void init_structsp2(game_t *game, sfRenderWindow *window)
{
    init_game_struct(game, window);
    sfSprite_setTexture(game->inventory, game->texture_inventory, sfTrue);
    sfSprite_setTexture(game->sprite, game->texture_sprite, sfTrue);
    sfSprite_setPosition(game->inventory, (sfVector2f){-1000, -1000});
    sfSprite_setPosition(game->sprite, (sfVector2f){-1000, -1000});
    sfSprite_setTexture(game->background, game->texture_background, sfTrue);
    sfSprite_setPosition(game->background, (sfVector2f){0, 0});
    sfSprite_setTexture
    (game->dialogue_line, game->texture_dialogue_line, sfTrue);
    sfSprite_setPosition(game->dialogue_line, (sfVector2f){650, 870});
    sfSprite_setTexture(game->mini_cake, game->texture_mini_cake, sfTrue);
    sfSprite_setPosition(game->mini_cake, (sfVector2f){270, 100});
    sfSprite_setTexture(game->questmark, game->texture_questmark, sfTrue);
    sfSprite_setPosition(game->questmark, (sfVector2f){-10, 750});
}

static void init_rectangles(game_t *game)
{
    for (int i = 0; i < 30; ++i) {
        game->slots[i].shape = sfRectangleShape_create();
        sfRectangleShape_setSize
        (game->slots[i].shape, (sfVector2f){125, 125});
        sfRectangleShape_setFillColor(game->slots[i].shape, sfTransparent);
        sfRectangleShape_setOutlineColor(game->slots[i].shape, sfTransparent);
        sfRectangleShape_setOutlineThickness(game->slots[i].shape, 1);
        game->slots[i].occupied = 0;
    }
}

static void init_game_items(game_t *game, const char *item_files[])
{
    sfTexture *texture_item;

    for (int i = 0; i < 4; ++i) {
        game->items[i].sprite = sfSprite_create();
        texture_item = sfTexture_createFromFile(item_files[i], NULL);
        sfSprite_setTexture(game->items[i].sprite, texture_item, sfTrue);
        sfSprite_setPosition
        (game->items[i].sprite, (sfVector2f){-1000, -1000});
        game->items[i].original_position =
        (sfVector2f){625 + (i % 6) * 150, 93 + (i / 6) * 145};
        game->items[i].being_dragged = 0;
    }
    init_rectangles(game);
}

void init_structs(game_t *game, const char *item_files[],
    sfRenderWindow *window)
{
    game->items = malloc(sizeof(item_t) * 4);
    init_game_items(game, item_files);
    for (int i = 0; i < 30; ++i)
        sfRectangleShape_setPosition(game->slots[i].shape,
        (sfVector2f){625 + (i % 6) * 150, 93 + (i / 6) * 145});
    for (int i = 0; i < 4; ++i)
        game->slots[i].occupied = 1;
    init_structsp2(game, window);
    init_player(game);
}
