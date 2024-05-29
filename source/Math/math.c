#include "../../include/littlething.h"

/* ================================================================ */

int float_is_equal(float f1, float f2) {

    static float threshold = 1.0f / 8192.0f;

    /* ======== */

    return fabsf(f1 - f2) < threshold;
}

/* ================================================================ */
