#ifndef HELPERS_H
#define HELPERS_H

#include "../../include/littlething.h"
#include "./linked-lists/include/lists.h"

/* ================================================================ */

extern void transform(int x, int y, int w, int h, int* res_x, int* res_y);

/* ================================================================ */

extern int Rect_draw(void* data);

/* ================================================================ */

extern void* SDL_Rect_new(int x, int y, int w, int h);

/* ================================================================ */

extern int SDL_Rect_match(void* data1, void* data2);

/* ================================================================ */

extern void SDL_Rect_connect(const sList_t list);

/* ================================================================ */

#endif /* HELPERS_H */
