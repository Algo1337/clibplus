.PHONY: all

all: install cp build do_test

install:
	sudo apt update -y && apt upgrade -y
	sudo apt install gcc -y
	sudo apt install build-essential

cp:
	rm -rf Libraries/*.c
	rm -rf Libraries/String/*.c
	rm -rf Libraries/Array/*.c
	rm -rf Libraries/Map/*.c
	rm -rf Libraries/Net/*.c
	rm -rf Libraries/OS/*.c
	mkdir -p /usr/local/include/clib
	cp -rf Libraries/* /usr/local/include/clib
	rm -r Libraries

build:
	cd Libraries; \
	gcc -c c_types.c *.c \
	String/*.c \
	Array/*.c \
	Map/*.c \
	Net/*.c \
	OS/*.c \
	-lssl -lcrypto -g3 -ggdb; \
	ar rcs clib+.a *.o; rm *.o; mv clib+.a /usr/local/lib/libclib+.a
	echo -ne '\x1b[32m[ + ]\x1b[0m Compile your program using -lclib+ argument\n'

do_test:
	gcc test/str.c -lclib+; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/str.c] Successfully Compiled and Run Text Completed\n'
	gcc test/arr.c -lclib+; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/arr.c] Successfully Compiled and Run Text Completed\n'
	gcc test/dim_array.c -lclib+; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/dim_array.c] Successfully Compiled and Run Text Completed\n'
	gcc test/map.c -lclib+; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/map.c] Successfully Compiled and Run Text Completed\n'
	gcc test/map_json.c -lclib+; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/map_json.c] Successfully Compiled and Run Text Completed\n'
	gcc test/http.c -lclib+ -lssl -lcrypto; ./a.out
	echo -ne '\x1b[32m[ + ]\x1b[0m [test/http.c] Successfully Compiled and Run Text Completed\n'
