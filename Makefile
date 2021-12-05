TARGET = chip8 
CC = gcc
CFLAGS = -Wall
SRC := $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
INC := $(wildcard include/*.h) 

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ `pkg-config --cflags --libs sdl2`
	clear

src/%.o: %.c $(INC)
	$(CC) -c -Wall $<

run: 
	./$(TARGET)

clean:
	rm $(TARGET) $(OBJ)
	clear
