# Compiler and flags
CC := ccache gcc
RAYLIB_FLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS := $(shell pkg-config --libs raylib)

# Directories
BUILD_DIR := build
SRC_DIR := src
ROCKS_DIR := ../rocks

# Include paths
INCLUDE_FLAGS := -I./include \
	-I../rocks/include \
	-I../rocks/include/renderer \
	-I../rocks/include/components \
	-I../rocks/clay

# Common compiler flags
COMMON_FLAGS := -Wall -Werror -O2 \
	-Wno-unused-variable \
	-Wno-missing-braces \
	-Wno-unused-but-set-variable \
	-DROCKS_USE_RAYLIB \
	-DCLAY_DESKTOP

# Source files
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
ROCKS_FILES := $(shell find $(ROCKS_DIR)/src -maxdepth 1 -type f -name '*.c')
ROCKS_COMP_FILES := $(shell find $(ROCKS_DIR)/src/components -type f -name '*.c')
ROCKS_RENDERER_FILES := $(shell find $(ROCKS_DIR)/src/renderer -type f -name 'raylib_*.c')

# Object files
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_FILES) $(ROCKS_FILES) $(ROCKS_COMP_FILES) $(ROCKS_RENDERER_FILES)))

# Main target
all: prepare $(BUILD_DIR)/waozi copy_assets

# Prepare build directory
prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/assets

# Compilation rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/%.o: $(ROCKS_DIR)/src/%.c
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/%.o: $(ROCKS_DIR)/src/components/%.c
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/%.o: $(ROCKS_DIR)/src/renderer/%.c
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

# Linking
$(BUILD_DIR)/waozi: $(OBJ_FILES)
	@echo "Linking..."
	@$(CC) $^ -o $@ $(RAYLIB_FLAGS) $(RAYLIB_LIBS) -lm -ldl -lpthread

# Copy assets
copy_assets:
	@echo "Copying assets..."
	@if [ -d "assets" ]; then cp -r assets/* $(BUILD_DIR)/assets/; fi

# Clean
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean completed successfully!"

.PHONY: all prepare clean copy_assets
