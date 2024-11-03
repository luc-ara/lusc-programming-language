CC := gcc
CFLAGS := -Iinclude
LDFLAGS := -lfl

SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INCLUDE_DIR := include
DATA_DIR := data
DOCS_DIR := docs
LIB_DIR := lib
TESTS_DIR := tests

FLEX_FILE := $(SRC_DIR)/scanner.l
FLEX_SRC := $(SRC_DIR)/scanner.yy.c
FLEX_OBJ := $(BUILD_DIR)/scanner.yy.o
FLEX_HEADER := $(INCLUDE_DIR)/scanner.yy.h
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(filter-out $(FLEX_SRC), $(wildcard $(SRC_DIR)/*.c)))

TARGET := $(BIN_DIR)/lusc

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(FLEX_OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(FLEX_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(FLEX_SRC) $(FLEX_HEADER): $(FLEX_FILE) | $(BUILD_DIR)
	flex -o $(FLEX_SRC) --header-file=$(FLEX_HEADER) $<

$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

run: all
	./bin/lusc

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(FLEX_SRC) $(FLEX_HEADER)

.PHONY: all clean run