#include "../../include/littlething.h"

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

static Uint32 SDL_Init_map_flag(const char* name) {

    static const struct {

        const char* name;
        Uint32 flag;

    } SDL_Init_Flags[] = {
        {"SDL_INIT_TIMER", SDL_INIT_TIMER},
        {"SDL_INIT_AUDIO", SDL_INIT_AUDIO},
        {"SDL_INIT_VIDEO", SDL_INIT_VIDEO},
        {"SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK},
        {"SDL_INIT_HAPTIC", SDL_INIT_HAPTIC},
        {"SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER},
        {"SDL_INIT_EVENTS", SDL_INIT_EVENTS},
        {"SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING},
        {"SDL_INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE},
    };

    static size_t size = sizeof(SDL_Init_Flags) / sizeof(SDL_Init_Flags[0]);

    /* ======== */

    size_t i = 0;

    for (; i < size; i++) {

        if (strcmp(name, SDL_Init_Flags[i].name) == 0) {
            return SDL_Init_Flags[i].flag;
        }
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

static Uint32 SDL_Init_get_flags(const cJSON* root) {

    Uint32 SDL_flags = 0;

    cJSON* array = NULL;
    size_t array_size = 0;

    size_t i = 0;

    /* ======== */

    if (extract_JSON_data(root, "SDL", cJSON_IsArray, &array) != 0) {
        return SDL_flags;
    }

    array_size = cJSON_GetArraySize(array);

    for (; i < array_size; i++) {

        cJSON* array_element = cJSON_GetArrayItem(array, i);

        SDL_flags |= SDL_Init_map_flag(array_element->valuestring);
    }

    /* ======== */

    return SDL_flags;
}

/* ================================================================ */

/* ================================================================ */
/* ============================ PUBLIC ============================ */
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

        ERROR(strerror(errno));

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

int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data) {

    if (root == NULL) {
        return 1;
    }

    if ((*data = cJSON_GetObjectItemCaseSensitive(root, name)) == NULL) {

        fprintf(stderr, "\033[0;31m%s\033[0;37m: there is no such element (\033[0;34m%s\033[0;37m) in the file", "Error", name);

        return 1;
    }

    if (check(*data) != 1) {
        return 1;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int cJSON_Parse_check(const char* buffer, cJSON** root) {

    int status = 0;
    
    if ((*root = cJSON_Parse(buffer)) == NULL) {

        const char* error_ptr = NULL;

        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            ERROR(error_ptr);
        }

        status = 1;
    }

    return status;
}

/* ================================================================ */

int LittleThing_init(void) {

    char* buffer = NULL;

    cJSON* root = NULL;

    Uint32 SDL_flags;

    int status = 0;

    /* ======== */

    if ((status = read_file("../../configs.json", &buffer)) == ENOENT) {

        /* In case of absence of a configuration file, a new one will be created with default settings */
        WARNING("missing configuration file");

        /* Just return from the function now */
        return (status = ENOENT);
    }

    if ((status = cJSON_Parse_check(buffer, &root)) != 0) {
        goto end;
    }

    SDL_flags = SDL_Init_get_flags(root);

    if ((status = SDL_Init(SDL_flags)) != 0) {

        ERROR(SDL_GetError());
    }

    /* ======== */

    end:
        free(buffer);
        cJSON_Delete(root);

        return status;
}

/* ================================================================ */
