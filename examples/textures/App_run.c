#include "../../include/littlething.h"

#define SPEED 100

struct entity {

    float x;
    float y;

    int width;
    int height;

    Texture_t texture;
};

struct entity ent = {600 / 2 - 64 / 2, 400 / 2 - 64 / 2, 64, 64};
SDL_Rect r = {0, 0, 0, 0};

void move_entity(void) {

    if (key_is_pressed(SDL_SCANCODE_W)) {
        ent.y -= SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_S)) {
        ent.y += SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_D)) {
        ent.x += SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_A)) {
        ent.x -= SPEED * g_app->timer->d;
    }

    r.x = ent.x;
    r.y = ent.y;
}

/* ================================================================ */

void App_run(const App_t app) {

    App_t a = NULL;

    if ((app == NULL) && (g_app == NULL)) {
        return ;
    }

    Texture_t current = NULL;

    Texture_t textures[3];

    a = (app == NULL) ? g_app : app;

    Texture_new("images/layer_export_gfn985.png", a->window, textures + 0);
    Texture_new("images/layer_export_lzlnhq.png", a->window, textures + 1);
    Texture_new("images/layer_export_prfrra.png", a->window, textures + 2);

    SDL_Rect dest = {0, 0, 600, 400};

    r.x = ent.x;
    r.y = ent.y;
    r.w = ent.width;
    r.h = ent.height;

    Texture_new("images/asset.png", a->window, &ent.texture);

    while (a->is_running) {

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);

        /* ================================================================ */

        App_handle_input(a);

        if (key_just_pressed(SDL_SCANCODE_1)) {
            current = textures[0];
        }

        if (key_just_pressed(SDL_SCANCODE_2)) {
            current = textures[1];
        }

        if (key_just_pressed(SDL_SCANCODE_3)) {
            current = textures[2];
        }

        move_entity();

        if (Timer_is_ready(a->timer)) {
                
            /* Clear the window */
            RGBA_color_SET(255, 255, 255, 255);
            SDL_RenderClear(a->window->r);

            /* ================================================================ */
            /* ===================== User code goes here  ===================== */
            /* ================================================================ */

            Texture_display(current, NULL, &dest);

            Texture_display(ent.texture, NULL, &r);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    for (size_t i = 0; i < 3; i++) {
        Texture_destroy(textures + i);
    }

    Texture_destroy(&ent.texture);

    return ;
}

/* ================================================================ */
