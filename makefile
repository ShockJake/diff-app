CC 		= g++
CFLAGS 	= -pedantic -Wall -c -o
LFLAGS 	= -g -o

OBJS = main.o 	 		   \
	./src/differentiator.o \
	./src/fileHandler.o    \
	./src/logger.o

BUILDED = ./build/main.o 	  \
	 ./build/differentiator.o \
	 ./build/fileHandler.o 	  \
	 ./build/logger.o

BUILD_DIR 		= ./build/
TARGET_DIR 		= ./target/
TARGET 			= $(TARGET_DIR)diffApp.exe
REBUILDABLES 	= $(BUILDED) $(TARGET)

all: compile

install: create_directories compile

compile: $(TARGET) move_files

# Rule for making executable program 
$(TARGET): $(OBJS)
	$(CC) $^ $(LFLAGS) $@

# Rule to prepare .o files
%.o: %.cpp
	$(CC) $(CFLAGS) $@ $<

# Header dependencies
main.o: 			./include/differentiator.h
differentiator.o: 	./include/differentiator.h
fileHandler.o: 		./include/fileHandler.h
logger.o: 			./include/logger.h

.Phony:
	clean
	copy_files
	create_directories

move_files:
	cp ./*.o $(BUILD_DIR)
	cp ./src/*.o $(BUILD_DIR)
	rm -f ./*.o
	rm -f ./src/*.o

create_directories:
	mkdir $(BUILD_DIR)
	mkdir $(TARGET_DIR)

clean:
	rm -f $(REBUILDABLES)