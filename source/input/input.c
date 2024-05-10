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

/* ================================================================ */
