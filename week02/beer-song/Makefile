CC     =  gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb #-save-temps
TARGET = beer-process
SRC    =  $(TARGET).c
OBJ    =  $(TARGET).o

.PHONY: clean

$(TARGET): $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)  *.o *.i *.s
