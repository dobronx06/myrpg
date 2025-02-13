/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** math
*/

#include "../include/my.h"

float custom_pow(float x, float y)
{
    float result = 1.0;

    while (y != 0) {
        result *= x;
        --y;
    }
    return result;
}

float custom_abs(float x)
{
    return x < 0 ? -x : x;
}

double custom_sqrt(double x)
{
    double y;
    int p = 0;
    int square;
    int c = 0;

    do {
        p++;
        square = (p + 1) * (p + 1);
    } while (x > square);
    y = (double)p;
    while (c < 10) {
        y = (x / y + y) / 2;
        if (y * y == x)
            return (y);
        c++;
    }
    return (y);
}

float calculate_distance(sfVector2i mouse_pos, sfVector2f slot_pos)
{
    return custom_sqrt(custom_pow(mouse_pos.x - slot_pos.x, 2) +
    custom_pow(mouse_pos.y - slot_pos.y, 2));
}
