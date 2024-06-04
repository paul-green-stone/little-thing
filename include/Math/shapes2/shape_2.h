#ifndef LITTLETHING_SHAPE2_H
#define LITTLETHING_SHAPE2_H

#include "../../littlething.h"
#include "shape_2.r"

/* ================================================================ */

/**
 * Create a new instance of a `Shape_2` class/struct.
*/
extern void* Shape_new(const void* shape, ...);

/* ================================================================ */

extern int Shape_destroy(void* shape);

/* ================================================================ */

extern int Shape_draw(const void* shape, ...);

/* ================================================================ */

extern void* Shape_copy(const void* shape);

/* ================================================================ */

extern int Shape_rotate(void* shape, float degrees);

/* ================================================================ */

extern int Shape_outline(const void* shape);

/* ================================================================ */

extern int Shape_get_pos(const void* shape, Vector2_t position);

/* ================================================================ */

extern char* Shape_get_type(const void* shape);

/* ================================================================ */

extern int Shape_belongs_to(const void* shape);

/* ================================================================ */

extern int Shapes_is_collide(const void* shape_1, const void* shape_2);

/* ================================================================ */

extern int Shape_info(const void* shape);

/* ================================================================ */

#endif /* LITTLETHING_SHAPE2_H */