#ifndef LITTLETHING_ENTITY_H
#define LITTLETHING_ENTITY_H

#include "../littlething.h"

/* ================================ */

typedef struct entity_2 {

    /* An entity's shape is used in a collision detection system to determine if it collides with other objects */
    int type;

    Vector2 g_pos;
    Vector2 l_pos;

    union {
        Rect2 rect;
    } shape;

} Entity2;

typedef struct entity_2* Entity2_t;

/* ================================================================ */

extern int Entity2_new(int type, Entity2_t* entity);

/* ================================================================ */

#endif /* LITTLETHING_ENTITY_H */
