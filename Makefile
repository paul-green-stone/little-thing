# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects
# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, Core.o cJSON.o Window.o Application.o Timer.o Input.o Texture.o Text.o Camera.o Math.o Entity.o)

MATHOBJS := $(addprefix $(OBJDIR)/, math.o Vector2.o Rect2.o Line_2.o Shapes_2.o)

# C compiler
CC := gcc
# We are interested in onject files without linking them into an executable
CFLAGS := -std=c11 -g -c
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -fPIC -O2

# Additional libraries that need to be linked to the final executable
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf

AR := ar
ARFLAGS := -r -s

OS_NAME := $(shell uname -s)

INCLUDE := $(wildcard include/*/*.h)
MATHINCLUDE := $(wildcard include/Math/*/*.h)

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

TARGET_STATIC := $(LIB_PREFIX)$(LIB_NAME)$(LIB_SUFFIX)
TARGET_SHARED := $(LIB_PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================ #

CORE := $(addprefix source/core/, core.c)
CJSON := $(addprefix source/core/, cJSON.c)

WINDOW := $(addprefix source/window/, window.c)

APPLICATION := $(addprefix source/application/, application.c)

TIMER := $(addprefix source/timer/, timer.c)

INPUT := $(addprefix source/input/, input.c)

TEXTURE := $(addprefix source/texture/, texture.c)

TEXT := $(addprefix source/text/, text.c)

CAMERA := $(addprefix source/camera/, camera.c)

ENTITY := $(addprefix source/entity/, entity.c)

# ================ #

MATH := $(addprefix source/Math/, math.c)

VECTOR2 := $(addprefix source/Math/vector2/, vector2.c)

RECT2 := $(addprefix source/Math/rect2/, rect2.c)

LINE_2 := $(addprefix source/Math/shapes_2/line_2/, line_2.c)

SHAPES_2 := $(addprefix source/Math/shapes_2/, shape_2.c)

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

# Input Module
$(OBJDIR)/Input.o: $(INPUT) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Texture Module
$(OBJDIR)/Texture.o: $(TEXTURE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Text Module
$(OBJDIR)/Text.o: $(TEXT) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Camera Module
$(OBJDIR)/Camera.o: $(CAMERA) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Entity Module
$(OBJDIR)/Entity.o: $(ENTITY) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# =============== #

$(OBJDIR)/Math.o: $(MATHOBJS)
	ld -r -o $@ $^

$(OBJDIR)/math.o: $(MATH) $(MATHINCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Vector2 Module
$(OBJDIR)/Vector2.o: $(VECTOR2) $(MATHINCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Line_2 Module
$(OBJDIR)/Line_2.o: $(LINE_2) $(MATHINCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Rect2 Module
$(OBJDIR)/Rect2.o: $(RECT2) $(MATHINCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# Shapes_2 Module
$(OBJDIR)/Shapes_2.o: $(SHAPES_2) $(MATHINCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $< $(CFLAGS)

# ================================================================ #

$(shell mkdir -p $(OBJDIR))

.PHONY: clean

clean:
	rm -rf $(OBJS) $(OBJDIR) $(TARGET_STATIC) $(TARGET_SHARED)
