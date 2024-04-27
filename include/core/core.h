#ifndef LITTLETHING_CORE_H
#define LITTLETHING_CORE_H

#include "../littlething.h"

#define WARNING(msg) fprintf(stderr, "\033[0;33m%s\033[0;37m: %s\n", "Warning", msg)

#define ERROR(msg) fprintf(stderr, "\033[0;31m%s\033[0;37m: %s\n", "Error", msg)

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

/* ================================================================ */

#endif /* LITTLETHING_CORE_H */
