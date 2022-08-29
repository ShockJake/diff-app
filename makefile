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

all: create_directories compile 

install: copy_to_bin
	@echo ' - Installed successfully'

compile: $(TARGET) move_files

# Rule for making executable program 
$(TARGET): $(OBJS)	
	@echo ' - Compilation is finished'
	$(CC) $^ $(LFLAGS) $@
	@echo ' - Linking is finished'

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
	copy_to_bin
	uninstall

move_files:
	cp ./*.o $(BUILD_DIR)
	cp ./src/*.o $(BUILD_DIR)
	rm -f ./*.o
	rm -f ./src/*.o
	@echo ' - Builded files are moved to build directory'

create_directories:
	mkdir $(BUILD_DIR)
	mkdir $(TARGET_DIR)
	@echo ' - Created directories'

clean:
	rm -f $(REBUILDABLES)
	@echo ' - Clean compleated'

copy_to_bin: 
	cp $(TARGET) /usr/local/bin/diffApp

uninstall:
	rm -f /usr/local/bin/diffApp
