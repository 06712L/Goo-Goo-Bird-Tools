#Compiler
CC ?= gcc
LDFLAGS =

#Folder
ROOT := $(CURDIR)
BUILD_DIR := $(ROOT)/build

#args
DEBUG ?= 0
STATIC ?= 0

#debug
ifeq ($(DEBUG),1)
BIN_DIR := $(BUILD_DIR)/bin-debug
OBJS_DIR := $(BUILD_DIR)/objs-debug

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

TARGET := goo-goo-bird-tools
CORE_OBJS =

.PHONY: ggb-core link clean cleanobj cleanbin
all: ggb-core

include ggb-core/core.mk
ggb-core: $(CORE_OBJS)
	@mkdir -p $(BIN_DIR) $(OBJS_DIR)
	$(CC) $(LDFLAGS) $^ -o $(BIN_DIR)/$(TARGET)


link: $(BIN_DIR)/$(TARGET)
	@mkdir -p ~/.local/bin
	ln -sf $(BIN_DIR)/$(TARGET) ~/.local/bin/$(TARGET)


clean:
	rm -rf $(BUILD_DIR) ~/.local/bin/$(TARGET)

cleanobj:
	rm -rf  $(OBJS_DIR)


cleanbin:
	rm -rf $(BIN_DIR)
