#ifndef LITTLETHING_CORE_H
#define LITTLETHING_CORE_H

#include "../littlething.h"

/* ================================================================ */

extern int read_file(const char* file_name, char** buffer);

/* ================================ */

extern int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data);

/* ================================================================ */

#endif /* LITTLETHING_CORE_H */