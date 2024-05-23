#ifndef LITTLETHING_CAMERA_H
#define LITTLETHING_CAMERA_H

#include "../littlething.h"

/* ================================ */

struct camera {
    
    SDL_Rect* dimensions;

    SDL_Rect* target;
};

typedef struct camera* Camera_t;

/* ================================================================ */

extern int Camera_new(int x, int y, int width, int height, Camera_t* c);

/* ================================================================ */

extern int Camera_destroy(Camera_t* camera);

/* ================================================================ */

extern int Camera_bind(const Camera_t camera, const SDL_Rect* rect);

/* ================================================================ */

extern int Camera_center(const Camera_t camera);

/* ================================================================ */

extern SDL_Rect Camera_update(const Camera_t camera, const SDL_Rect* rect);

/* ================================================================ */

#endif /* LITTLETHING_CAMERA_H */
