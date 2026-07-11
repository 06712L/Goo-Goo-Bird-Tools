#goo-goo-bird-tools
$(OBJS_DIR)/%-ggbt.o: $(shell find ./ggb-core/goo-goo-bird-tools -type f -name "*.c")
	make -C ./ggb-core/goo-goo-bird-tools assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)
CORE_OBJS += $(OBJS_DIR)/selection-tool-ggbt.o $(OBJS_DIR)/goo-goo-bird-tools-ggbt.o

#goo-goo-calculator
$(OBJS_DIR)/%-ggc.o: $(shell find ./ggb-core/goo-goo-calculator -type f -name "*.c")
	make -C ./ggb-core/goo-goo-calculator assembly ROOT=$(ROOT) CC=$(CC) DEBUG=$(DEBUG) STATIC=$(STATIC)
CORE_OBJS += $(OBJS_DIR)/goo-goo-calculator-main-ggc.o $(OBJS_DIR)/calculate-ggc.o
