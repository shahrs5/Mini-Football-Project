.PHONY: all clean

PROJECT_NAME       ?= game
RAYLIB_VERSION     ?= 4.5.0
RAYLIB_PATH        ?= ../..

COMPILER_PATH      ?= C:/raylib/w64devkit/bin

PLATFORM           ?= PLATFORM_DESKTOP
DESTDIR            ?= /usr/local
RAYLIB_INSTALL_PATH ?= $(DESTDIR)/lib
RAYLIB_H_INSTALL_PATH ?= $(DESTDIR)/include
RAYLIB_LIBTYPE     ?= STATIC
BUILD_MODE         ?= RELEASE
USE_EXTERNAL_GLFW  ?= FALSE
USE_WAYLAND_DISPLAY ?= FALSE

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
    else
        UNAMEOS=$(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS=LINUX
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS=OSX
        endif
    endif
endif

RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src
EXAMPLE_RUNTIME_PATH   ?= $(RAYLIB_RELEASE_PATH)

CC = g++

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),OSX)
        CC = clang++
    endif
endif

MAKE = mingw32-make

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),LINUX)
        MAKE = make
    endif
    ifeq ($(PLATFORM_OS),OSX)
        MAKE = make
    endif
endif

CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        CFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        ifeq ($(RAYLIB_LIBTYPE),STATIC)
            CFLAGS += -D_DEFAULT_SOURCE
        endif
        ifeq ($(RAYLIB_LIBTYPE),SHARED)
            CFLAGS += -Wl,-rpath,$(EXAMPLE_RUNTIME_PATH)
        endif
    endif
endif

INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

ifneq ($(wildcard /opt/homebrew/include/.*),)
    INCLUDE_PATHS += -I/opt/homebrew/include
endif

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),LINUX)
        INCLUDE_PATHS = -I$(RAYLIB_H_INSTALL_PATH) -isystem. -isystem$(RAYLIB_PATH)/src -isystem$(RAYLIB_PATH)/release/include -isystem$(RAYLIB_PATH)/src/external
    endif
endif

LDFLAGS = -L.

ifneq ($(wildcard $(RAYLIB_RELEASE_PATH)/.*),)
    LDFLAGS += -L$(RAYLIB_RELEASE_PATH)
endif
ifneq ($(wildcard $(RAYLIB_PATH)/src/.*),)
    LDFLAGS += -L$(RAYLIB_PATH)/src
endif
ifneq ($(wildcard /opt/homebrew/lib/.*),)
    LDFLAGS += -L/opt/homebrew/lib
endif

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),LINUX)
        LDFLAGS = -L. -L$(RAYLIB_INSTALL_PATH) -L$(RAYLIB_RELEASE_PATH)
    endif
endif

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
        ifeq ($(USE_WAYLAND_DISPLAY),TRUE)
            LDFLAGS += -DPLATFORM_WAYLAND
            LDLIBS += -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
        endif
        ifeq ($(USE_EXTERNAL_GLFW),TRUE)
            LDLIBS += -lglfw
        endif
    endif
    ifeq ($(PLATFORM_OS),OSX)
        LDLIBS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
    endif
endif

OBJS = ball.cpp main.cpp timer.cpp game.cpp player.cpp

EXE = $(PROJECT_NAME)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJS) $(EXE)
