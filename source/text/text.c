#include "../../include/littlething.h"

/* ================================================================ */

int Text_new(const char* string, const TTF_Font* font, Text_t* text) {

    if (string == NULL) {
        return -1;
    }

    /* ================================ */

    if (font == NULL) {
        return -1;
    }

    /* ================================ */

    if ((*text = (Text_t) calloc(1, sizeof(struct text))) == NULL) {
        return -1;
    }

    /* ================================ */

    if (Text_update(*text, string, font) == EXIT_FAILURE) {
        Text_destroy(text);
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int Text_update(const Text_t text, const char* new_string, const TTF_Font* font) {

    SDL_Surface* s = NULL;
    SDL_Texture* t = NULL;

    if (text == NULL) {
        return -1;
    }

    /* ================================ */

    if (new_string == NULL) {
        return -1;
    }

    /* ================================ */

    if ((s = TTF_RenderText_Solid((TTF_Font*) font, new_string, *g_color)) == NULL) {

        SDL_FreeSurface(s);

        ERROR(TTF_GetError());

        return -1;
    }

    if ((t = SDL_CreateTextureFromSurface(g_app->window->r, s)) == NULL) {
        
        SDL_FreeSurface(s);

        ERROR(SDL_GetError());

        return -1;
    }

    /* ================================ */

    if (text->texture != NULL) {
        SDL_DestroyTexture(text->texture);
    }

    text->texture = t;

    /* ================================ */

    SDL_QueryTexture(text->texture, NULL, NULL, &text->pos.w, &text->pos.h);

    SDL_FreeSurface(s);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Text_destroy(Text_t* text) {

    if ((text == NULL) || (*text == NULL)) {
        return -1;
    }

    SDL_DestroyTexture((*text)->texture);
    free(*text);

    *text = NULL;

    return 0;
}

/* ================================================================ */


int Text_display(const Text_t text, const Window_t w) {

    if (text == NULL) {
        return -1;
    }

    if ((w == NULL) && (g_app->window->w == NULL)) {
        return -1;
    }

    return (SDL_RenderCopy((w == NULL) ? g_app->window->r : w->r, text->texture, NULL, &text->pos));
}

/* ================================================================ */
