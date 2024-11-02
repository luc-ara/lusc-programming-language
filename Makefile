CC = gcc
CFLAGS = -Iinclude

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
INCLUDE_DIR = include
DATA_DIR = data
DOCS_DIR = docs
LIB_DIR = lib
TESTS_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TARGET = $(BIN_DIR)/lusc

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

run:
	./bin/lusc

.PHONY: all clean