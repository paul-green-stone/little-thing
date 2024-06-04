#include "../../../../include/littlething.h"
#include "../../../../include/Math/shapes2/shape_2.r"

/* ================================ */

struct Line_2 {

    /* Always must be first */
    const void* _class;

    /* =============== */

    Point2 base_point;

    Vector2 direction;
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/**
 * A `Line_2` constructor
 */
static void* Line_2__ctor(void* _this, va_list* args) {
    
    /* Cast `_this` (originally `void*`) to a pointer to a `Line_2` struct/class */
    struct Line_2* this = _this;

    /* Base Point */
    double b_x = 0;
    double b_y = 0;

    /* Direction */
    double d_x = 0;
    double d_y = 0;

    /* ======== */

    /* Retrieve arguments if provided */
    b_x = va_arg(*args, double);
    b_y = va_arg(*args, double);

    d_x = va_arg(*args, double);
    d_y = va_arg(*args, double);

    this->base_point.x = (float) b_x;
    this->base_point.y = (float) b_y;

    this->direction.x = (float) d_x;
    this->direction.y = (float) d_y;

    /* ======== */

    return this;
}

/* ================================================================ */

/**
 * A `Line_2` destructor
 */
static void* Line_2__dtor(void* _this) {

    struct Line_2* this = _this;

    /* ======== */

    /* Zeroing the "instance" fields */
    this->base_point = (Point2) {0, 0};
    this->direction = (Vector2) {0, 0};

    /* ======== */

    return this;
}

/* ================================================================ */

static int Line_2__draw(const void* _this, va_list* args) {

    const struct Line_2* this = _this;

    /* Line length */
    int length = va_arg(*args, int);

    /* ======== */

    return SDL_RenderDrawLine(g_app->window->r, this->base_point.x - this->direction.x * length, this->base_point.y - this->direction.y * length, this->base_point.x +this->direction.x * length, this->base_point.y + this->direction.y * length);
}

/* ================================================================ */

static void* Line_2__copy(const void* the_one_to_be_copied, void* _this) {

    const struct Line_2* const original_line = the_one_to_be_copied;
    struct Line_2* copied_line = _this;

    /* ======== */

    copied_line->base_point.x = original_line->base_point.x;
    copied_line->base_point.y = original_line->base_point.y;

    copied_line->direction.x = original_line->direction.x;
    copied_line->direction.y = original_line->direction.y;

    /* ======== */

    return copied_line;
}

/* ================================================================ */

static int Line_2__rotate(void* _this, float degrees) {

    struct Line_2* this = _this;

    /* ======== */

    return Vector2_rotate(&this->direction, degrees);
}

/* ================================================================ */

static void Line_2__info(const void* _this) {

    const struct Line_2* this = _this;

    /* ======== */

    printf("%-16s: %s\n", "type", "Line_2");
    printf("%-16s: [%.2f; %.2f]\n", "Base Point", this->base_point.x, this->base_point.y);
    printf("%-16s: [%.2f; %.2f]\n", "Direction", this->direction.x, this->direction.y);
}

/* ================================================================ */

static int Line_2__get_base_point(const void* _this, Vector2_t position) {

    const struct Line_2* this = _this;

    /* ======== */

    position->x = this->base_point.x;
    position->y = this->base_point.y;

    /* ======== */

    return 0;
}

static int Lines_2__is_equivalent(const void* line_1, const void* line_2) {

    const struct Line_2* a = line_1;
    const struct Line_2* b = line_2;

    Vector2 temp;

    /* ======== */

    if (!Vectors2_is_parallel((Vector2_t) &a->direction, (Vector2_t) &b->direction)) {
        return 0;
    }

    Vector2_sub((Vector2_t) &a->base_point, (Vector2_t) &b->base_point, &temp);

    /* ======== */

    return Vectors2_is_parallel(&temp, (Vector2_t) &a->direction);
}

/* ================================================================ */

static int Lines_2__is_collide(const void* line_1, const void* line_2) {

    const struct Line_2* a = line_1;
    const struct Line_2* b = line_2;

    /* ======== */

    if (Vectors2_is_parallel((Vector2_t) &a->direction, (Vector2_t) &b->direction)) {
        
        return Lines_2__is_equivalent(a, b);
    }

    /* ======== */

    return 1;
}

/* ================================================================ */

static int Line_2__is_collide(const void* line, const void* another_shape) {

    const struct Line_2* this = line;
    
    /* ======== */

    return 0;
}

/* ================================================================ */

static const struct Shape_2 _Line_2 = {

    .size = sizeof(struct Line_2),
    .base_shape = LINE,

    .ctor = Line_2__ctor,
    .dtor = Line_2__dtor,

    .fill = Line_2__draw,

    .outline = NULL /* Not implemented for a line */,

    .copy = Line_2__copy,
    .rotate = Line_2__rotate,
    .collide = Lines_2__is_collide,

    .get_position = Line_2__get_base_point,
    
    .info = Line_2__info /* For debugging only */
};

const void* Line_2 = &_Line_2;

/* ================================ */