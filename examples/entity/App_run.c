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

    Vector2_t v1 = NULL;
    Vector2_t v2 = NULL;

    Vector2_new(3, 1, &v1);
    Vector2_new(0, -2, &v2);

    printf("v1: [%.2f; %.2f]\n", v1->x, v1->y);
    printf("v2: [%.2f; %.2f]\n", v2->x, v2->y);

    // Vector2_div_scalar(v1, 2, v1);
    // printf("v1: [%.2f; %.2f]\n", v1->x, v1->y);

    // Vector2_sub(v1, v2, v1);
    // printf("v1: [%.2f; %.2f]\n", v1->x, v1->y);

    // Vector2_negate(v1);
    // printf("Negation of v1: [%.2f; %.2f]\n", v1->x, v1->y);

    // Vector2_div_scalar(v1, 0.5, v1);
    // printf("Scalar multiplicatin of v1: [%.2f; %.2f]\n", v1->x, v1->y);

    struct vector_2 n;
    Vector2_normalize(v1, &n);
    printf("Normalized v1: [%.2f; %.2f]\n", n.x, n.y);
    printf("Original v1: [%.2f; %.2f]\n", v1->x, v1->y);

    // Vector2_rotate(v1, -10.f);
    // printf("After rotating v1 by 10 degrees: [%.2f; %.2f]\n", v1->x, v1->y);

    printf("v1 length is: %.2f\n", Vector2_length(v1));
    printf("v2 length is: %.2f\n", Vector2_length(v2));

    float dot = 0;
    Vector2_dot(v1, v2, &dot);
    printf("The dot product of v1 and v2 is %.2f\n", dot);

    float r = 0;
    Vector2_angle_between(v1, v2, &r);

    printf("Angel between v1 and v2 is %.2f\n", r);

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

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    Vector2_destroy(&v1);
    Vector2_destroy(&v2);

    return ;
}

/* ================================================================ */
