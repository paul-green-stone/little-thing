# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects
# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, Core.o)

CC 							:= gcc
CFLAGS						:= -g -c
ALL_CFLAGS					:= $(CFLAGS) -Wall -Wextra -pedantic-errors -fPIC -O2 -lsdl2

AR							:= ar
ARFLAGS						:= -r -s

OS_NAME						:= $(shell uname -s)

INCLUDE						:= $(wildcard include/*/*.h)

LIB_NAME					:= littlething

ifeq ($(OS_NAME), Linux)
    LIB_PREFIX				:= lib
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .so
else ifeq ($(OS_NAME), Darwin)
    LIB_PREFIX				:= lib
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .dylib
else ifeq ($(OS_NAME), MINGW32_NT-10.0)
    LIB_PREFIX				:=
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .dll
else
    $(error Unsupported operating system)
endif

TARGET_STATIC				:= $(LIB_PREFIX)$(LIB_NAME)$(LIB_SUFFIX)
TARGET_SHARED				:= $(LIB_PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================ #

CORE						:= $(addprefix source/core/, core.c cJSON.c)

# ================================================================ #

all: $(TARGET_STATIC) $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJECTS)
	$(AR) $(ARFLAGS) $(TARGET_STATIC) $^

$(TARGET_SHARED): $(OBJECTS)
	$(CC) -shared -o $@ $^

# ================================ #

# Core Module
$(OBJDIR)/Core.o: $(CORE) $(INCLUDE)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -o $@ $<

# ================================================================ #

$(shell mkdir -p $(OBJDIR))

.PHONY: clean

clean:
	rm -rf $(OBJS) $(OBJDIR) $(TARGET_STATIC) $(TARGET_SHARED)
