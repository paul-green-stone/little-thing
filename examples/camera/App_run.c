#include "../../include/littlething.h"

/* ================================================================ */
/* =============== Include additional headers here ================ */
/* ================================================================ */

/* ================================================================ */

#define PLAYER_SIZE 32

#define PLAYER_SPEED 64

struct player {

    float x;
    float y;

    int width;
    int height;
};

/* ================================================================ */

void move(struct player* player, SDL_Rect* rect, Camera_t c, SDL_Rect* b) {

    if (key_is_pressed(SDL_SCANCODE_W)) {
        player->y -= PLAYER_SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_S)) {
        player->y += PLAYER_SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_D)) {
        player->x += PLAYER_SPEED * g_app->timer->d;
    }

    if (key_is_pressed(SDL_SCANCODE_A)) {
        player->x -= PLAYER_SPEED * g_app->timer->d;
    }

    rect->x = player->x;
    rect->y = player->y;
}

void show_coords(SDL_Rect* r, Camera_t c, SDL_Rect* b, SDL_Rect* grid) {

    if (key_just_pressed(SDL_SCANCODE_E)) {

        printf("Player global coordinates: [%d; %d]\n", r->x, r->y);
        printf("Player local coordinates: [%d; %d]\n\n", r->x - c->dimensions->x, r->y - c->dimensions->y);

        printf("Camera global coordinates (upper left corner): [%d; %d]\n", c->dimensions->x, c->dimensions->y);
        printf("Camera global coordinates (bottom right corner): [%d; %d]\n\n", c->dimensions->x + c->dimensions->w, c->dimensions->y + c->dimensions->h);

        printf("Building global coordinates: [%d; %d]\n", b->x, b->y);
        printf("Building local coordinates: [%d; %d]\n\n", b->x - c->dimensions->x, b->y - c->dimensions->y);

        printf("Grid starts at: [%d; %d]\n", grid->x, grid->y);
        printf("Grid finishes at: [%d; %d]\n", grid->x + grid->w, grid->y + grid->h);
        printf("Its dimensions: [%d; %d]\n", grid->x + grid->w - grid->x, grid->y + grid->h - grid->y);

        printf("==========\n");
    }
}

void App_run(const App_t app) {

    App_t a = NULL;

    if ((app == NULL) && (g_app == NULL)) {
        return ;
    }

    a = (app == NULL) ? g_app : app;

    /* ================================================================ */
    /* =================== Define variables here  ===================== */
    /* ================================================================ */

    TTF_Font* font = Font_load("../text/fonts/PressStart2P-Regular.ttf", 8);

    Text_t player_pos = NULL;
    Text_t camera_pos = NULL;

    int width = 0;
    int height = 0;
    SDL_GetWindowSize(a->window->w, &width, &height);

    Camera_t camera = NULL;
    Camera_new(0, 0, width, height, &camera);

    struct player player = {width / 2 - PLAYER_SIZE / 2, height / 2 - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};
    SDL_Rect rect = {player.x, player.y, player.width, player.height};

    SDL_Rect building = {-32, 64, 96, 96};
    SDL_Rect building_rect = {building.x - camera->dimensions->x, building.y - camera->dimensions->y, building.w, building.h};

    Camera_bind(camera, &rect);

    SDL_Rect grid = {camera->dimensions->x - 64, camera->dimensions->y - 64, camera->dimensions->w + 128, camera->dimensions->h + 128};

    HEX_color_SET(0x000000, 0xFF);
    char player_coord_buf[32];
    sprintf(player_coord_buf, "%d; %d", (int) player.x, (int) player.y);
    Text_new(player_coord_buf, font, &player_pos);

    while (a->is_running) {

        /* ================================================================ */
        /* ===================== Update timers here  ====================== */
        /* ================================================================ */

        Timer_tick(a->timer);

        /* ================================================================ */

        App_handle_input(a);

        move(&player, &rect, camera, &building);

        grid.x = (camera->dimensions->x - 64) - ((int) player.x % 32);
        grid.y = (camera->dimensions->y - 64) - ((int) player.y % 32);

        HEX_color_SET(0x000000, 0xFF);
        sprintf(player_coord_buf, "%d; %d", (int) player.x, (int) player.y);
        Text_update(player_pos, player_coord_buf, font);

        player_pos->pos.x = player.x + player.width + 4;
        player_pos->pos.y = player.y - 8;

        Camera_center(camera);

        show_coords(&rect, camera, &building, &grid);

        if (Timer_is_ready(a->timer)) {
                
            /* Clear the window */
            RGBA_color_SET(255, 255, 255, 255);
            SDL_RenderClear(a->window->r);

            /* ================================================================ */
            /* ================= User draw functions go here  ================= */
            /* ================================================================ */

            HEX_color_SET(0xFF0000, 0xFF);
            SDL_Rect offset = Camera_update(camera, &building);
            SDL_RenderFillRect(a->window->r, &offset);

            HEX_color_SET(0x00FF00, 0xFF);
            offset = Camera_update(camera, &grid);
            draw_grid(a->window, 32, 32, &offset);

            HEX_color_SET(0x000000, 0xFF);
            offset = Camera_update(camera, &rect);
            SDL_RenderFillRect(a->window->r, &offset);

            offset = Camera_update(camera, &player_pos->pos);
            player_pos->pos = offset;

            Text_display(player_pos, a->window);

            /* ================================================================ */
            /* ================================================================ */
            /* ================================================================ */

            SDL_RenderPresent(a->window->r);

            Timer_reset(a->timer);
        }
    }

    Camera_destroy(&camera);

    Font_unload(font);

    Text_destroy(&player_pos);

    return ;
}

/* ================================================================ */
