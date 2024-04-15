#include "../../include/littlething.h"

/* ================================================================ */

int read_file(const char* file_name, char** buffer) {
    
    FILE* file = NULL;

    size_t number_of_bytes = 0;
    size_t bytes_read = 0;

    if ((file = fopen(file_name, "r")) == NULL) {
        return errno;
    }

    /* ======== */

    fseek(file, 0L, SEEK_END);

    number_of_bytes = ftell(file) + 1;

    fseek(file, 0L, SEEK_SET);

    /* ======== */

    if ((*buffer = calloc(number_of_bytes, sizeof(char))) == NULL) {
        fclose(file);

        return errno;
    }

    bytes_read = fread(*buffer, sizeof(char), number_of_bytes, file);

    *(*buffer + bytes_read) = '\0';

    fclose(file);

    /* ======== */
    
    return 0;
}

/* ================================ */

int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data) {

    if (root == NULL) {
        return 1;
    }

    if ((*data = cJSON_GetObjectItemCaseSensitive(root, name)) == NULL) {
        return 1;
    }

    if (check(*data) != 1) {
        return 1;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */
