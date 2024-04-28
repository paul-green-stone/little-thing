#include "../../include/littlething.h"

    /* ================================================================ */

    void App_run(const App_t app) {

        App_t a = NULL;

        if ((app == NULL) && (g_app == NULL)) {
            return ;
        }

        a = (app == NULL) ? g_app : app;

        int colors[3] = {
            0xff0000,
            0x00ff00,
            0x0000ff,
        };

        Timer_t color_timer = NULL;
        Timer_new(&color_timer);
        Timer_set(color_timer, 0.5f);
        int i = 0;

        HEX_color_SET(colors[i], 0xff);

        while (a->is_running) {

            /* ================================================================ */
            /* ===================== Update timers here  ====================== */
            /* ================================================================ */

            Timer_tick(a->timer);
            Timer_tick(color_timer);

            App_handle_input(a);

            if (Timer_is_ready(a->timer)) {
                
                /* Clear the window */
                SDL_RenderClear(a->window->r);

                /* ================================================================ */
                /* ===================== User code goes here  ===================== */
                /* ================================================================ */

                /* ================================================================ */
                /* ================================================================ */
                /* ================================================================ */

                SDL_RenderPresent(a->window->r);

                Timer_reset(a->timer);
            }

            if (Timer_is_ready(color_timer)) {

                    i = (i == 2) ? 0 : i + 1;

                    HEX_color_SET(colors[i], 0xff);

                    Timer_reset(color_timer);
                }
        }

        return ;
    }

    /* ================================================================ */
    