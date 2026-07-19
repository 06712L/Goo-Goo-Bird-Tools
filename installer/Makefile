#Folder
ROOT ?= $(CURDIR)
BUILD_DIR := $(ROOT)/build
SRC_DIR := src
INCLUDE_DIR := ./include

#args
DEBUG ?= 0

#Compiler
CC ?= musl-gcc
CFLAGS ?= -std=gnu17 -Wall -Werror -iquote $(INCLUDE_DIR)
LDFLAGS = -static

#debug
ifeq ($(DEBUG),1)
BIN_DIR := $(BUILD_DIR)/bin-debug
OBJS_DIR := $(BUILD_DIR)/objs-debug
CFLAGS += -g3 -O0

#release
else
BIN_DIR := $(BUILD_DIR)/bin
OBJS_DIR := $(BUILD_DIR)/objs
CFLAGS += -O2
LDFLAGS += -s
endif

OBJS := $(OBJS_DIR)/main.o $(OBJS_DIR)/installer.o
TARGET := installer

.PHONY: build clean cleanbin cleanobj
all: build


build: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/$(TARGET)


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)


cleanbin:
	rm -rf $(BIN_DIR)


cleanobj:
	rm -rf $(OBJS_DIR)
