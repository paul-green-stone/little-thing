#ifndef LITTLETHING_MATH_H
#define LITTLETHING_MATH_H

#define PI 3.14159265358979323846f

/* ================================ */

#define deg2rad(degrees) ((degrees * PI) / 180.0f)

/* ================================ */

#define rad2deg(radian) (((radian) * 180.0f) / PI)

/* ================================ */

#define Point2_is_collide_Point2(p1, p2) (Vector2_is_collide_Vector2(p1, p2))

/* ================================================================ */

#include "vector2/vector2.h"
#include "shapes2/line2.h"

/* ================================================================ */

extern int float_is_equal(float f1, float f2);

/* ================================================================ */

#endif /* LITTLETHING_MATH_H */

