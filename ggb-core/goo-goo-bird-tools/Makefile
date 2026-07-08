#Folder
ROOT ?= $(CURDIR)
BUILD_DIR := $(ROOT)/build
SRC_DIR := src
INCLUDE_DIR := include

#args
DEBUG ?= 0
STATIC ?= 0

#Compiler
CC ?= gcc
CFLAGS ?= -std=gnu17 -Wall -Werror -iquote $(INCLUDE_DIR)
LDFLAGS =

#debug
ifeq ($(DEBUG),1)
BIN_DIR := $(BUILD_DIR)/bin-debug
OBJS_DIR := $(BUILD_DIR)/objs-debug
CFLAGS += -g3

#release
else
BIN_DIR := $(BUILD_DIR)/bin
OBJS_DIR := $(BUILD_DIR)/objs
LDFLAGS += -s
endif

#static
ifeq ($(STATIC),1)
LDFLAGS += -static
endif

OBJS := $(OBJS_DIR)/main.o
TARGET := goo-goo-bird-tools

.PHONY: main clean cleanbin cleanobj
all: main


main: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/$(TARGET)


assembly: $(OBJS)


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)


cleanbin:
	rm -rf $(BIN_DIR)


cleanobj:
	rm -rf $(OBJS_DIR)
