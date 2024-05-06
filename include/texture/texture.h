#ifndef LITTLETHING_TEXTURE_H
#define LITTLETHING_TEXTURE_H

#include "../littlething.h"

/* ================================ */

struct texture {

    SDL_Texture* t;

    SDL_Renderer* r;
};

typedef struct texture* Texture_t;

/* ================================================================ */

extern int Texture_new(const char* pathname, const Window_t window, Texture_t* texture);

/* ================================ */

extern int Texture_destroy(Texture_t* texture);

/* ================================ */

extern int Texture_display(const Texture_t t, SDL_Rect* src, SDL_Rect* dest);

/* ================================================================ */

#endif /* LITTLETHING_TEXTURE_H */
