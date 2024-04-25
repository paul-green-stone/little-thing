#ifndef LITTLETHING_APPLICATION_H
#define LITTLETHING_APPLICATION_H

#include "../littlething.h"

/* ================================ */

struct application {

    Window_t window;
    Timer_t timer;

    int is_running;
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
