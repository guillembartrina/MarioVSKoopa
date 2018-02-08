CC = g++

INC = inc
SRC = src
BIN = bin

LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

CFLAGS = -std=c++11 -Wall -I$(INC)
LFLAGS = $(LIBS)

_DEPS =
DEPS  =$(patsubst %,$(INC)/%,$(_DEPS))

OBJ  = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(wildcard $(SRC)/*.cpp))

OUT  = main

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean

clean:
	rm -rf $(BIN)/*.o $(OUT)
