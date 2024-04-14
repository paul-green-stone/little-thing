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

/* ================================================================ */
