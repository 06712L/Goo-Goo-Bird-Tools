CC ?= gcc
CFLAGS := -std=gnu17 -Wall -fpie -iquote include
LDFLAGS :=
DEBUG ?= 0
STATIC ?= 0
ifeq ($(DEBUG),1)
CFLAGS += -O0 -g3
OBJS_DIR := build/oiia-debug
TARGET_DIR = build/bin-debug
else
CFLAGS += -O2
LDFLAGS += -s
OBJS_DIR := build/oiia
TARGET_DIR = build/bin
endif
ifeq ($(STATIC),1)
LDFLAGS += -static
endif
LIBS ?=
TARGET := goo-goo-bird-tools
SRC_DIR := src
MAIN_OBJS = $(OBJS_DIR)/main.o
TOTAL_OBJS = $(MAIN_OBJS)

.PHONY: ggb-main link clean
all: ggb-main


ggb-main:$(TOTAL_OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(LDFLAGS) $(TOTAL_OBJS) -o $(TARGET_DIR)/$(TARGET)
	@make link


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p build
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


link: $(TARGET_DIR)/$(TARGET)
	ln -sf $(CURDIR)/$(TARGET_DIR)/$(TARGET) ~/.local/bin/$(TARGET)


clean:
	rm -rf $(OBJS_DIR) $(TARGET_DIR) ~/.local/bin/$(TARGET)
