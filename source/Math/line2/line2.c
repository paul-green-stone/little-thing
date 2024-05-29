#include "../../../include/littlething.h"

/* ================================================================ */

int Line2_new(float base_x, float base_y, float dir_x, float dir_y, Line2_t* line) {

    if ((*line = calloc(1, sizeof(Line2))) == NULL) {
        return -1;
    }

    (*line)->base.x = base_x;
    (*line)->base.y = base_y;

    (*line)->direction.x = dir_x;
    (*line)->direction.y = dir_y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Line2_destroy(Line2_t* line) {

    if ((line == NULL) || (*line == NULL)) {
        return -1;
    }

    free(*line);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Lines2_is_equivalent(const Line2_t a, const Line2_t b) {

    Vector2 temp;

    if ((a == NULL) || (b == NULL)) {
        return 0;
    }    

    if (!Vectors2_is_parallel(&a->direction, &b->direction)) {
        return 0;
    }

    Vector2_sub(&a->base, &b->base, &temp);

    /* ======== */

    return Vectors2_is_parallel(&temp, &a->direction);
}

/* ================================================================ */

int Lines2_is_collide(const Line2_t a, const Line2_t b) {

    if ((a == NULL) || (b == NULL)) {
        return 0;
    }

    if (Vectors2_is_parallel(&a->direction, &b->direction)) {
        return Lines2_is_equivalent(a, b);
    }

    /* ======== */

    return 1;
}

/* ================================================================ */

int Line2_draw(const Line2_t line, int length) {

    if (line == NULL) {
        return -1;
    }

    /* ======== */

    return SDL_RenderDrawLine(g_app->window->r, line->base.x - line->direction.x * length, line->base.y - line->direction.y * length, line->base.x + line->direction.x * length, line->base.y + line->direction.y * length);
}

/* ================================================================ */
