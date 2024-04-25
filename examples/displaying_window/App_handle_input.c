#include "../../include/littlething.h"

/* ================================================================ */

void App_handle_input(const App_t app) {
    
    while (SDL_PollEvent(&g_event)) {

        switch (g_event.type) {

            case SDL_QUIT:

                app->is_running = !app->is_running;

                break ;

            default:
                break ;
        }
    }

    return ;
}
