/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** inventory
*/

#include "../include/my.h"

static void toggle_inventory_visibility(sfSprite *inventory,
    sfSprite *sprite, int inventory_visible)
{
    if (inventory_visible) {
        sfSprite_setPosition(inventory, (sfVector2f){0, 0});
        sfSprite_setPosition(sprite, (sfVector2f){50, -50});
    } else {
        sfSprite_setPosition(inventory, (sfVector2f){-1000, -1000});
        sfSprite_setPosition(sprite, (sfVector2f){-1000, -1000});
    }
}

static void set_items_position(item_t *items, int inventory_visible)
{
    if (inventory_visible) {
        for (int i = 0; i < NUM_ITEMS; i++) {
            sfSprite_setPosition(items[i].sprite, items[i].original_position);
        }
    } else {
        for (int i = 0; i < NUM_ITEMS; i++) {
            items[i].original_position = sfSprite_getPosition(items[i].sprite);
            sfSprite_setPosition(items[i].sprite, (sfVector2f){-1000, -1000});
        }
    }
}

int find_nearest_slot(slot_t *slots, sfVector2i mouse_pos)
{
    float min_distance = -1.0f;
    int nearest_slot = -1;
    sfVector2f slot_pos;
    float distance;

    for (int i = 0; i < NUM_SLOTS; ++i) {
        if (slots[i].occupied == 0) {
            slot_pos = sfRectangleShape_getPosition(slots[i].shape);
            distance = calculate_distance(mouse_pos, slot_pos);
            min_distance = (min_distance == -1.0f ||
            distance < min_distance) ? distance : min_distance;
            nearest_slot = (min_distance == -1.0f ||
            distance < min_distance) ? i : nearest_slot;
        }
    }
    return nearest_slot;
}

static void drop_dragging_item2(item_t **dragging_item, slot_t *slots,
    int nearest_slot, sfVector2f original_position)
{
    sfVector2f slot_pos;

    if (nearest_slot != -1) {
        slot_pos = sfRectangleShape_getPosition(slots[nearest_slot].shape);
        sfSprite_setPosition((*dragging_item)->sprite, slot_pos);
        (*dragging_item)->original_position =
            sfSprite_getPosition((*dragging_item)->sprite);
        slots[nearest_slot].occupied = 1;
    } else {
        sfSprite_setPosition((*dragging_item)->sprite, original_position);
    }
}

void drop_dragging_item(item_t **dragging_item, game_t *game)
{
    sfVector2f original_position;
    sfVector2i mouse_pos;
    int nearest_slot;

    if (*dragging_item != NULL) {
        original_position = (*dragging_item)->original_position;
        mouse_pos = sfMouse_getPositionRenderWindow(game->window);
        nearest_slot = find_nearest_slot(game->slots, mouse_pos);
        drop_dragging_item2(dragging_item, game->slots, nearest_slot,
            original_position);
        sfSprite_setPosition((*dragging_item)->sprite,
            (sfVector2f){-1000, -1000});
        (*dragging_item)->being_dragged = 0;
        *dragging_item = NULL;
    }
}

void handle_inventory(game_t *game, item_t **dragging_item)
{
    static int inventory_visible = 0;
    sfEvent *event = &game->event;

    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyI) {
        inventory_visible = !inventory_visible;
        toggle_inventory_visibility(game->inventory, game->sprite,
            inventory_visible);
        set_items_position(game->items, inventory_visible);
        if (!inventory_visible) {
            drop_dragging_item(dragging_item, game);
        }
    }
}

void handle_drag_and_drop(game_t *game, item_t **dragging_item)
{
    static sfVector2f offset;
    static int previous_slot = -1;
    sfEvent *event = &game->event;
    sfVector2i mouse_pos;

    evt_button_pressed(game, dragging_item, &offset, &previous_slot);
    evt_button_released(game, dragging_item, &previous_slot);
    if (event->type == sfEvtMouseMoved && *dragging_item &&
        (*dragging_item)->being_dragged) {
        mouse_pos = sfMouse_getPositionRenderWindow(game->window);
        sfSprite_setPosition((*dragging_item)->sprite,
            (sfVector2f){mouse_pos.x - offset.x, mouse_pos.y - offset.y});
    }
}
