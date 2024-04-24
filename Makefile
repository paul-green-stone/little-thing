# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects
# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, Core.o cJSON.o Window.o Application.o Timer.o)

# C compiler
CC := gcc
# We are interested in onject files without linking them into an executable
CFLAGS := -g -c
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -fPIC -O2

# Additional libraries that need to be linked to the final executable
LDFLAGS := -lSDL2

AR := ar
ARFLAGS := -r -s

OS_NAME := $(shell uname -s)

INCLUDE := $(wildcard include/*/*.h)

LIB_NAME := littlething

ifeq ($(OS_NAME), Linux)
    LIB_PREFIX := lib
    LIB_SUFFIX := .a
    DLL_SUFFIX := .so
else ifeq ($(OS_NAME), Darwin)
    LIB_PREFIX := lib
    LIB_SUFFIX := .a
    DLL_SUFFIX := .dylib
else ifeq ($(OS_NAME), MINGW32_NT-10.0)
    LIB_PREFIX :=
    LIB_SUFFIX := .a
    DLL_SUFFIX := .dll
else
    $(error Unsupported operating system)
endif

TARGET_STATIC				:= $(LIB_PREFIX)$(LIB_NAME)$(LIB_SUFFIX)
TARGET_SHARED				:= $(LIB_PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================ #

CORE						:= $(addprefix source/core/, core.c)
CJSON                       := $(addprefix source/core/, cJSON.c)

WINDOW := $(addprefix source/window/, window.c)

APPLICATION := $(addprefix source/application/, application.c)

TIMER := $(addprefix source/timer/, timer.c)

# ================================================================ #

all: $(TARGET_STATIC) $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJECTS)
	$(AR) $(ARFLAGS) $(TARGET_STATIC) $^

$(TARGET_SHARED): $(OBJECTS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# ================================ #

# Core Module
$(OBJDIR)/Core.o: $(CORE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# cJSON Module
$(OBJDIR)/cJSON.o: $(CJSON) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Window Module
$(OBJDIR)/Window.o: $(WINDOW) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Application Module
$(OBJDIR)/Application.o: $(APPLICATION) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Timer Module
$(OBJDIR)/Timer.o: $(TIMER) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# ================================================================ #

$(shell mkdir -p $(OBJDIR))

.PHONY: clean

clean:
	rm -rf $(OBJS) $(OBJDIR) $(TARGET_STATIC) $(TARGET_SHARED)
