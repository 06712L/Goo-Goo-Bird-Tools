.PHONY: BUILD_goo-goo-bird-tools \

#goo-goo-bird-tools
$(OBJS_DIR)/selection-tool.o $(OBJS_DIR)/goo-goo-bird-tools.o: BUILD_goo-goo-bird-tools
CORE_OBJS += $(OBJS_DIR)/selection-tool.o $(OBJS_DIR)/goo-goo-bird-tools.o
BUILD_goo-goo-bird-tools: $(shell find ./ggb-core/goo-goo-bird-tools -type f -name "*.c")
	$(MAKE) -C ./ggb-core/goo-goo-bird-tools assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)
