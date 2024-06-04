#include "../../../include/littlething.h"

/* ================================================================ */

int Rect2_new(float x, float y, int width, int height, Rect2_t* rect) {

    if (*rect == NULL) {
        return -1;
    }

    if ((*rect = calloc(1, sizeof(Rect2))) == NULL) {
        return -1;
    }

    (*rect)->position.x = x;
    (*rect)->position.y = y;

    (*rect)->width = width;
    (*rect)->height = height;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Rect2_destroy(Rect2_t* rect) {

    if ((rect == NULL) || (*rect == NULL)) {
        return -1;
    }

    free(*rect);

    *rect = NULL;
    
    /* ======== */

    return 0;
}

/* ================================================================ */

int Rect2_draw(const Rect2_t rect) {

    SDL_Rect r;

    if (rect == NULL) {
        return -1;
    }

    r.x = rect->position.x;
    r.y = rect->position.y;
    r.w = rect->width;
    r.h = rect->height;

    /* ======== */

    return SDL_RenderFillRect(g_app->window->r, &r);
}

/* ================================================================ */

int Rect2_outline(const Rect2_t rect) {

    SDL_Rect r;

    if (rect == NULL) {
        return -1;
    }

    r.x = rect->position.x;
    r.y = rect->position.y;
    r.w = rect->width;
    r.h = rect->height;

    /* ======== */

    return SDL_RenderDrawRect(g_app->window->r, &r);
}

/* ================================================================ */

int Rects2_is_collide(const Rect2_t r1, const Rect2_t r2) {

    if ((r1 == NULL) || (r2 == NULL)) {
        return -1;
    }

    float r1_left = r1->position.x;
    float r1_right = r1_left + r1->width;
    float r1_bottom = r1->position.y;
    float r1_top = r1_bottom + r1->height;

    float r2_left = r2->position.x;
    float r2_right = r2_left + r2->width;
    float r2_bottom = r2->position.y;
    float r2_top = r2_bottom + r2->height;

    /* ======== */

    return is_overlap(r1_left, r1_right, r2_left, r2_right) && is_overlap(r1_bottom, r1_top, r2_bottom, r2_top);
}

/* ================================================================ */
