CC = g++
CFLAGS = -pedantic -Wall -g -o
BFLAGS = -g -o
OBJS = main.o 	 \
	./src/differentiator.o \
	./src/fileHandler.o 	 \
	./src/logger.o
TARGET = ./target/diffApp.exe
REBUILDABLES = $(OBJS) $(TARGET)

all: $(TARGET)
	echo All done

# Rule for making program executable
$(TARGET): $(OBJS)
	$(CC) $(BFLAGS) $@ $^

# Rule to prepare .o files
%.o: %.cpp
	$(CC) $(CFLAGS) $@ -c $<
	

# Header dependencies
main.o: ./include/differentiator.h
differentiator.o: ./include/differentiator.h
fileHandler.o: ./include/fileHandler.h
logger.o: ./include/logger.h

.Phony:
	clean

clean:
	rm -f $(REBUILDABLES)