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

    Point2 base_1 = {100, 100};
    Point2 base_2 = {100, 110};

    Line2_t l1 = NULL;
    Line2_new(base_1.x, base_1.y, 100, 100, &l1);

    Line2_t l2 = NULL;
    Line2_new(base_2.x, base_2.y, 100, 100, &l2);

    printf("l1 and l2 collide (?) : %d\n", Lines2_is_collide(l1, l2));
    printf("l1 and l2 are equivalent (?) : %d\n", Lines2_is_equivalent(l1, l2));

    float angle;
    Vector2_angle_between(&l1->direction, &l2->direction, &angle);

    printf("Angle between l1 and l2: %.2f\n", angle);

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

            RGBA_color_SET(255, 0, 0, 255);
            Line2_draw(l1, 10);

            RGBA_color_SET(0, 255, 0, 255);
            Line2_draw(l2, 10);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    Line2_destroy(&l1);
    Line2_destroy(&l2);

    return ;
}

/* ================================================================ */
