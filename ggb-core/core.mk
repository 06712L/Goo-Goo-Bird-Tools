.PHONY: BUILD_goo-goo-bird-tools \
BUILD_goo-goo-calculator \

#goo-goo-bird-tools
$(OBJS_DIR)/selection-tool.o $(OBJS_DIR)/goo-goo-bird-tools.o: BUILD_goo-goo-bird-tools
CORE_OBJS += $(OBJS_DIR)/selection-tool.o $(OBJS_DIR)/goo-goo-bird-tools.o
BUILD_goo-goo-bird-tools: $(shell find ./ggb-core/goo-goo-bird-tools -type f -name "*.c")
	$(MAKE) -C ./ggb-core/goo-goo-bird-tools assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)


#goo-goo-calculator
$(OBJS_DIR)/goo-goo-calculator-main.o $(OBJS_DIR)/calculate.o: BUILD_goo-goo-calculator
CORE_OBJS +=  $(OBJS_DIR)/goo-goo-calculator-main.o $(OBJS_DIR)/calculate.o
BUILD_goo-goo-calculator: $(shell find ./ggb-core/goo-goo-calculator -type f -name "*.c")
	$(MAKE) -C ./ggb-core/goo-goo-calculator assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)
