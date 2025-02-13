/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** pause_menu
*/

#include "../include/my.h"

void disp_button(sfRenderWindow *window, bouton_t *button)
{
    while (button != NULL) {
        sfRenderWindow_drawSprite(window, button->spriteBouton, NULL);
        button = button->nextbouton;
    }
}

void display_button_pause(menu_t *menu)
{
    add_button(&menu->button_pause, init_bouton(create_button(),
        "menu/assets/bouton_jouer", (sfVector2f){1920 / 2 - 100, 300},
        (sfVector2f){0.2, 0.2}));
    add_button(&menu->button_pause, init_bouton(create_button(),
        "menu/assets/bouton_quitter",
        (sfVector2f){1920 / 2 - 100, 500}, (sfVector2f){0.2, 0.2}));
}

void create_all_button_pause(menu_t *menu)
{
    display_button_pause(menu);
    disp_button(menu->window, menu->button_pause);
}

void init_bouton_pause(game_t *data)
{
    data->menu = malloc(sizeof(menu_t));
    data->menu->button_pause = NULL;
    data->menu->current_scene = 0;
    data->menu->window = data->window;
}

static void handle_pause_event(game_t *data)
{
    if (data->event.type == sfEvtClosed) {
        sfRenderWindow_close(data->window);
        return;
    }
}

static void initialize_and_get_bounds(game_t *data, sfFloatRect *boundsBouton,
    sfFloatRect *boundsBouton2)
{
    init_bouton_pause(data);
    sfRenderWindow_setMouseCursorVisible(data->window, sfTrue);
    create_all_button_pause(data->menu);
    sfRenderWindow_display(data->window);
    *boundsBouton = sfSprite_getGlobalBounds
    (data->menu->button_pause->spriteBouton);
    *boundsBouton2 = sfSprite_getGlobalBounds
    (data->menu->button_pause->nextbouton->spriteBouton);
}

static void handle_pause_logic(game_t *data, sfFloatRect boundsBouton,
    sfFloatRect boundsBouton2)
{
    sfVector2i mousePos;

    while (1) {
        mousePos = sfMouse_getPositionRenderWindow(data->window);
        if (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfFloatRect_contains(&boundsBouton, mousePos.x, mousePos.y)) {
            sfRenderWindow_setMouseCursorVisible(data->window, sfFalse);
            break;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfFloatRect_contains(&boundsBouton2, mousePos.x, mousePos.y)) {
            sfRenderWindow_close(data->window);
            break;
        }
        while (sfRenderWindow_pollEvent(data->window, &data->event)) {
            handle_pause_event(data);
        }
    }
}

void draw_pause(game_t *data)
{
    sfFloatRect boundsBouton;
    sfFloatRect boundsBouton2;

    initialize_and_get_bounds(data, &boundsBouton, &boundsBouton2);
    handle_pause_logic(data, boundsBouton, boundsBouton2);
}
