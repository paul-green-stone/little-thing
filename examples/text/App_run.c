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

    TTF_Font* font = Font_load("fonts/PressStart2P-Regular.ttf", 28);
    Text_t text = NULL;

    int width;
    int height;

    SDL_GetWindowSize(a->window->w, &width, &height);

    HEX_color_SET(0x000000, 0xff);
    Text_new("Hello, World!", font, &text);
    text->pos.x = width / 2 - text->pos.w / 2;
    text->pos.y = height / 2 - text->pos.h / 2;

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

            HEX_color_SET(0xFF0000, 0xff);
            Text_display(text, a->window);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    Font_unload(font);

    return ;
}

/* ================================================================ */
