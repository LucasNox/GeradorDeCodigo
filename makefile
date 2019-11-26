CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra -O3 -g

BIN		:= ./
SRC		:= ./

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= gerador.exe
else
EXECUTABLE	:= gerador
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	rm $(BIN)/$(EXECUTABLE)

run: remake
	./$(BIN)/$(EXECUTABLE) < $(FILEIN)

vrun: remake
	valgrind --leak-check=full ./$(BIN)/$(EXECUTABLE) < $(FILEIN)

.PHONY: remake
remake:
	rm -f $(BIN)/$(EXECUTABLE)
	$(CC) $(C_FLAGS) $(wildcard *.cpp) $(wildcard *.hpp) -o $(EXECUTABLE) $(LIBRARIES)
	
$(BIN)/$(EXECUTABLE):
	$(CC) $(C_FLAGS) $(wildcard *.cpp) $(wildcard *.hpp) -o $@ $(LIBRARIES)