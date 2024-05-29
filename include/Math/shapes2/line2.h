#ifndef LITTLETHING_LINE_H
#define LITTLETHING_LINE_H

#include "../../littlething.h"

/* ================================ */

typedef struct line_2 {

    /* A base point */
    Point2 base;

    /* A line's direction */
    Vector2 direction;
} Line2;

typedef struct line_2* Line2_t;

/* ================================================================ */

extern int Line2_new(float base_x, float base_y, float dir_x, float dir_y, Line2_t* line);

/* ================================================================ */

extern int Line2_destroy(Line2_t* line);

/* ================================================================ */

extern int Lines2_is_equivalent(const Line2_t a, const Line2_t b);

/* ================================================================ */

extern int Lines2_is_collide(const Line2_t a, const Line2_t b);

/* ================================================================ */

extern int Line2_draw(const Line2_t line, int length);

/* ================================================================ */

#endif /* LITTLETHING_LINE_H */
