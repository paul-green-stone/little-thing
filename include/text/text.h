#ifndef LITTLETHING_TEXT_H
#define LITTLETHING_TEXT_H

#include "../littlething.h"

/* ================================ */

/**
 * Load `file` for use as a font at `ptsize` size.
 */
#define Font_load(filepath, ptsize) (TTF_OpenFont(filepath, ptsize))

/**
 * Call this when done with a font. This will free any resources associated with the font.
 */
#define Font_unload(font) (TTF_CloseFont(font))

/* ================================ */

struct text {

    /* Text position on the screen/window */
    SDL_Rect pos;

    SDL_Texture* texture;
};

typedef struct text* Text_t;

/* ================================================================ */

extern int Text_new(const char* string, const TTF_Font* font, Text_t* text);

/* ================================ */

extern int Text_destroy(Text_t* text);

/* ================================ */

extern int Text_update(const Text_t text, const char* new_string, const TTF_Font* font);

/* ================================ */

extern int Text_display(const Text_t text, const Window_t w);

/* ================================================================ */

#endif /* LITTLETHING_TEXT_H */
