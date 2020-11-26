INCLUDES = \
		-I include/

SOURCES = \
		src/*.c

FILENAME = MAIN

LINUX_DEFINES = \
			_POSIX
WINDOWS_DEFINES = \
			_WIN32

linux:
	clear
	gcc -o $(FILENAME) $(SOURCES) $(INCLUDES) -D $(LINUX_DEFINES)

windows:
	clear
	gcc -o $(FILENAME) $(SOURCES) $(INCLUDES) -D $(WINDOWS_DEFINES)

dependencies:

clean:
	clear
	rm $(FILENAME)

run:
	clear
	./$(FILENAME)