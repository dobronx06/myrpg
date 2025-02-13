/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** create_button
*/

#include "../include/menu.h"

void add_button(bouton_t **head, bouton_t *new_button)
{
    bouton_t *tmp = *head;

    if (*head == NULL) {
        *head = new_button;
        return;
    }
    while (tmp->nextbouton != NULL)
        tmp = tmp->nextbouton;
    tmp->nextbouton = new_button;
}

bouton_t *create_button(void)
{
    bouton_t *new_button = malloc(sizeof(bouton_t));
    static int id = 0;

    new_button->id = id;
    id++;
    return new_button;
}

bouton_t *init_bouton(bouton_t *new_button, const char *texturePathPrefix,
    sfVector2f pos, sfVector2f size)
{
    char normalTexturePath[100];
    char hoverTexturePath[100];

    sprintf(normalTexturePath, "%s.png", texturePathPrefix);
    sprintf(hoverTexturePath, "%s2.png", texturePathPrefix);
    new_button->textureBouton =
    sfTexture_createFromFile(normalTexturePath, NULL);
    new_button->textureSecondBouton =
    sfTexture_createFromFile(hoverTexturePath, NULL);
    new_button->spriteBouton = sfSprite_create();
    sfSprite_setTexture
    (new_button->spriteBouton, new_button->textureBouton, sfTrue);
    new_button->posBouton = pos;
    sfSprite_setPosition(new_button->spriteBouton, new_button->posBouton);
    sfSprite_setScale(new_button->spriteBouton, size);
    new_button->boundsBouton =
    sfSprite_getGlobalBounds(new_button->spriteBouton);
    new_button->nextbouton = NULL;
    return new_button;
}

void display_buttons(sfRenderWindow *window, bouton_t *button, menu_t *menu)
{
    while (button != NULL) {
        sfRenderWindow_drawSprite(window, button->spriteBouton, NULL);
        button = button->nextbouton;
    }
    if (menu->cur_buttons == menu->button_settings) {
        sfRenderWindow_drawSprite(window, menu->spriteSlider, NULL);
        sfRenderWindow_drawRectangleShape(window, menu->knob, NULL);
    }
}
