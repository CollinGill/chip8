TARGET = out
CC = gcc
SRC := $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INC := $(wildcard include/*.h) 

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^
	clear

%.o: %.c $(INC)
	$(CC) -c -Wall $<

run: 
	./$(TARGET)

clean:
	rm $(TARGET) $(OBJ)
	clear
