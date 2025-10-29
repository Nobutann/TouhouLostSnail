CC = gcc
CFLAGS = -Wall -std=c99

# Includes
INCLUDE_DIR = include
RAYLIB_INCLUDE = C:/raylib/raylib/src
INCLUDES = -I $(INCLUDE_DIR) -I $(RAYLIB_INCLUDE)

# Bibliotecas
LIB_DIRS = -L C:/raylib/raylib/src
LIBS = -lraylib -lgdi32 -lwinmm

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/game.exe

# Compilar tudo
all: $(TARGET)

# Criar diretórios antes de compilar
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilar cada .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linkar executável
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIB_DIRS) $(LIBS)

# Rodar o executável
run: $(TARGET)
	./$(TARGET)

# Limpar build
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
