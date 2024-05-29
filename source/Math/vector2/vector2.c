#include "../../../include/littlething.h"

/* ================================================================ */

int Vector2_new(float x, float y, Vector2_t* vector) {

    if ((*vector = calloc(1, sizeof(struct vector_2))) == NULL) {
        return -1;
    }

    (*vector)->x = x;
    (*vector)->y = y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_destroy(Vector2_t* vector) {

    if ((vector == NULL) || (*vector == NULL)) {
        return -1;
    }

    free (*vector);

    *vector = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_add(const Vector2_t v1, const Vector2_t v2, Vector2_t r) {

    if ((v1 == NULL) || (v2 == NULL)) {
        return -1;
    }

    if (r == NULL) {
        r = v1;
    }

    r->x = v1->x + v2->x;
    r->y = v1->y + v2->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_sub(const Vector2_t v1, const Vector2_t v2, Vector2_t r) {

    if ((v1 == NULL) || (v2 == NULL)) {
        return -1;
    }

    if (r == NULL) {
        r = v1;
    }

    r->x = v1->x - v2->x;
    r->y = v1->y - v2->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_negate(const Vector2_t v) {

    if (v == NULL) {
        return -1;
    }

    v->x = -v->x;
    v->y = -v->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_mul_scalar(const Vector2_t v, float s, Vector2_t r) {

    if (v == NULL) {
        return -1;
    }

    if (r == NULL) {
        r = v;
    }

    r->x *= s;
    r->y *= s;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_div_scalar(const Vector2_t v, float d, Vector2_t r) {

    if (v == NULL) {
        return -1;
    }

    if (d == 0) {
        return -1;
    }

    if (r == NULL) {
        r = v;
    }

    r->x /= d;
    r->y /= d;

    /* ======== */

    return 0;
}

/* ================================================================ */

float Vector2_length(const Vector2_t v) {

    if (v == NULL) {
        return -1.0f;
    }

    /* ======== */

    return sqrtf((v->x * v->x) + (v->y * v->y));
}

/* ================================================================ */

int Vector2_normalize(const Vector2_t v, Vector2_t r) {

    float length = 0;

    if (v == NULL) {
        return -1;
    }

    if (r == NULL) {
        r = v;
    }

    length = Vector2_length(v);

    if (length > 0) {
        r->x = v->x / length;
        r->y = v->y / length;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_rotate(Vector2_t v, float degrees) {

    float radian = 0;

    float sine = 0;
    float cosine = 0;

    float x;
    float y;

    if (v == NULL) {
        return -1;
    }

    x = v->x;
    y = v->y;

    radian = deg2rad(degrees);

    sine = sinf(radian);
    cosine = cosf(radian);

    v->x = x * cosine - y * sine;
    v->y = x * sine + y * cosine;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_dot(const Vector2_t v1, const Vector2_t v2, float* result) {

    if ((v1 == NULL) || (v2 == NULL)) {
        return -1;
    }

    *result = v1->x * v2->x + v1->y * v2->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_angle_between(const Vector2_t v1, const Vector2_t v2, float* result) {

    struct vector_2 norm_v1;
    struct vector_2 norm_v2;

    float dot;

    if ((v1 == NULL) || (v2 == NULL)) {
        return -1;
    }

    if (result == NULL) {
        return -1;
    }

    Vector2_normalize(v1, &norm_v1);
    Vector2_normalize(v2, &norm_v2);

    if (Vector2_dot(&norm_v1, &norm_v2, &dot) != 0) {
        return -1;
    }

    *result = rad2deg(acosf(dot));

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_is_collide_Vector2(const Vector2_t v1, const Vector2_t v2) {

    if ((v1 == NULL) || (v2 == NULL)) {
        return 0;
    }

    /* ======== */

    return float_is_equal(v1->x, v2->x) && float_is_equal(v1->y, v2->y);
}

/* ================================================================ */

int Vector2_rotate_90(Vector2_t v) {

    float x;
    float y;

    if (v == NULL) {
        return -1;
    }

    x = v->x;
    y = v->y;

    v->x = -y;
    v->y = x;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vectors2_is_parallel(const Vector2_t v1, const Vector2_t v2) {

    Vector2 temp;
    float dot = 0;

    if ((v1 == NULL) || (v2 == NULL)) {
        return 0;
    }

    temp.x = v1->x;
    temp.y = v1->y;

    Vector2_rotate_90(&temp);
    Vector2_dot(&temp, v2, &dot);

    /* ======== */

    return float_is_equal(0.0f, dot);
}

/* ================================================================ */

int Vector2_is_equal(const Vector2_t v1, const Vector2_t v2) {

    if ((v1 == NULL) || (v2 == NULL)) {
        return 0;
    }

    /* ======== */

    return float_is_equal(v1->x - v2->x, 0) && float_is_equal(v1->y - v2->y, 0);
}

/* ================================================================ */

void Vector2_debug(const char* name, const Vector2_t v) {

    Vector2 temp;

    if (v == NULL) {
        return ;
    }

    Vector2_normalize(v, &temp);

    printf("%s->x = %.2f\t", name, v->x);
    printf("%s->y = %.2f\n", name, v->y);
    printf("%s length: %.2f\n", name, Vector2_length(v));
    printf("unit vector is: [%.2f; %.2f]\n\n", temp.x, temp.y);
}

/* ================================================================ */
