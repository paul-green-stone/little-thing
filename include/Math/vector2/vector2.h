#ifndef LITTLETHING_VECTOR2_H
#define LITTLETHING_VECTOR2_H

#include "../../littlething.h"

/* ================================ */

typedef struct vector_2 {

    float x;
    float y;
} Vector2;

typedef struct vector_2 Point2;

typedef struct vector_2* Vector2_t;

/* ================================================================ */

#define __v2_debug(v) (Vector2_debug(#v, v))

#define Vector2_NULL(v) (Vector2_new(0.f, 0.f, v))

/* ================================================================ */

extern void Vector2_debug(const char* name, const Vector2_t v);

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

extern int Vector2_rotate_90(Vector2_t v);

/* ================================================================ */

extern int Vector2_dot(const Vector2_t v1, const Vector2_t v2, float* result); 

/* ================================================================ */

extern int Vector2_angle_between(const Vector2_t v1, const Vector2_t v2, float* result);

/* ================================================================ */

extern int Vector2_is_collide_Vector2(const Vector2_t v1, const Vector2_t v2);

/* ================================================================ */

extern int Vectors2_is_parallel(const Vector2_t v1, const Vector2_t v2);

/* ================================================================ */

extern int Vector2_is_equal(const Vector2_t v1, const Vector2_t v2);

/* ================================================================ */

#endif /* LITTLETHING_VECTOR2_H */