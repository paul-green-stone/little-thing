#ifndef LITTLETHING_VECTOR2_H
#define LITTLETHING_VECTOR2_H

#include "../../littlething.h"

/* ================================ */

struct vector_2 {

    float x;
    float y;
};

typedef struct vector_2* Vector2_t;

/* ================================================================ */

extern int Vector2_new(float x, float y, Vector2_t* vector);

/* ================================================================ */

extern int Vector2_destroy(Vector2_t* vector);

/* ================================================================ */

extern int Vector2_add(const Vector2_t v1, const Vector2_t v2, Vector2_t r);

/* ================================================================ */

extern int Vector2_sub(const Vector2_t v1, const Vector2_t v2, Vector2_t r);

/* ================================================================ */

extern int Vector2_negate(const Vector2_t v);

/* ================================================================ */

extern int Vector2_mul_scalar(const Vector2_t v, float s, Vector2_t r);

/* ================================================================ */

extern int Vector2_div_scalar(const Vector2_t v, float d, Vector2_t r);

/* ================================================================ */

extern float Vector2_length(const Vector2_t v);

/* ================================================================ */

extern int Vector2_normalize(const Vector2_t v, Vector2_t r);

/* ================================================================ */

extern int Vector2_rotate(Vector2_t v, float degrees);

/* ================================================================ */

extern int Vector2_dot(const Vector2_t v1, const Vector2_t v2, float* result); 

/* ================================================================ */

extern int Vector2_angle_between(const Vector2_t v1, const Vector2_t v2, float* result);

/* ================================================================ */

#endif /* LITTLETHING_VECTOR2_H */