#include "../../include/littlething.h"

/* ================================================================ */
/* =============== Include additional headers here ================ */
/* ================================================================ */

/* ================================================================ */

int m_x;
int m_y;

/* ================================================================ */

void App_handle_input(const App_t app) {
        
    while (SDL_PollEvent(g_event)) {

        switch (g_event->type) {

            case SDL_QUIT:

                app->is_running = !app->is_running;

                break ;

            /* ================================ */

            default:
                break ;
        }
    }

    memcpy(app->p_frame, (Uint8*) app->c_frame, MAX_KEYBOARD_KEYS);
    memcpy(app->c_frame, (Uint8*) SDL_GetKeyboardState(NULL), MAX_KEYBOARD_KEYS);
    
    SDL_GetMouseState(&m_x, &m_y);
}

/* ================================================================ */

