#include "../../include/littlething.h"

/* ================================================================ */

int Window_new(struct window_props* props, Window_t* window) {

    Window_t w = NULL;

    struct window_props def = {

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

    if ((w->w = SDL_CreateWindow(props ? props->title : def.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, props ? props->w : def.w, props ? props->h : def.h, props ? props->w_flags : def.w_flags)) == NULL) {

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

int Window_draw_grid(Window_t window, int width, int height, int edge) {

    int window_width;
    int window_height;

    size_t rows;
    size_t columns;

    size_t i = 0;

    if (window == NULL) {
        return -1;
    }

    SDL_GetWindowSize(window->w, &window_width, &window_height);

    rows = window_height / height;
    columns = window_width / width;

    if (edge == GRID_EDGE) {
        rows += 1;
        columns += 1;
    }

    /* ======================= Drawing columns ======================== */
    for (i = (edge == GRID_EDGE) ? 0 : 1; i < columns; i++) {
        SDL_RenderDrawLine(window->r, i * width, 0, i * width, window_height);
    }

    /* ========================= Drawing rows ========================= */
    for (i = (edge == GRID_EDGE) ? 0 : 1; i < rows; i++) {
        SDL_RenderDrawLine(window->r, 0, i * height, window_width, i * height);
    }

    return 0;
}

/* ================================================================ */
