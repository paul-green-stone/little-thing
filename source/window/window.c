#include "../../include/littlething.h"

/* ================================================================ */

int Window_new(struct window_props* props, Window_t* window) {

    Window_t w = NULL;

    struct window_props def = {
        .x = SDL_WINDOWPOS_CENTERED,
        .y = SDL_WINDOWPOS_CENTERED,

        .w = 600,
        .h = 400,

        .w_flags = 0,

        .r_flags = SDL_RENDERER_ACCELERATED,
    };

    strncpy(def.title, "Application", strlen("Application") + 1);

    if ((w = calloc(1, sizeof(struct window))) == NULL) {

        ERROR(strerror(errno));

        return 1;
    }

    if ((w->w = SDL_CreateWindow(props ? props->title : def.title, props ? props->x : def.x, props ? props->y : def.y, props ? props->w : def.w, props ? props->h : def.h, props ? props->w_flags : def.w_flags)) == NULL) {

        ERROR(SDL_GetError());

        return 1;
    }

    if ((w->r = SDL_CreateRenderer(w->w, -1, props ? props->r_flags : def.r_flags)) == NULL) {

        Window_destroy(&w);

        ERROR(SDL_GetError());

        return 1;
    }

    *window = w;

    return 0;
}

/* ================================================================ */

int Window_destroy(Window_t* window) {

    if ((window == NULL) || (*window == NULL)) {
        return 1;
    }

    SDL_DestroyRenderer((*window)->r);

    SDL_DestroyWindow((*window)->w);

free(*window);

    *window = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */
