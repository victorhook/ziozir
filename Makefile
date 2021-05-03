CC=gcc
CFLAGS=-I src -g
DEPS = src/cpu.h
TARGET = cpu

SOURCE_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SOURCE_DIR)/*.c)
OBJ = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(DEPS) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<


run: $(TARGET)
	./$(TARGET)

# clean:
#rm $(OBJ)