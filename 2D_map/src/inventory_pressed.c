/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** inventory_pressed
*/

#include "../include/my.h"

void evt_button_pressed3(game_t *game, item_t **dragging_item,
    int *previous_slot)
{
    sfVector2f slot_pos;

    for (int j = 0; j < NUM_SLOTS; ++j) {
        slot_pos = sfRectangleShape_getPosition(game->slots[j].shape);
        if (custom_abs(slot_pos.x - (*dragging_item)->original_position.x)
            < 1.0f && custom_abs(slot_pos.y -
            (*dragging_item)->original_position.y) < 1.0f) {
            game->slots[j].occupied = 0;
            *previous_slot = j;
            break;
        }
    }
}

void evt_button_pressed2(game_t *game, item_t **dragging_item,
    sfVector2f *offset, int *previous_slot)
{
    sfFloatRect item_bounds;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);

    for (int i = 0; i < NUM_ITEMS; i++) {
        item_bounds = sfSprite_getGlobalBounds(game->items[i].sprite);
        if (sfFloatRect_contains(&item_bounds, mouse_pos.x, mouse_pos.y)) {
            *dragging_item = &game->items[i];
            (*dragging_item)->being_dragged = 1;
            offset->x = mouse_pos.x - item_bounds.left;
            offset->y = mouse_pos.y - item_bounds.top;
            evt_button_pressed3(game, dragging_item, previous_slot);
            break;
        }
    }
}

void evt_button_pressed(game_t *game, item_t **dragging_item,
    sfVector2f *offset, int *previous_slot)
{
    sfEvent *event = &game->event;

    if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft)
        evt_button_pressed2(game, dragging_item, offset, previous_slot);
}
