CC = gcc
CFLAGS = -Wall -std=c99

# Includes
INCLUDE_DIR = include
RAYLIB_INCLUDE = C:/Users/walti/raylib/include
INCLUDES = -I$(INCLUDE_DIR) -I$(RAYLIB_INCLUDE)

# Bibliotecas
LIB_DIRS = -L C:/Users/walti/raylib/lib
LIBS = -lraylib -lgdi32 -lwinmm

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/game.exe

all: $(TARGET)

# cria pastas (jeito que funciona no mingw/msys)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# compila .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# linka
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIB_DIRS) $(LIBS)

run: $(TARGET)
	$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
