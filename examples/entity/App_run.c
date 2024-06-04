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

    /* ================================================================ */
    /* =================== Define variables here  ===================== */
    /* ================================================================ */

    void* line_1 = Shape_new(Line_2, 300.f, 200.f, -2.0f, 5.0f);
    void* line_1_copy = Shape_copy(line_1);

    if (line_1 != NULL) {
        Shape_info(line_1);
    }

    if (line_1_copy != NULL) {
        Shape_info(line_1_copy);
    }

    printf("line_1 and line_1_copy is collide : %d\n", Shapes_is_collide(line_1, line_1_copy));

    Timer_t rotation_timer = NULL;
    Timer_new(&rotation_timer);
    Timer_set(rotation_timer, .1f);

    Timer_t rotation_timer2 = NULL;
    Timer_new(&rotation_timer2);
    Timer_set(rotation_timer2, .2f);

    while (a->is_running) {

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);
        Timer_tick(rotation_timer);
        Timer_tick(rotation_timer2);

        /* ================================================================ */

        App_handle_input(a);

        if (Timer_is_ready(a->timer)) {
                
            /* Clear the window */
            RGBA_color_SET(255, 255, 255, 255);
            SDL_RenderClear(a->window->r);

            /* ================================================================ */
            /* ================= User draw functions go here  ================= */
            /* ================================================================ */
            
            RGBA_color_SET(0, 0, 255, 255);
            Shape_draw(line_1, 100);

            RGBA_color_SET(0, 255, 0, 255);
            Shape_draw(line_1_copy, 100);

            // RGBA_color_SET(0, 0, 0, 255);
            // Shape_draw(line_1_copy, 100);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }

        if (Timer_is_ready(rotation_timer)) {

            Shape_rotate(line_1, 1);

            Timer_reset(rotation_timer);
        }

        if (Timer_is_ready(rotation_timer2)) {

            Shape_rotate(line_1_copy, -1);

            Timer_reset(rotation_timer2);
        }
    }

    Shape_destroy(line_1);
    Shape_destroy(line_1_copy);

    Timer_destroy(&rotation_timer);
    Timer_destroy(&rotation_timer2);

    return ;
}

/* ================================================================ */
