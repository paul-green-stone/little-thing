#!/usr/local/bin/perl -w

use strict;

# ================================================================ #

open (my $file, '>', 'App_run.c')
    or die "Could not create `App_run.c` file: $!\n";

my $file_content = "
#include \"./include/littlething.h\"

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

print $file $file_content;

close $file;

# ================================================================ #
