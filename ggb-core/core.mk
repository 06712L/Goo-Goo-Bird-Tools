$(OBJS_DIR)/%.o: $(shell find ./ggb-core -type f -name "*.c")
#goo-goo-bird-tools
	make -C ./ggb-core/goo-goo-bird-tools assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)
CORE_OBJS += $(OBJS_DIR)/selection-tool.o $(OBJS_DIR)/goo-goo-bird-tools.o
