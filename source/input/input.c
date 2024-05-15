#include "../../include/littlething.h"

/* ================================================================ */

int key_just_pressed(int scancode) {

    return g_app->c_frame[scancode] && !g_app->p_frame[scancode];
}

/* ================================ */

int key_just_released(int scancode) {

    return !g_app->c_frame[scancode] && g_app->p_frame[scancode];
}

/* ================================ */

int key_is_pressed(int scancode) {

    return g_app->c_frame[scancode];
}

/* ================================ */

int mbtn_just_pressed(int btn) {

    /* Check if the given button has been pressed */
    if ((g_app->mouse_state >> btn) & 1) {

        /* Clear the button state that has just been pressed */
        g_app->mouse_state &= ~(1 << btn);

        return 1;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */
