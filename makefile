CC = g++
CFLAGS = -pedantic -Wall -g -o
BFLAGS = -g -o

OBJS = main.o 	 		   \
	./src/differentiator.o \
	./src/fileHandler.o    \
	./src/logger.o

BUILDED = ./build/main.o 	  \
	 ./build/differentiator.o \
	 ./build/fileHandler.o 	  \
	 ./build/logger.o

TARGET = ./target/diffApp.exe
BUILD_DIR = ./build
REBUILDABLES = $(BUILDED) $(TARGET)

all: $(TARGET)
	cp ./*.o ./build
	cp ./src/*.o ./build
	rm -f ./*.o
	rm -f ./src/*.o

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