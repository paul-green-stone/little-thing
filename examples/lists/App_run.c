#include "../../include/littlething.h"
#include "./linked-lists/include/lists.h"

#include "helpers.h"

/* ================================================================ */

void App_run(const App_t app) {

    int res_x;
    int res_y;

    App_t a = NULL;

    if ((app == NULL) && (g_app == NULL)) {
        return ;
    }

    sList_t list = NULL;
    /* ========== Creating a new linked list data structure =========== */
    sList_new(&list, free, NULL, SDL_Rect_match);

    /* ===================== Cell width & height ====================== */
    int cell_w = 20;
    int cell_h = 20;

    a = (app == NULL) ? g_app : app;

    SDL_SetRenderDrawBlendMode(a->window->r, SDL_BLENDMODE_BLEND);

    while (a->is_running) {

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);

        /* ================================================================ */

        App_handle_input(a);
        
        if (((g_app->mouse_state >> SDL_BUTTON_LEFT) & 1)) {

            transform(m_x, m_y, 20, 20, &res_x, &res_y);

            sNode_t node;
            SDL_Rect rect = {res_x * cell_w, res_y * cell_h, cell_w, cell_h};
            void* data;

            if (sList_find(list, &rect, &node) != 0) {
                sList_insert_last(list, SDL_Rect_new(res_x * cell_w, res_y * cell_h, cell_w, cell_h));
            }
            else {
                sList_delete_Node(list, node, &data);
            }
            
            g_app->mouse_state &= ~(1 << SDL_BUTTON_LEFT);
        }

        if (Timer_is_ready(a->timer)) {
                
            /* Clear the window */
            RGBA_color_SET(0, 0, 0, 255);
            SDL_RenderClear(a->window->r);

            /* ================================================================ */
            /* ===================== User code goes here  ===================== */
            /* ================================================================ */

            RGBA_color_SET(255, 0, 0, 255);
            sList_foreach(list, Rect_draw);

            /* Drawing a grid */
            RGBA_color_SET(0, 255, 0, 100);
            Window_draw_grid(a->window, cell_w, cell_h);

            RGBA_color_SET(0, 0, 255, 255);
            SDL_Rect_connect(list, cell_w, cell_h);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    /* ===================== Destroying the list ====================== */
    sList_destroy(&list);

    /* ======== */

    return ;
}

/* ================================================================ */
