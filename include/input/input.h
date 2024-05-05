#ifndef LITTLETHING_INPUT_H
#define LITTLETHING_INPUT_H

#include "../littlething.h"

/* ================================================================ */

/**
 * \brief Check if a specific key was pressed only once since the last check.
 *
 * \param[in] scancode key to check, refer to SDL_Scancode enumeration
 *
 * \return 1 if the key was pressed only once since the last check, 0 otherwise
 */
extern int key_just_pressed(int scancode);

/* ================================ */

/**
 * \brief Check if a specific key was released the last check.
 *
 * \param[in] scancode key to check, refer to SDL_Scancode enumeration
 *
 * \return 1 if the key was released since the last check, 0 otherwise
 */
extern int key_just_released(int scancode);

/* ================================ */

/**
 * \brief Check if a specific key is pressed.
 *
 * \param[in] scancode key to check, refer to SDL_Scancode enumeration
 *
 * \return 1 if the key was pressed, 0 otherwise
 */
extern int key_is_pressed(int scancode);

/* ================================================================ */

#endif /* LITTLETHING_INPUT_H */
