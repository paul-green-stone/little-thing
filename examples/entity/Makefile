CC := gcc

CFLAGS := -g
ALL_CFLAGS := -Wall -Wextra -pedantic-errors -O2

LDFLAGS := -lm -lSDL2 -lSDL2_image -lSDL2_ttf

PROG := a.out

# ================================================================ #

# Make a window.o object file
$(PROG): main.c App_handle_input.c App_run.c
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $^ ../../liblittlething.a $(LDFLAGS)

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out