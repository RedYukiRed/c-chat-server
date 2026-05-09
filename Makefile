# ==========[ Compiler Settings ]==========
CC = gcc
CFAGS = -Wall -Wextra -g
BUILD_DIR = build

# ==========[ Source Files ]==========
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRC))

# ==========[ Target Executable ]==========
TARGET = $(BUILD_DIR)/Chat

# ==========[ Rules]==========
$(shell mkdir -p $(BUILD_DIR))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	@echo "✅ Build complete → $(TARGET)"

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

