CC = gcc
CFLAGS = -Wall -std=c99

# Caminhos corretos da Raylib no SEU PC
RAYLIB_INCLUDE = C:/Users/walti/raylib/include
RAYLIB_LIB = C:/Users/walti/raylib/lib

INCLUDES = -I $(RAYLIB_INCLUDE)
LIB_DIRS = -L $(RAYLIB_LIB)

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/game.exe

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIB_DIRS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
