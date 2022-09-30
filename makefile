CC 		= g++
CFLAGS 	= -pedantic -Wall -c -std=c++17 -o
LFLAGS 	= -g -o

OBJS = main.o 	 		   \
	./src/differentiator.o \
	./src/fileHandler.o    \
	./src/logger.o		   \
	./src/functions.o

BUILDED = ./build/main.o 	   \
	 ./build/differentiator.o  \
	 ./build/fileHandler.o 	   \
	 ./build/logger.o          \
	 ./build/colorProperties.o \
	 ./build/functions.o

BLUE_COLOR = "\033[0;34m"
DEFAULT_COLOR = "\033[0m"

BUILD_DIR 		= ./build/
TARGET_DIR 		= ./target/
TARGET 			= $(TARGET_DIR)diffApp
REBUILDABLES 	= $(BUILDED) $(TARGET)

all: create_directories compile 

install: copy_to_bin
	@echo  $(BLUE_COLOR) ' - Installed successfully' $(DEFAULT_COLOR)

compile: $(TARGET) move_files

# Rule for making executable program 
$(TARGET): $(OBJS)	
	@echo $(BLUE_COLOR) ' - Compilation is finished' $(DEFAULT_COLOR)
	$(CC) $^ $(LFLAGS) $@
	@echo $(BLUE_COLOR) ' - Linking is finished' $(DEFAULT_COLOR)

# Rule to prepare .o files
%.o: %.cpp
	$(CC) $(CFLAGS) $@ $<

# Header dependencies
main.o: 			./include/functions.h
differentiator.o: 	./include/differentiator.h ./include/colorProperties.h
fileHandler.o: 		./include/fileHandler.h
logger.o: 			./include/logger.h .include/colorProperties.h
functions.o:		./include/functions.h ./include/differentiator.h

.Phony:
	clean
	copy_files
	create_directories
	copy_to_bin
	uninstall

move_files:
	cp ./*.o $(BUILD_DIR)
	cp ./src/*.o $(BUILD_DIR)
	rm -f ./*.o
	rm -f ./src/*.o
	@echo $(BLUE_COLOR) ' - Builded files are moved to build directory' $(DEFAULT_COLOR)

create_directories:
	mkdir $(BUILD_DIR)
	mkdir $(TARGET_DIR)
	@echo $(BLUE_COLOR) ' - Created directories' $(DEFAULT_COLOR)

clean:
	rm -f $(REBUILDABLES)
	@echo $(BLUE_COLOR) ' - Clean compleated' $(DEFAULT_COLOR)

copy_to_bin: 
	cp $(TARGET) /usr/local/bin/diffApp

uninstall:
	rm -f /usr/local/bin/diffApp
