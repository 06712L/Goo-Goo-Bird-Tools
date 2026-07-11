#Folder
ROOT ?= $(CURDIR)
BUILD_DIR := $(ROOT)/build
SRC_DIR := src
INCLUDE_DIR := ./include

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
CFLAGS += -g3 -O0

#release
else
BIN_DIR := $(BUILD_DIR)/bin
OBJS_DIR := $(BUILD_DIR)/objs
CFLAGS += -O2
LDFLAGS += -s
endif

#static
ifeq ($(STATIC),1)
LDFLAGS += -static
endif

OBJS := $(OBJS_DIR)/goo-goo-calculator-main-ggc.o $(OBJS_DIR)/calculate-ggc.o
TARGET := goo-goo-calculator

.PHONY: main assembly clean cleanbin cleanobj
all: main


main: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/$(TARGET)


assembly: $(OBJS)
CFLAGS += -DCOMBINATION -iquote $(ROOT)/ggb-core/include


$(OBJS_DIR)/%-ggc.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)


cleanbin:
	rm -rf $(BIN_DIR)


cleanobj:
	rm -rf $(OBJS_DIR)
