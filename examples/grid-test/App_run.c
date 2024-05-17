#include "../../include/littlething.h"

/* ================================================================ */
/* =============== Include additional headers here ================ */
/* ================================================================ */

/* ================================================================ */

/* ================================================================ */

void App_run(const App_t app) {

    App_t a = NULL;

    if ((app == NULL) && (g_app == NULL)) {
        return ;
    }

    a = (app == NULL) ? g_app : app;

    SDL_Rect r = {50, 50, 100, 100};

    while (a->is_running) {

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);

        /* ================================================================ */

        App_handle_input(a);

        if (Timer_is_ready(a->timer)) {
                
            /* Clear the window */
            RGBA_color_SET(255, 255, 255, 255);
            SDL_RenderClear(a->window->r);

            /* ================================================================ */
            /* ================= User draw functions go here  ================= */
            /* ================================================================ */

            SDL_RenderSetViewport(a->window->r, &r);
            HEX_color_SET(0x000000, 0xff);
            Window_draw_grid(a->window, 10, 10, GRID_EDGE);

            SDL_RenderSetViewport(a->window->r, NULL);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    return ;
}

/* ================================================================ */
