CC     =  gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb #-save-temps
TARGET = hello_world
SRC    =  $(TARGET).c
OBJ    =  $(TARGET).o

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
