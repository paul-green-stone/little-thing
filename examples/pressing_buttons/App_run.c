#include "../../include/littlething.h"

int global = 0;

#define SPEED 10

struct entity {

    float x;
    float y;

    int width;
    int height;
};

struct entity rect = {50, 50, 100, 100};
SDL_Rect r = {0, 0, 0, 0};

void move(void) {

    if (key_is_pressed(SDL_SCANCODE_W)) {
        rect.y -= SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_S)) {
        rect.y += SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_D)) {
        rect.x += SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_A)) {
        rect.x -= SPEED * g_app->timer->d;
    }

    r.x = rect.x;
    r.y = rect.y;
}

/* ================================================================ */

void App_run(const App_t app) {

    App_t a = NULL;

    r.x = rect.x;
    r.y = rect.y;
    r.w = rect.width;
    r.h = rect.height;

    if ((app == NULL) && (g_app == NULL)) {
        return ;
    }

    a = (app == NULL) ? g_app : app;

    RGBA_color_SET(255, 255, 255, 255);

    while (a->is_running) {

        App_handle_input(a);

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);

        /* ================================================================ */

        move();

        if (Timer_is_ready(a->timer)) {

            RGBA_color_SET(255, 255, 255, 255);
                
            /* Clear the window */
            SDL_RenderClear(a->window->r);

            /* Set a color for the rect */
            RGBA_color_SET(0, 255, 0, 255);

            SDL_RenderFillRect(a->window->r, &r);

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    return ;
}

/* ================================================================ */
