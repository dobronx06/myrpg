/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** handle_event
*/

#include "../include/menu.h"

void resize(menu_t *menu, sfEvent *event)
{
    sfVector2u sizeWindow = sfRenderWindow_getSize(menu->window);
    sfVector2f ratio = {(float)menu->windowSize.x / (float)sizeWindow.x,
    (float)menu->windowSize.y / (float)sizeWindow.y};

    if (event->type == sfEvtMouseMoved){
        event->mouseMove.x *= ratio.x;
        event->mouseMove.y *= ratio.y;
    }
    if (event->type == sfEvtMouseButtonPressed){
        event->mouseButton.x *= ratio.x;
        event->mouseButton.y *= ratio.y;
    }
}

static void set_color(sfEvent *event, bouton_t *button)
{
    while (button != NULL) {
        sfSprite_setTexture(button->spriteBouton,
            sfFloatRect_contains
            (&button->boundsBouton, event->mouseMove.x, event->mouseMove.y) ?
            button->textureSecondBouton : button->textureBouton, sfTrue);
        button = button->nextbouton;
    }
}

static sfRenderWindow* create_new_window(sfVector2u size,
    sfUint32 style, menu_t *menu)
{
    sfRenderWindow *window = sfRenderWindow_create
    ((sfVideoMode){size.x, size.y, 32}, "My_RPG", style, NULL);
    const sfView *view = NULL;

    sfRenderWindow_setSize(menu->window, size);
    view = sfRenderWindow_getView(menu->window);
    sfRenderWindow_close(menu->window);
    sfRenderWindow_setView(window, view);
    return window;
}

static void change_window_size(bouton_t *button, menu_t *menu)
{
    sfVector2u size;

    switch (button->id) {
    case 5:
        size = (sfVector2u){1920, 1080};
        menu->style = sfFullscreen | sfClose | sfResize;
        break;
    case 6:
        size = (sfVector2u){1600, 900};
        menu->style = sfClose | sfResize;
        break;
    case 7:
        size = (sfVector2u){960, 540};
        menu->style = sfClose | sfResize;
        break;
    default:
        return;
    }
    menu->window = create_new_window(size, menu->style, menu);
}

static void play(bouton_t *button, menu_t *menu)
{
    if (button->id == 0){
        first_map(menu->window);
    }
}

static void close_window(bouton_t *button, menu_t *menu)
{
    if (button->id == 2)
        sfRenderWindow_close(menu->window);
}

static void button_clicked(sfEvent *event, bouton_t *button, menu_t *menu)
{
    while (button != NULL) {
        if (sfFloatRect_contains
        (&button->boundsBouton, event->mouseButton.x, event->mouseButton.y)) {
            play(button, menu);
            menu->current_scene = (button->id == 1) ? 1 : menu->current_scene;
            menu->current_scene = (button->id == 4) ? 0 : menu->current_scene;
            close_window(button, menu);
            change_window_size(button, menu);
        }
        button = button->nextbouton;
    }
}

void check_is_clicked_knob(menu_t *menu)
{
    sfVector2f mousePos;

    if (menu->event.type == sfEvtMouseButtonPressed) {
        mousePos = (sfVector2f){menu->event.mouseButton.x,
            menu->event.mouseButton.y};
        if (sfRectangleShape_getGlobalBounds(menu->knob).left <= mousePos.x &&
            mousePos.x <= sfRectangleShape_getGlobalBounds(menu->knob).left +
            sfRectangleShape_getGlobalBounds(menu->knob).width &&
            sfRectangleShape_getGlobalBounds(menu->knob).top <= mousePos.y &&
            mousePos.y <= sfRectangleShape_getGlobalBounds(menu->knob).top +
            sfRectangleShape_getGlobalBounds(menu->knob).height) {
            menu->isPressed = sfTrue;
        }
    }
}

void change_volume_music(menu_t *menu)
{
    float posX;
    float volume;

    if (menu->event.type == sfEvtMouseMoved) {
        posX = (float)menu->event.mouseMove.x;
        if (posX < 805)
            posX = 805;
        if (posX > 1170)
            posX = 1170;
        sfRectangleShape_setPosition(menu->knob, (sfVector2f){posX, 695});
        volume = (posX - 805) / 200;
        sfMusic_setVolume(menu->music, volume * 100);
    }
}

void handle_event(sfEvent *event, menu_t *menu)
{
    if (menu->event.type == sfEvtClosed)
        sfRenderWindow_close(menu->window);
    if (event->type == sfEvtMouseMoved) {
        set_color(event, menu->cur_buttons);
    }
    if (event->type == sfEvtMouseButtonPressed) {
        button_clicked(event, menu->cur_buttons, menu);
        check_is_clicked_knob(menu);
    } else if (event->type == sfEvtMouseButtonReleased) {
        menu->isPressed = sfFalse;
    }
    if (event->type == sfEvtMouseMoved && menu->isPressed == sfTrue) {
        change_volume_music(menu);
    }
}
