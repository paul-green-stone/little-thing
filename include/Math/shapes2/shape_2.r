#ifndef LITTLETHING_SHAPE_2_H
#define LITTLETHING_SHAPE_2_H

/* ================================================================ */

/**
 * All the methods/functions an instance of a `Shape_2` class/struct must support.
 * It can also be viewed as a type description of `Shape_2`, or a virtual table
 * mimicking run-time polymorphism.
 */
struct Shape_2 {

    /* ============================ FIELDS ============================ */

    /* How many bytes of memory to allocate for the given shape */
    size_t size;

    /* Figure, shape */
    int base_shape;

    /* =========================== METHODS ============================ */

    /* How to construct the given shape */
    void* (*ctor)(void* this, va_list* args);

    /* How to destroy the given shape */
    void* (*dtor)(void* this);

    /* ================================ */

    /* How to draw/fill the given shape */
    int (*fill)(const void* this, va_list* args);

    /* How to outline the given shape */
    int (*outline)(const void* this);

    /* How to copy the given shape */
    void* (*copy)(const void*, void*);

    /* How to rotate the given shape */
    int (*rotate)(void* this, float degrees);

    /* Get coordinates */
    int (*get_position)(const void* this, Vector2_t position);

    /* Check if two shapes collide (they must be the same) */
    int (*collide)(const void*, const void*);

    /* Provide information about the shape */
    void (*info)(const void* this);
};

/* ================================================================ */

#endif /* LITTLETHING_SHAPE_2_H */
