#ifndef LITTLETHING_CORE_H
#define LITTLETHING_CORE_H

#include "../littlething.h"

#define WARNING(msg) fprintf(stderr, "\033[0;33m%s\033[0;37m: %s\n", "Warning", msg)

#define ERROR(msg) fprintf(stderr, "\033[0;31m%s\033[0;37m: %s\n", "Error", msg)

/* ================================================================ */

extern int read_file(const char* file_name, char** buffer);

/* ================================ */

extern int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data);

/* ================================ */

extern int cJSON_Parse_check(const char* buffer, cJSON** root);

/* ================================ */

extern int LittleThing_init(void);

/* ================================ */

extern int LittleThing_quit(void);

/* ================================ */

extern int write_to_file(const cJSON* root, const char* name);

/* ================================================================ */

#endif /* LITTLETHING_CORE_H */
