# Compiler and flags
CC := ccache gcc
RAYLIB_FLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS := $(shell pkg-config --libs raylib)

# Directories
BUILD_DIR := build
SRC_DIR := src
ROCKS_DIR := rocks
CLAY_DIR := rocks/clay
VENDOR_DIR := rocks/vendor
NANOSVG_DIR := $(VENDOR_DIR)/nanosvg/src
CMARK_DIR := $(VENDOR_DIR)/cmark
CMARK_SRC_DIR := $(CMARK_DIR)/src
CMARK_BUILD_DIR := $(CMARK_DIR)/build
CMARK_INCLUDE_DIR := $(CMARK_BUILD_DIR)/src  # For generated headers

# Include paths
INCLUDE_FLAGS := -I./include \
                 -I$(ROCKS_DIR)/include \
                 -I$(ROCKS_DIR)/include/renderer \
                 -I$(ROCKS_DIR)/include/components \
                 -I$(CLAY_DIR) \
                 -I$(NANOSVG_DIR) \
                 -I$(CMARK_SRC_DIR) \
                 -I$(CMARK_INCLUDE_DIR)

# Common compiler flags
COMMON_FLAGS := -Wall -Werror -O2 \
                -Wno-unused-variable \
                -Wno-missing-braces \
                -Wno-unused-but-set-variable \
                -DROCKS_USE_RAYLIB \
                -DCLAY_DESKTOP

# Library paths and flags
CMARK_LIB := $(CMARK_BUILD_DIR)/src/libcmark.a
LIBS := $(RAYLIB_LIBS) $(CMARK_LIB) -lm -ldl -lpthread

# Source files
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
ROCKS_FILES := $(shell find $(ROCKS_DIR)/src -maxdepth 1 -type f -name '*.c')
ROCKS_COMP_FILES := $(shell find $(ROCKS_DIR)/src/components -type f -name '*.c')
ROCKS_RENDERER_FILES := $(shell find $(ROCKS_DIR)/src/renderer -type f -name 'raylib_*.c')

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(SRC_FILES)) \
             $(patsubst $(ROCKS_DIR)/src/%.c,$(BUILD_DIR)/rocks/src/%.o,$(ROCKS_FILES)) \
             $(patsubst $(ROCKS_DIR)/src/components/%.c,$(BUILD_DIR)/rocks/src/components/%.o,$(ROCKS_COMP_FILES)) \
             $(patsubst $(ROCKS_DIR)/src/renderer/%.c,$(BUILD_DIR)/rocks/src/renderer/%.o,$(ROCKS_RENDERER_FILES))

# Main target
all: prepare $(CMARK_BUILD_DIR)/src/libcmark.a $(BUILD_DIR)/waozi copy_assets

# Prepare build directory
prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src
	@mkdir -p $(BUILD_DIR)/rocks/src/components
	@mkdir -p $(BUILD_DIR)/rocks/src/renderer
	@mkdir -p $(BUILD_DIR)/assets

# Build cmark static library
$(CMARK_BUILD_DIR)/src/libcmark.a:
	$(MKDIR) $(CMARK_BUILD_DIR)
	cd $(CMARK_DIR) && cmake -S . -B build -DCMARK_TESTS=OFF -DCMARK_SHARED=OFF
	cd $(CMARK_BUILD_DIR) && make

# Compilation rules
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c | $(CMARK_BUILD_DIR)/src/libcmark.a
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/rocks/src/%.o: $(ROCKS_DIR)/src/%.c | $(CMARK_BUILD_DIR)/src/libcmark.a
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/rocks/src/components/%.o: $(ROCKS_DIR)/src/components/%.c | $(CMARK_BUILD_DIR)/src/libcmark.a
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

$(BUILD_DIR)/rocks/src/renderer/%.o: $(ROCKS_DIR)/src/renderer/%.c | $(CMARK_BUILD_DIR)/src/libcmark.a
	@echo "Compiling $<..."
	@$(CC) -c $< -o $@ $(RAYLIB_FLAGS) $(INCLUDE_FLAGS) $(COMMON_FLAGS)

# Linking
$(BUILD_DIR)/waozi: $(OBJ_FILES)
	@echo "Linking..."
	@$(CC) $^ -o $@ $(RAYLIB_FLAGS) $(LIBS)

# Copy assets
copy_assets:
	@echo "Copying assets..."
	@if [ -d "assets" ]; then cp -r assets/* $(BUILD_DIR)/assets/; fi
	@if [ -d "content" ]; then cp -r content/* $(BUILD_DIR)/assets/; fi

# Clean
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)
	@rm -rf $(CMARK_BUILD_DIR)
	@echo "Clean completed successfully!"

.PHONY: all prepare clean copy_assets