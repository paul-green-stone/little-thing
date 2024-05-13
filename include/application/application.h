#ifndef LITTLETHING_APPLICATION_H
#define LITTLETHING_APPLICATION_H

#include "../littlething.h"

#define MAX_KEYBOARD_KEYS 256

/* ================================ */

struct application {

    Window_t window;
    Timer_t timer;

    int is_running;

    int mouse_state;

    /* Current frame */
    Uint8 c_frame[MAX_KEYBOARD_KEYS];
    /* Previous frame */
    Uint8 p_frame[MAX_KEYBOARD_KEYS];
};

typedef struct application* App_t;

/* ================================================================ */

extern int Application_new(struct window_props* props, App_t* app);

/* ================================ */

extern int Application_destroy(App_t* app);

/* ================================ */

extern void App_run(const App_t app);

/* ================================ */

extern void App_handle_input(const App_t app);

/* ================================================================ */

#endif /* LITTLETHING_APPLICATION_H */
