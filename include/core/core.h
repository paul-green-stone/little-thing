#ifndef LITTLETHING_CORE_H
#define LITTLETHING_CORE_H

#include "../littlething.h"

#define WARNING(msg) fprintf(stderr, "\033[0;33m%s\033[0;37m: %s\n", "Warning", msg)

#define ERROR(msg) fprintf(stderr, "\033[0;31m%s\033[0;37m: %s\n", "Error", msg)

/* ================================================================ */

/**
 * Set color in RGBA format.
 * 
 * \param[in] red amount of red
 * \param[in] green amount of green
 * \param[in] blue amount of blue
 * \param[in] alpha amount of alpha channel
 */
#define RGBA_color_SET(red, green, blue, alpha) \
    g_color->r = red; g_color->g = green; g_color->b = blue; g_color->a = alpha; \
    SDL_SetRenderDrawColor(g_app->window->r, red, green, blue, alpha)

/* ================================================================ */

/**
 * Set color in RGBA format.
 * 
 * \param[in] color color in hexadecimal format
 * \param[in] alpha amount of alpha channel
 */
#define HEX_color_SET(color, alpha) \
    *g_color = (SDL_Color) {(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, alpha}; \
    SDL_SetRenderDrawColor(g_app->window->r, g_color->r, g_color->g, g_color->b, g_color->a)

/* ================================================================ */

/**
 * The function allocates memory for a buffer and reads a file content into it.
 * It's the user who is responsible for freeing the buffer after the work is done.
 * 
 * \param[in] file_name file to read
 * \param[out] buffer buffer that stores the file content
 * 
 * \return The function returns 0 on success, nonzero value on failure
 */
extern int read_file(const char* file_name, char** buffer);

/* ================================ */

/**
 * The function extracts a piece of information `name` from a cJSON object named `root` and stores it in `data`.
 * The `check` method is responsible for verifying whether the extracted `name` belongs to the specified type.
 * 
 * \param[in] root object to extract information from
 * \param[in] name a piece of information to extract
 * \param[in] check a pointer to the function that verifies whether `name` is of specified type
 * \param[out] data placeholder for extracted data
 * 
 * \return The function returns 0 on success, nonzero value on failure
*/
extern int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data);

/* ================================ */

/**
 * The function parses the string located in the `buffer`
 * and stores the result in `root`.
 * The function is simply a wrapper around `cJSON_Parse` function
 * with error displaying mechanism implemented.
 * 
 * \param[in] buffer string to parse
 * \param[out] root placeholder for parsed string
 * 
 * \return The function returns 0 on success, nonzero value on failure
*/
extern int cJSON_Parse_check(const char* buffer, cJSON** root);

/* ================================ */

extern int LittleThing_init(void);

/* ================================ */

extern int LittleThing_quit(void);

/* ================================ */

extern int write_to_file(const char* str, const char* name);

/* ================================ */

extern int draw_grid(const Window_t w, int c_w, int c_h, SDL_Rect* dimensions);

/* ================================================================ */

#endif /* LITTLETHING_CORE_H */
