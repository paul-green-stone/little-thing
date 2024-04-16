CC 							:= gcc
CFLAGS						:=
ALL_CFLAGS					:= $(CFLAGS) -Wall -Wextra -pedantic-errors -O2 -lcunit

SRCS						:= $(wildcard ./*.c)

BIN							:= a.out

# ================================================================ #

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(ALL_CFLAGS) $< -o $@ ../../liblittlething.a -lSDL2

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(BIN)