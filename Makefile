CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lreadline

SRC := $(shell find . -type f -name "*.c")
OBJ := $(SRC:.c=.o)

TARGET = shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
