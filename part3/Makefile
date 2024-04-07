CC := gcc

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

EXECUTABLE := $(BIN_DIR)/tc

$(EXECUTABLE): $(OBJ_FILES)
	gcc -Wall $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p build
	gcc -Wall -c $^ -o $@

clean:
	@rm -rf $(BUILD_DIR) 
	@rm -f  $(EXECUTABLE)
	@echo "Cleaned project"

run: bin/tc
	./$(EXECUTABLE) $(source) $(flags)
