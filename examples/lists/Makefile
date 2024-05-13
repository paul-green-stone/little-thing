CC := gcc

CFLAGS := -g
ALL_CFLAGS := -Wall -Wextra -pedantic-errors -O2

LDFLAGS := -lSDL2 -lSDL2_image

PROG := a.out

# ================================================================ #

# Make a window.o object file
$(PROG): main.c App_handle_input.c App_run.c helpers.c
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $^ ../../liblittlething.a ./linked-lists/liblists.a $(LDFLAGS)

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out