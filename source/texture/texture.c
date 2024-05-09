#include "../../include/littlething.h"

#define BUFFER 128

/* ================================================================ */

int Texture_new(const char* pathname, const Window_t window, Texture_t* t) {

    SDL_Surface* surface = NULL;

    char buffer[BUFFER];

    if (window == NULL) {

        sprintf(buffer, "\033[0;34m%s\033[0;37m - missing window. Make sure it is not NULL", __func__);
        
        ERROR(buffer);

        return -1;
    }

    /* ======== */

    if ((*t = calloc(1, sizeof(struct texture))) == NULL) {
        
        return -1;
    }

    /* ======== */

    if ((surface = IMG_Load(pathname)) == NULL) {
        Texture_destroy(t);

        return -1;
    }

    /* ======== */

    if (((*t)->t = SDL_CreateTextureFromSurface(window->r, surface)) == NULL) {

        SDL_FreeSurface(surface);

        Texture_destroy(t);

        return -1;
    }

    (*t)->r = window->r;

    SDL_FreeSurface(surface);

    /* ======== */

    return 0;
}

/* ================================ */

int Texture_destroy(Texture_t* t) {

    if ((t == NULL) && (*t == NULL)) {

        return -1;
    }

    SDL_DestroyTexture((*t)->t);

    free(*t);

    *t = NULL;

    /* ======== */

    return 0;
}

/* ================================ */

int Texture_display(const Texture_t t, SDL_Rect* src, SDL_Rect* dest) {

    if (t == NULL) {
        return -1;
    }

    return SDL_RenderCopy(t->r, t->t, src, dest);
}

/* ================================================================ */
