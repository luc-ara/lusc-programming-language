CC := gcc
CFLAGS := -Iinclude 
LDFLAGS := -lfl

SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INC_DIR := include
TESTS_DIR := tests

FLEX_FILE := $(SRC_DIR)/lexer.l
FLEX_SRC := $(SRC_DIR)/lexer.yy.c
FLEX_OBJ := $(BUILD_DIR)/lexer.yy.o
FLEX_HEADER := $(INC_DIR)/lexer.yy.h

BISON_FILE := $(SRC_DIR)/parser.y
BISON_SRC := $(SRC_DIR)/parser.tab.c
BISON_OBJ := $(BUILD_DIR)/parser.tab.o
BISON_HEADER := $(INC_DIR)/parser.tab.h

SRC_FILES := $(sort $(wildcard $(SRC_DIR)/*.c) $(FLEX_SRC) $(BISON_SRC))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TARGET := $(BIN_DIR)/lusc

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lusc.o: $(SRC_DIR)/lusc.c $(FLEX_HEADER) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(FLEX_SRC) $(FLEX_HEADER): $(FLEX_FILE) $(BISON_HEADER)
	flex --outfile=$(FLEX_SRC) --header-file=$(FLEX_HEADER) $<

$(BISON_SRC) $(BISON_HEADER): $(BISON_FILE)
	bison --output=$(BISON_SRC) --header=$(BISON_HEADER) $<

$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

test: all
	$(TARGET) $(TESTS_DIR)/input.txt $(TESTS_DIR)/output.txt

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(FLEX_SRC) $(FLEX_HEADER) $(BISON_SRC) $(BISON_HEADER)

reset:
	make clean
	clear
	make

.PHONY: all clean test reset inspect