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

.PHONY: ggb-core link clean
all: ggb-core

include ggb-core/core.mk
ggb-core: $(CORE_OBJS)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(LDFLAGS) $^ -o $(BIN_DIR)/$(TARGET)


link: $(BIN_DIR)/$(TARGET)
	ln -sf $(CURDIR)/$(BIN_DIR)/$(TARGET) ~/.local/bin/$(TARGET)


clean:
	rm -rf $(BUILD_DIR) ~/.local/bin/$(TARGET)
