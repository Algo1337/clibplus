.PHONY: install build cp

install:
	sudo apt update -y && apt upgrade -y

cp:
	rm -rf Libraries/*.c
	rm -rf Libraries/String/*.c
	rm -rf Libraries/Array/*.c
	rm -rf Libraries/Map/*.c
	mkdir -p /usr/local/include/C_TYPES
	cp -rf Libraries/* /usr/local/include/C_TYPES

build:
	cd Libraries; \
	gcc -c c_types.c *.c \
	String/*.c \
	Array/*.c \
	Map/*.c \
	-g3 -ggdb; \
	ar rcs ctypes.a *.o; rm *.o; mv ctypes.a /usr/local/lib/libctypes.a
	echo -ne '\x1b[32m[ + ]\x1b[0m Compile your program using -lctypes argument\n'
