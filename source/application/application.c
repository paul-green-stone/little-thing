#include "../../include/littlething.h"

/* ================================================================ */

int Application_new(struct window_props* props, App_t* app) {

    App_t a = NULL;

    if ((a = calloc(1, sizeof(struct application))) == NULL) {
        return 1;
    }

    if (Window_new(props, &a->window) != 0) {
        free(*app);

        return 1;
    }

    a->is_running = 1;

    *app = a;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Application_destroy(App_t* app) {

    if ((app == NULL) || (*app == NULL)) {
        return 1;
    }

    Window_destroy(&(*app)->window);

    free(*app);

    *app = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */
