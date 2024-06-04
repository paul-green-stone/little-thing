#include "../../include/littlething.h"

/* ================================ */

typedef int (*create_shape)(va_list);

struct shape_info {
    int type;
};

/* ================================================================ */

int Entity2_new(int type, Entity2_t* entity) {

    if (entity == NULL) {
        return -1;
    }

    if ((*entity = calloc(1, sizeof(struct entity_2))) == NULL) {
        return -1;
    }

    (*entity)->type = type;

    /* ======== */

    return 0;
}

/* ================================================================ */