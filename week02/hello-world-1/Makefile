CC     =  gcc
CFLAGS = -g3 -W -Wall -std=c99 -ggdb
TARGET = hello_world
SRC    =  $(TARGET).c
OBJ    =  $(TARGET).o

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
