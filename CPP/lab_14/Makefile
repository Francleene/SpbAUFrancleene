CC  = g++
EXE = main

SRC_DIR = src
OBJ_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS = -Iinclude
CFLAGS   = -Wall -Werror -Wextra

.PHONY: all clean

all: make_dir $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

make_dir:
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR) $(EXE)
