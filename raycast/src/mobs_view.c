/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** mobs_view
*/

#include "../include/my.h"

bool is_within_range(mob_t *mob, engine_t *data, float range)
{
    float dx = data->posX - mob->x;
    float dy = data->posY - mob->y;

    return (dx * dx + dy * dy) <= (range * range);
}

static void move_toward_player(engine_t *data, mob_t *mob, float speed)
{
    float dx = data->posX - mob->x;
    float dy = data->posY - mob->y;
    float length = sqrt(dx * dx + dy * dy);
    float newX = 0;
    float newY = 0;

    if (length > 0) {
        dx /= length;
        dy /= length;
    }
    newX = mob->x + dx * speed;
    newY = mob->y + dy * speed;
    if (data->worldMap[(int)newX][(int)newY] == 0) {
        mob->x = newX;
        mob->y = newY;
    }
}

void update_mob_state(engine_t *data, int i)
{
    if (data->sprites[i].health <= 0) {
        data->sprites[i].is_alive = false;
    }
}

void attack_mobs(engine_t *data, player_t *player, int i)
{
    mob_t *mob = &data->sprites[i];

    if (is_within_range(mob, data, 0.5)) {
        if (sfSound_getStatus(mob->attack_sfx) != sfPlaying) {
            sfSound_play(mob->attack_sfx);
            player->health -= 10;
            printf("Player health: %d\n", player->health);
        }
    }
}

static void update_mobs2(engine_t *data, mob_t *mob, player_t *player, int i)
{
    float fov_radius = 6.0;
    float mob_speed = 0.03;

    if (mob->is_alive) {
        if (is_within_range(mob, data, fov_radius)) {
            move_toward_player(data, mob, mob_speed);
        }
        update_mob_state(data, i);
        attack_mobs(data, player, i);
    }
}

void update_mobs(engine_t *data, quest_t *quest, player_t *player)
{
    mob_t *mob = NULL;

    for (int i = 0; i < quest->end_ojb; i++) {
        mob = &data->sprites[i];
        update_mobs2(data, mob, player, i);
    }
}

void already_killed(quest_t *quest, int id)
{
    for (int i = 0; i < quest->end_ojb; i++) {
        if (id == quest->id_counted[i])
            return;
    }
    quest->ojb_progress++;
    quest->id_counted[quest->next_free_index] = id;
    quest->next_free_index++;
}
