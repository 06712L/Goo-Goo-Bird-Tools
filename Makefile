CC ?= gcc
CFLAGS := -std=gnu17 -Wall -fpie -iquote include
DEBUG ?= 0
STATIC ?= 0
ifeq ($(DEBUG),1)
CFLAGS += -O0 -g3
OBJS_DIR := Build/oiia-debug
TARGET_DIR = Build/bin-debug
else
CFLAGS += -O2 -s
OBJS_DIR := Build/oiia
TARGET_DIR = Build/bin
endif
ifeq ($(STATIC),1)
CFLAGS += -static
endif
LIBS ?=
TARGET := goo-goo-bird-tools
SRC_DIR := src
MAIN_OBJS = $(OBJS_DIR)/main.o
TOTAL_OBJS = $(MAIN_OBJS)

.PHONY: ggb-main ggb-core ggb-expand link clean
all: ggb-main


ggb-main:$(TOTAL_OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(TOTAL_OBJS) -o $(TARGET_DIR)/$(TARGET)
	@make link


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p Build
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


link: $(TARGET_DIR)/$(TARGET)
	ln -sf $(CURDIR)/$(TARGET_DIR)/$(TARGET) ~/.local/bin/$(TARGET)


clean:
	rm -rf $(OBJS_DIR) $(TARGET_DIR) ~/.local/bin/$(TARGET)
