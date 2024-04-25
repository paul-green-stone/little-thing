#!/usr/local/bin/perl -w

use strict;

# ================================================================ #
# ========== This script generates two essential files, ========== # 
# ============ `App_run.c` and `App_handle_input.c`, ============= #
# ======= which are necessary for an end-user application. ======= #
# ================================================================ #
# =================== In `App_handle_input.c`, =================== #
# ====== you can write code responsible for event handling. ====== #
# This is the place where you can handle various user input events #
# ================================================================ #
# ====================== On the other hand, ====================== #
# === `the App_run` function takes care of the heavy lifting. ==== #
# ============== It manages tasks such as drawing, =============== #
# ============== screen updates, timers, and more. =============== #
# ================================================================ #
# ======== Feel free to customize and modify these files ========= #
# =========== to suit your specific application needs. =========== #
# ================================================================ #

# ================ Create a new file `App_run.c` ================= #
open (my $file, '>', 'App_run.c')
    or die "Could not create `App_run.c` file: $!\n";

my $file_content; 

{
    $file_content = "#include \"./include/littlething.h\"

    /* ================================================================ */

    void App_run(const App_t app) {

        App_t a = NULL;

        if ((app == NULL) && (g_app == NULL)) {
            return ;
        }

        a = (app == NULL) ? g_app : app;

        while (a->is_running) {

            /* ================================================================ */
            /* ===================== Update timers here  ====================== */
            /* ================================================================ */

            Timer_tick(a->timer);

            App_handle_input(a);

            if (Timer_is_ready(a->timer)) {
                
                /* Clear the window */
                SDL_SetRenderDrawColor(a->window->r, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(a->window->r);

                /* ================================================================ */
                /* ===================== User code goes here  ===================== */
                /* ================================================================ */

                /* ================================================================ */
                /* ================================================================ */
                /* ================================================================ */

                SDL_SetRenderDrawColor(a->window->r, 0xff, 0x00, 0x00, 0xff);

                SDL_RenderPresent(a->window->r);

                Timer_reset(a->timer);
            }
        }

        return ;
    }

    /* ================================================================ */
    ";
}

print $file $file_content;

close $file;


# ============= Create a new file `App_handle_input.c` ============= #
open ($file, '>', 'App_handle_input.c')
    or die "Could not create `App_run.c` file: $!\n";

{
    $file_content = "#include \"./include/littlething.h\"

    /* ================================================================ */

    void App_handle_input(const App_t app) {
        
        while (SDL_PollEvent(&g_event)) {

            switch (g_event.type) {

                case SDL_QUIT:

                    app->is_running = !app->is_running;

                    break ;
            }
        }

        return ;
    }
    ";
}

print $file $file_content;

close $file;

# ================================================================ #
