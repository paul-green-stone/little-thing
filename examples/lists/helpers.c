#include "helpers.h"

/* ================================================================ */

void transform(int x, int y, int w, int h, int* res_x, int* res_y) {

    *res_x = x / w;
    *res_y = y / h;
}

/* ================================================================ */

int Rect_draw(void* data) {

    SDL_Rect rect = *((SDL_Rect*) data);

    SDL_RenderFillRect(g_app->window->r, &rect);

    return 1;
}

/* ================================================================ */

void* SDL_Rect_new(int x, int y, int w, int h) {

    SDL_Rect* rect = NULL;

    if ((rect = calloc(1, sizeof(SDL_Rect))) == NULL) {
        return NULL;
    }

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    /* ======== */

    return rect;
}

/* ================================================================ */

int SDL_Rect_match(void* data1, void* data2) {

    SDL_Rect* r1 = ((SDL_Rect*) data1);
    SDL_Rect* r2 = ((SDL_Rect*) data2);

    return !((r1->x == r2->x) && (r1->y == r2->y));
}

/* ================================================================ */

void SDL_Rect_connect(const sList_t list) {

    size_t size = sList_size(list);

    void* previous = NULL;
    void* current = NULL;

    SDL_Rect* r1 = NULL;
    SDL_Rect* r2 = NULL;

    if (size > 1) {

        previous = sList_next(list);

        for (current = sList_next(list); current != NULL; current = sList_next(list)) {

            r1 = (SDL_Rect*) previous;
            r2 = (SDL_Rect*) current;

            SDL_RenderDrawLine(g_app->window->r, r1->x + r1->w / 2, r1->y + r1->h / 2, r2->x + r2->w / 2, r2->y + r2->h / 2);

            previous = current;
        }
    }

    return ;
}

/* ================================================================ */