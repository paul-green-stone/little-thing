#ifndef LITTLETHING_WINDOW_H
#define LITTLETHING_WINDOW_H

#include "../littlething.h"

#define BUFFER 128

/* ================================ */

struct window {

    SDL_Window* w;
    SDL_Renderer* r;
};

typedef struct window* Window_t;

/* ================ */

struct window_props {

    char title[BUFFER];

    /* width */
    int w;
    /* height */
    int h;

    /* Window flags */
    Uint32 w_flags;

    /* Renderer flags */
    Uint32 r_flags;
};

/* ================================================================ */

extern int Window_new(struct window_props* props, Window_t* window);

/* ================================ */

extern int Window_destroy(Window_t* window);

/* ================================================================ */

#undef BUFFER

#endif /* LITTLETHING_WINDOW_H */
