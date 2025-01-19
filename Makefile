CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = num_wordle
SRC = Num_Wordle.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
