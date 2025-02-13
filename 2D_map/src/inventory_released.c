/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** inventory_released
*/

#include "../include/my.h"

void cond_handle_slots(float *min_distance, int *nearest_slot,
    int i, float distance)
{
    if (*min_distance == -1.0f || distance < *min_distance) {
        *min_distance = distance;
        *nearest_slot = i;
    }
}

void handle_slots(game_t *game, float *min_distance, int *nearest_slot)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f slot_pos;
    float distance;

    for (int i = 0; i < NUM_SLOTS; ++i) {
        if (game->slots[i].occupied == 0) {
            slot_pos = sfRectangleShape_getPosition(game->slots[i].shape);
            distance = custom_sqrt(custom_pow(mouse_pos.x - slot_pos.x, 2)
                + custom_pow(mouse_pos.y - slot_pos.y, 2));
            cond_handle_slots(min_distance, nearest_slot, i, distance);
        }
    }
}

void neighbour_slots(game_t *game, item_t **dragging_item, int nearest_slot,
    int *previous_slot)
{
    sfVector2f near_slot_pos;
    sfVector2f prev_slot_pos;

    if (nearest_slot != -1) {
        near_slot_pos =
            sfRectangleShape_getPosition(game->slots[nearest_slot].shape);
        sfSprite_setPosition((*dragging_item)->sprite, near_slot_pos);
        (*dragging_item)->original_position =
            sfSprite_getPosition((*dragging_item)->sprite);
        game->slots[nearest_slot].occupied = 1;
        return;
    }
    if (*previous_slot != -1) {
        prev_slot_pos =
            sfRectangleShape_getPosition(game->slots[*previous_slot].shape);
        sfSprite_setPosition((*dragging_item)->sprite, prev_slot_pos);
        (*dragging_item)->original_position =
            sfSprite_getPosition((*dragging_item)->sprite);
        game->slots[*previous_slot].occupied = 1;
    }
}

void evt_button_released2(game_t *game, item_t **dragging_item,
    int *previous_slot)
{
    int nearest_slot = -1;
    float min_distance = -1.0f;

    if (*dragging_item && (*dragging_item)->being_dragged) {
        handle_slots(game, &min_distance, &nearest_slot);
        neighbour_slots(game, dragging_item, nearest_slot, previous_slot);
        (*dragging_item)->being_dragged = 0;
        *dragging_item = NULL;
        *previous_slot = -1;
    }
}

void evt_button_released(game_t *game, item_t **dragging_item,
    int *previous_slot)
{
    sfEvent *event = &game->event;

    if (event->type == sfEvtMouseButtonReleased &&
        event->mouseButton.button == sfMouseLeft)
        evt_button_released2(game, dragging_item, previous_slot);
}
