PROJ_NAME = VS
CC = gcc 
BUILD_DIR = ./bin
SRC_DIR = ./src
FILES = $(wildcard ./src/*.c)
FILES += $(wildcard ./src/ui/*.c)
SRC_FILES = $(filter-out ./src/test.c, $(FILES))
SRC_OBJS = $(SRC_FILES:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)
DFLAGS = -g -O0 -Wall -Werror -MMD -MP

export LD_LIBRARY_PATH = $(PWD)/lib

ifeq ($(OS),Windows_NT)
	LIBS += -L ./lib
	INCLUDE += -I ./include
	LINK += -l:glfw3.dll -l:libcglm.a -lopengl32 -lalut -lopenal -l:libengine_win.a
else
	detected_OS = $(shell uname)
	ifeq ($(detected_OS),Linux)
		LIBS += -L usr/lib/x86_64-linux-gnu/
		LIBS += -L ./lib
		INCLUDE += -I ./include
		LINK += -l:libglfw.so.3 -lGL -lX11 -l:libXrandr.so.2 -l:libXi.so.6 -l:libengine_lin.a
		LINK += -ldl -lm -l:libcglm.so.0 -lpthread -lalut -lopenal
	endif
endif

.PHONY: clean run debug test main

threads:
	@$(MAKE) -j all

all: ./bin/src $(BUILD_DIR)/$(PROJ_NAME)

$(BUILD_DIR)/$(PROJ_NAME): $(SRC_OBJS)
	@$(CC) $(LIBS) $(SRC_OBJS) -o $(BUILD_DIR)/$(PROJ_NAME) $(LINK)
	@echo "Created $(PROJ_NAME) binary"

$(BUILD_DIR)/%.c.o: %.c
	@$(CC) $(DFLAGS) $(INCLUDE) -c $< -o $@
	@echo "--> Compiled: " $<

./bin/src:
	@mkdir -p ./bin/src/ui
	@echo "Created build directory"

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f ./assets/*/*/*.obj.bin*
	@rm -f ./assets/*/*.obj.bin*
	@echo "Cleaned ./bin"
	@mkdir ./bin/
	@cp ./lib/glfw3.dll ./bin/glfw3.dll

run: threads
	@./bin/$(PROJ_NAME)

debug:
	gdb ./bin/$(PROJ_NAME)

-include $(DEPS)

