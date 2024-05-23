#include "../../include/littlething.h"

/* ================================================================ */

int Camera_new(int x, int y, int width, int height, Camera_t* c) {

    Camera_t camera = NULL;

    if ((camera = calloc(1, sizeof(struct camera))) == NULL) {
        return -1;
    }

    if ((camera->dimensions = calloc(1, sizeof(SDL_Rect))) == NULL) {
        Camera_destroy(&camera);
    }

    camera->dimensions->x = x;
    camera->dimensions->y = y;
    camera->dimensions->w = width;
    camera->dimensions->h = height;

    *c = camera;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Camera_destroy(Camera_t* camera) {
    
    if ((camera == NULL) || (*camera == NULL)) {
        return -1;
    }

    free((*camera)->dimensions);

    free(*camera);

    *camera = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Camera_bind(const Camera_t camera, const SDL_Rect* rect) {

    if ((camera == NULL) || (rect == NULL)) {
        return -1;
    }

    camera->target = (SDL_Rect*) rect;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Camera_center(const Camera_t camera) {
    
    if ((camera == NULL) || (camera->target == NULL)) {
        return -1;
    }
    
    camera->dimensions->x = (camera->target->x + camera->target->w) - (camera->dimensions->w / 2);
    camera->dimensions->y = (camera->target->y + camera->target->h) - (camera->dimensions->h / 2);

    /* ======== */

    return 0;
}

/* ================================================================ */

SDL_Rect Camera_update(const Camera_t camera, const SDL_Rect* rect) {

    SDL_Rect offset;
    
    if (camera == NULL) {
        return *rect;
    }

    if (rect == NULL) {
        return (SDL_Rect) {0, 0, 0, 0};
    }

    /* ================ */

    offset.x = rect->x - camera->dimensions->x;
    offset.y = rect->y - camera->dimensions->y;

    offset.w = rect->w;
    offset.h = rect->h;

    //SDL_RenderFillRect(g_app->window->r, &offset);

    /* ======== */

    return offset;
}

/* ================================================================ */
