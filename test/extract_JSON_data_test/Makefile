CC := gcc
CFLAGS :=
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -O2

LDFLAGS := -lcunit -lSDL2

SRCS := $(wildcard ./*.c)

BIN := a.out

# ================================================================ #

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(ALL_CFLAGS) $< -o $@ ../../liblittlething.a $(LDFLAGS)

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(BIN)