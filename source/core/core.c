#include "../../include/littlething.h"

/* ================================================================ */

#define TITLE "Little Thing"

SDL_Event event;
SDL_Event* g_event = &event;

SDL_Color color;
SDL_Color* g_color = &color;

App_t g_app = NULL;

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

/* The lookup table entity for `SDL` flags */
struct mapping {

    const char* name;
    Uint32 flag;
};

/* ================================ */

/* The lookup table for `SDL_CreateWindow` flags */
struct mapping SDL_CreateWindow_Flags[] = {
    {"SDL_WINDOW_FULLSCREEN", SDL_WINDOW_FULLSCREEN},
    {"SDL_WINDOW_OPENGL", SDL_WINDOW_OPENGL},
    {"SDL_WINDOW_SHOWN", SDL_WINDOW_SHOWN},
    {"SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN},
    {"SDL_WINDOW_BORDERLESS", SDL_WINDOW_BORDERLESS},
    {"SDL_WINDOW_RESIZABLE", SDL_WINDOW_RESIZABLE},
    {"SDL_WINDOW_MINIMIZED", SDL_WINDOW_MAXIMIZED},
    {"SDL_WINDOW_MOUSE_GRABBED", SDL_WINDOW_MOUSE_GRABBED},
    {"SDL_WINDOW_INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS},
    {"SDL_WINDOW_MOUSE_FOCUS", SDL_WINDOW_MOUSE_FOCUS},
    {"SDL_WINDOW_FULLSCREEN_DESKTOP", ( SDL_WINDOW_FULLSCREEN | 0x00001000 )},
    {"SDL_WINDOW_FOREIGN", SDL_WINDOW_FOREIGN},
    {"SDL_WINDOW_ALLOW_HIGHDPI", SDL_WINDOW_ALLOW_HIGHDPI},
    {"SDL_WINDOW_MOUSE_CAPTURE", SDL_WINDOW_MOUSE_CAPTURE},
    {"SDL_WINDOW_ALWAYS_ON_TOP", SDL_WINDOW_ALWAYS_ON_TOP},
    {"SDL_WINDOW_SKIP_TASKBAR", SDL_WINDOW_SKIP_TASKBAR},
    {"SDL_WINDOW_UTILITY", SDL_WINDOW_UTILITY},
    {"SDL_WINDOW_TOOLTIP", SDL_WINDOW_TOOLTIP},
    {"SDL_WINDOW_POPUP_MENU", SDL_WINDOW_POPUP_MENU},
    {"SDL_WINDOW_KEYBOARD_GRABBED", SDL_WINDOW_KEYBOARD_GRABBED},
    {"SDL_WINDOW_VULKAN", SDL_WINDOW_VULKAN},
    {"SDL_WINDOW_METAL", SDL_WINDOW_METAL},
    {"SDL_WINDOW_INPUT_GRABBED", SDL_WINDOW_MOUSE_GRABBED}
};

/* ================================ */

/* The lookup table for `SDL_CreateRenderer` flags */
struct mapping SDL_CreateRenderer_Flags[] = {
    {"SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE},
    {"SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED},
    {"SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC},
    {"SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE}
};

/* ================================ */

/* The lookup table for `SDL_Init` flags */
struct mapping SDL_Init_Flags[] = {
    {"SDL_INIT_TIMER", SDL_INIT_TIMER},
    {"SDL_INIT_AUDIO", SDL_INIT_AUDIO},
    {"SDL_INIT_VIDEO", SDL_INIT_VIDEO},
    {"SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK},
    {"SDL_INIT_HAPTIC", SDL_INIT_HAPTIC},
    {"SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER},
    {"SDL_INIT_EVENTS", SDL_INIT_EVENTS},
    {"SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING},
    {"SDL_INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE}
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/**
 * The function maps a string to its corresponding SDL flag.
 * To achieve this, it requires information about the table to search in,
 * its size, and the string to be converted into a flag.
 * If the flag is unrecognized, the function will return 0.
 * 
 * \param[in] lookup_table an array holding mappings of strings to flags
 * \param[in] string_flag a string equivalent of the flag to be searched in the `lookup_table`
 * \param[in] table_size number of elements, flags, in the `lookup_table`
 * 
 * \return The function returns a valid SDL flag upon success, and 0 to indicate an error if an unrecognized flag is encountered..
 */
static Uint32 SDL_lookup_flag(const struct mapping* lookup_table, const char* string_flag, size_t table_size) {

    size_t i = 0;

    for (; i < table_size; i++) {

        if (strcmp(string_flag, (lookup_table + i)->name) == 0) {
            return (lookup_table + i)->flag;
        }
    }

    /* ======== */

    WARNING("unrecognized flag");

    return 0;
}

/* ================================================================ */

/**
 * The function retrieves the flags required for the `SDL_Init` function to initialize the necessary subsystems.
 * These flags are extracted from a `cJSON` object,
 * which is obtained by reading a `.json` file into a buffer and parsing the buffer.
 * Subsequently, the function returns the bitwise OR (|) of the flags after mapping
 * their string equivalents to the corresponding SDL macros.
 * 
 * \param[in] root a string parsed by the `cJSON_Parse` function
 * 
 * \return The function returns the bitwise OR (|) of the flags after mapping their string equivalents to the corresponding SDL macros, or 0 if an error occurs. This result is used for initializing the default SDL subsystems.
 */
static Uint32 SDL_Init_get_flags(const cJSON* root) {

    /* Flags to be returned */
    Uint32 SDL_flags = 0;

    /* In the `.json` file, the `SDL_Init` flags are stored in an array named `SDLf` */
    cJSON* array = NULL;
    /* Number of flags in the array */
    size_t array_size = 0;

    size_t i = 0;

    /* ======== */

    /* Obtaining the `SDLf` array from the `root` object */
    if (extract_JSON_data(root, "SDLf", cJSON_IsArray, &array) != 0) {
        return SDL_flags;
    }

    array_size = cJSON_GetArraySize(array);

    for (; i < array_size; i++) {

        /* Retrieve the next element from the given array */
        cJSON* array_element = cJSON_GetArrayItem(array, i);

        /* Map a string to its equivalent flag */
        SDL_flags |= SDL_lookup_flag(SDL_Init_Flags, array_element->valuestring, sizeof(SDL_Init_Flags) / sizeof(SDL_Init_Flags[0]));
    }

    /* ======== */

    return SDL_flags;
}

/* ================================================================ */

/**
 * Creates a default `.json` file containing SDL flags to be used in initialization.
 * 
 * \param[in] pathname name of the file
 * 
 * \return The function returns 0 on success, nonzero value on failure.
*/
static int create_default_SDL(const char* pathname) {

    /* That's how the result file will look like */
    /*
        {
            "SDLf: ["SDL_INIT_VIDEO", "SDL_INIT_AUDIO", "SDL_INIT_EVENTS", "SDL_INIT_TIMER]"
        }
    */

    int status = 0;

    cJSON* root = NULL;
    cJSON* SDL_flags = NULL;
    cJSON* flag = NULL;

    size_t i = 0;

    /* The list of default subsystems to be added to the file */
    char* flags[] = {"SDL_INIT_VIDEO", "SDL_INIT_AUDIO", "SDL_INIT_EVENTS", "SDL_INIT_TIMER"};
    size_t size = sizeof(flags) / sizeof(flags[0]);

    /* = Creating a root object as a container for dependent elements = */
    if ((root = cJSON_CreateObject()) == NULL) {
        goto end;
    }

    /* ================================================================ */
    /* ============================= SDL ============================== */
    /* ================================================================ */

    if ((SDL_flags = cJSON_CreateArray()) == NULL) {
        goto end;
    }

    cJSON_AddItemToObject(root, "SDLf", SDL_flags);

    for (; i < size; i++) {

        if ((flag = cJSON_CreateString(flags[i])) == NULL) {
            goto end;
        }

        cJSON_AddItemToArray(SDL_flags, flag);
    }

    /* ================================================================ */
    /* ====================== Writing to a file ======================= */
    /* ================================================================ */

    if (write_to_file(cJSON_Print(root), pathname) != 0) {

        status = errno;

        char msg[128];

        sprintf(msg, "a file (\033[0;34m%s\033[0;37m) cannot be created", pathname);

        ERROR(msg);

        goto end;
    }

    /* ======== */

    end:
        cJSON_Delete(root);

        return status;
}

/* ================================================================ */

/**
 * Creates a default `.json` file containing essential information about the application,
 * including necessary settings and configurations.
 * 
 * \param[in] pathname name of the file
 * 
 * \return The function returns 0 on success, nonzero value on failure.
*/
static int create_default_Application(const char* pathname) {

    /* That's how the result file will look like */
    /*
        {
	        "width":	600,
	        "height":	400,
	        "window":	["SDL_WINDOW_SHOWN"],
	        "renderer":	["SDL_RENDERER_ACCELERATED"],
            "title": "Little Thing"
        }
    */

    int status = 0;

    cJSON* root = NULL;
    cJSON* flags = NULL;
    cJSON* flag = NULL;

    size_t i = 0;

    /* Default SDL_WindowCreate flags */
    char* window_flags[] = {"SDL_WINDOW_SHOWN"};
    size_t wsize = sizeof(window_flags) / sizeof(window_flags[0]);

    /* Default SDL_CreateRenderer flags */
    char* renderer_flags[] = {"SDL_RENDERER_ACCELERATED"};
    size_t rsize = sizeof(renderer_flags) / sizeof(renderer_flags[0]);

    /* Default window width */
    int width = 600;
    /* Default window height */
    int height = 400;

    cJSON* data = NULL;

    /* ================================================================ */

    if ((root = cJSON_CreateObject()) == NULL) {

        status = -1;

        goto end;
    }

    /* ================================================================ */
    /* ======================= Creating `title` ======================= */
    /* ================================================================ */

    if ((data = cJSON_CreateString(TITLE)) == NULL) {
        
        status = -1;

        goto end;
    }

    cJSON_AddItemToObject(root, "title", data);

    /* ================================================================ */
    /* ======================= Creating `width` ======================= */
    /* ================================================================ */

    if ((data = cJSON_CreateNumber(width)) == NULL) {
        
        status = -1;

        goto end;
    }

    cJSON_AddItemToObject(root, "width", data);

    /* ================================================================ */
    /* ====================== Creating `height` ======================= */
    /* ================================================================ */

    if ((data = cJSON_CreateNumber(height)) == NULL) {
        
        status = -1;

        goto end;
    }

    cJSON_AddItemToObject(root, "height", data);

    /* ================================================================ */
    /* =================== Creating `window` array ==================== */
    /* ================================================================ */

    if ((flags = cJSON_CreateArray()) == NULL) {

        status = -1;

        goto end;
    }

    for (i = 0; i < wsize; i++) {

        if ((flag = cJSON_CreateString(window_flags[i])) == NULL) {
            goto end;
        }

        cJSON_AddItemToArray(flags, flag);
    }

    cJSON_AddItemToObject(root, "window", flags);

    /* ================================================================ */
    /* ================== Creating `renderer` array =================== */
    /* ================================================================ */

    if ((flags = cJSON_CreateArray()) == NULL) {

        status = -1;

        goto end;
    }

    for (i = 0; i < rsize; i++) {

        if ((flag = cJSON_CreateString(renderer_flags[i])) == NULL) {
            goto end;
        }

        cJSON_AddItemToArray(flags, flag);
    }

    cJSON_AddItemToObject(root, "renderer", flags);

    /* ================================================================ */
    /* ====================== Writing to a file ======================= */
    /* ================================================================ */



    if (write_to_file(cJSON_Print(root), pathname) != 0) {

        status = errno;

        char msg[128];

        sprintf(msg, "a file (\033[0;34m%s\033[0;37m) cannot be created", pathname);

        ERROR(msg);

        goto end;
    }

    end:
        cJSON_Delete(root);

        return status;
}

/* ================================================================ */

/**
 * The function retrieves information necessary for creating the application,
 * including window flags (used in `SDL_CreateWindow`), renderer flags (used in `SDL_CreateRenderer`),
 * window width, and window height, among other things.
 * 
 * \param[out] props a pointer to the 'window_props' structure to store properties in
 * 
 * \return The function returns 0 on success, nonzero value on failure.
 */
static int get_props(struct window_props* props, const cJSON* root) {

    cJSON* data = NULL;

    size_t size = 0;
    size_t i = 0;

    if (root == NULL) {
        return -1;
    }

    if (props == NULL) {
        return -1;
    }

    /* ====================== Retrieving `title` ====================== */
    extract_JSON_data(root, "title", cJSON_IsNumber, &data);
    /* If the element is missing, default values are used. HARDCODED FOR NOW */
    strncpy(props->title, data->valuestring, TITLE_SIZE - 1);

    /* ====================== Retrieving `width` ====================== */
    extract_JSON_data(root, "width", cJSON_IsNumber, &data);
    /* If the element is missing, default values are used. HARDCODED FOR NOW */
    props->w = (data) ? data->valueint : 600;

    /* ===================== Retrieving `height` ====================== */
    extract_JSON_data(root, "height", cJSON_IsNumber, &data);
    props->h = (data) ? data->valueint : 400;

    /* ====================== Retrieving `window` ===================== */
    extract_JSON_data(root, "window", cJSON_IsArray, &data);
    size = cJSON_GetArraySize(data);

    /* ======================== and its flags ========================= */
    for (i = 0; i < size; i++) {

        cJSON* array_element = cJSON_GetArrayItem(data, i);

        props->w_flags |= SDL_lookup_flag(SDL_CreateWindow_Flags, array_element->valuestring, sizeof(SDL_CreateWindow_Flags) / sizeof(SDL_CreateWindow_Flags[0]));
    }

    /* ==================== Retrieving `renderer` ===================== */
    extract_JSON_data(root, "renderer", cJSON_IsArray, &data);
    size = cJSON_GetArraySize(data);

    /* ======================== and its flags ========================= */
    for (i = 0; i < size; i++) {

        cJSON* array_element = cJSON_GetArrayItem(data, i);

        props->r_flags |= SDL_lookup_flag(SDL_CreateRenderer_Flags, array_element->valuestring, sizeof(SDL_CreateRenderer_Flags) / sizeof(SDL_CreateRenderer_Flags[0]));
    }

    /* ======== */

    return 0;
}   

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

    /* ====== Figuring out how many bytes of memory to allocate ======= */
    fseek(file, 0L, SEEK_END);

    number_of_bytes = ftell(file) + 1;

    fseek(file, 0L, SEEK_SET);

    /* ====================== Actual allocation ======================= */
    if ((*buffer = calloc(number_of_bytes, sizeof(char))) == NULL) {

        ERROR(strerror(errno));

        fclose(file);

        return errno;
    }

    /* =================== Reading into the buffer ==================== */
    bytes_read = fread(*buffer, sizeof(char), number_of_bytes, file);

    *(*buffer + bytes_read) = '\0';

    fclose(file);

    /* ======== */
    
    return 0;
}

/* ================================================================ */

int extract_JSON_data(const cJSON* root, const char* name, cJSON_bool (*check)(const cJSON* const), cJSON** data) {

    if (root == NULL) {
        return -1;
    }

    if (check == NULL) {
        return -1;
    }

    if ((*data = cJSON_GetObjectItemCaseSensitive(root, name)) == NULL) {

        fprintf(stderr, "\033[0;31m%s\033[0;37m: there is no such element (\033[0;34m%s\033[0;37m) in the file\n", "Error", name);

        return -2;
    }

    if (check(*data) != 1) {
        return -1;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int cJSON_Parse_check(const char* buffer, cJSON** root) {
    
    if ((*root = cJSON_Parse(buffer)) == NULL) {

        const char* error_ptr = NULL;

        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            ERROR(error_ptr);
        }

        return -1;
    }

    return 0;
}

/* ================================================================ */

int LittleThing_init(void) {

    const char* default_config_SDL = "SDL.json";
    const char* default_config_App = "Application.json";
    char* buffer = NULL;

    cJSON* root = NULL;

    Uint32 SDL_flags;

    int status = 0;

    struct window_props props = {.w_flags = 0, .r_flags = 0};

    /* ================================================================ */
    /* =============== Trying to read a `SDL.json` file =============== */
    /* ================================================================ */

    while ((status = read_file(default_config_SDL, &buffer)) != 0) {

        if (status == ENOENT) {
            /* In case of absence of a configuration file, a new one will be created with default settings */
            WARNING("missing configuration file. Creating a default one ...");

            if ((status = create_default_SDL(default_config_SDL)) != 0) {

                ERROR(strerror(errno));

                goto end;
            }
        }
    }

    /* =============== Parsing the file content, buffer =============== */
    if ((status = cJSON_Parse_check(buffer, &root)) != 0) {
        goto end;
    }

    SDL_flags = SDL_Init_get_flags(root);

    /* ======================= Initializing SDL ======================= */
    if ((status = SDL_Init(SDL_flags)) != 0) {

        ERROR(SDL_GetError());

        goto end;
    }

    free(buffer);

    /* ================================================================ */
    /* =========== Trying to read a `Application.json` file =========== */
    /* ================================================================ */

    while ((status = read_file(default_config_App, &buffer)) != 0) {

        if (status == ENOENT) {
            /* In case of absence of a configuration file, a new one will be created with default settings */
            WARNING("missing configuration file. Creating a default one ...");

            if ((status = create_default_Application(default_config_App)) != 0) {

                ERROR(strerror(errno));

                goto end;
            }
        }
    }

    /* =============== Parsing the file content, buffer =============== */
    if ((status = cJSON_Parse_check(buffer, &root)) != 0) {
        goto end;
    }

    get_props(&props, root);

    if ((status = Application_new(&props, &g_app)) != 0) {
        goto end;
    }

    RGBA_color_SET(255, 255, 255, 255);

    /* ======== */

    end:
        free(buffer);
        cJSON_Delete(root);

        return status;
}

/* ================================================================ */

int LittleThing_quit(void) {

    int status = 0;

    SDL_Quit();

    Application_destroy(&g_app);

    /* ======== */

    return status;
}

/* ================================================================ */

int write_to_file(const char* str, const char* name) {

    FILE* file = NULL;

    if (name == NULL) {
        return -1;
    }

    if ((file = fopen(name, "w+")) == NULL) {
        return errno;
    }

    fprintf(file, "%s", str);

    fclose(file);

    /* ======== */

    return 0;
}

/* ================================================================ */
