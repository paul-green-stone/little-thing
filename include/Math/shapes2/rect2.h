#ifndef LITTLETHING_RECT2_H
#define LITTLETHING_RECT2_H

#include "../../littlething.h"

/* ================================ */

typedef struct rect_2 {

    Vector2 position;

    int width;
    int height;
} Rect2;

typedef struct rect_2* Rect2_t;

/* ================================================================ */

extern int Rect2_new(float x, float y, int width, int height, Rect2_t* rect);

/* ================================================================ */

extern int Rect2_destroy(Rect2_t* rect);

/* ================================================================ */

extern int Rect2_draw(const Rect2_t rect);

/* ================================================================ */

extern int Rect2_outline(const Rect2_t rect);

/* ================================================================ */

extern int Rects2_is_collide(const Rect2_t r1, const Rect2_t r2);

/* ================================================================ */

#endif /* LITTLETHING_RECT2_H */