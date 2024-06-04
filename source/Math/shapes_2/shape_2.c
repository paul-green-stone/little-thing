#include "../../../include/littlething.h"
#include "../../../include/Math/shapes2/shape_2.r"

/* ================================================================ */

void* Shape_new(const void* shape, ...) {

    /* 
        Every shape struct contains a virtual table/type description
        as the first member field, so casting it to `Shape_2` allows us to get access to `Shape_2`
        internal information
    */
    const struct Shape_2* this = shape;

    void* new_shape = NULL;

    /* ======== */

    if (this == NULL) {
        return NULL;
    }

    /* Dynamically allocate memory for a new instance of the `Shape_2` class/struct */
    if ((new_shape = calloc(1, this->size)) == NULL) {
        return NULL;
    }

    *(const struct Shape_2**) new_shape = this;

    /* ======== */

    if (this->ctor) {

        va_list args;
        va_start(args, shape);

        new_shape = this->ctor(new_shape, &args);

        va_end(args);
    }

    /* ======== */

    return new_shape;
}

/* ================================================================ */

int Shape_destroy(void* shape) {

    const struct Shape_2** this = shape;

    /* ======== */

    if ((shape) && (*this) && (*this)->dtor) {
        shape = (*this)->dtor(shape);
    }

    free(shape);

    /* ======== */

    return 0;
}

/* ================================================================ */

void* Shape_copy(const void* this_shape) {

    const struct Shape_2* const *original_shape = this_shape;
    void* copied_shape = NULL;

    /* ======== */

    if ((this_shape == NULL) || (*original_shape == NULL) || ((*original_shape)->copy == NULL)) {
        return NULL;
    }

    if ((copied_shape = calloc(1, (*original_shape)->size)) == NULL) {
        return NULL;
    }

    *(const struct Shape_2**) copied_shape = *original_shape;

    copied_shape = (*original_shape)->copy(this_shape, copied_shape);

    /* ======== */

    return copied_shape;
}

/* ================================================================ */

int Shape_rotate(void* shape, float degrees) {

    const struct Shape_2* const *this = shape;

    /* ======== */

    if ((shape == NULL) || (*this == NULL) || ((*this)->rotate == NULL)) {
        return -1;
    }

    (*this)->rotate(shape, degrees);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Shape_info(const void* _shape) {

    const struct Shape_2* const *this = _shape;

    /* ======== */

    if (this == NULL) {
        return -1;
    }

    (*this)->info(_shape);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Shape_belongs_to(const void* this_shape) {

    const struct Shape_2* const *this = this_shape;

    if ((this_shape == NULL) || (*this == NULL)) {
        return -1;
    }

    /* ======== */

    return (*this)->base_shape;
}

/* ================================================================ */

int Shape_draw(const void* shape, ...) {

    const struct Shape_2* const *this = shape;

    int result = 0;

    if ((shape == NULL) || (*this == NULL) || ((*this)->fill == NULL)) {
        return -1;
    }

    /* ======== */

    va_list args;
    va_start(args, shape);

    result = (*this)->fill(shape, &args);

    va_end(args);

    /* ======== */

    return result;
}

/* ================================================================ */

int Shape_get_pos(const void* this_shape, Vector2_t position) {

    const struct Shape_2* const *this = this_shape;

    if ((this_shape == NULL) || (*this == NULL) || ((*this)->get_position == NULL) || (position == NULL)) {
        return -1;
    }

    /* ======== */

    return (*this)->get_position(this_shape, position);
}

/* ================================================================ */

int Shapes_is_collide(const void* shape_1, const void* shape_2) {

    const struct Shape_2* const *a = shape_1;
    const struct Shape_2* const *b = shape_2;

    int type_1;
    int type_2;

    /* ======== */

    if ((shape_1 == NULL) || (shape_2 == NULL)) {
        return 0;
    }

    if (((*a)->collide == NULL) || ((*b)->collide == NULL)) {
        return 0;
    }

    type_1 = (*a)->base_shape;
    type_2 = (*b)->base_shape;

    /* ======== */

    if (type_1 == type_2){
        return (*a)->collide(shape_1, shape_2);
    }
    else {
        return 0;
    }
}

/* ================================================================ */
