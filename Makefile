.PHONY: install cp

install:
	sudo apt update -y && apt upgrade -y
	echo 'alias c_types_path="echo /usr/local/include/C_TYPES/*.c /usr/local/include/C_TYPES/Array/*.c /usr/local/include/C_TYPES/String/*.c /usr/local/include/C_TYPES/Map/*.c"' >> ~/.bashrc
	bash

cp:
	mkdir -p /usr/local/include/C_TYPES
	cp -rf Libraries/* /usr/local/include/C_TYPES
	echo -ne '\x1b[32m[ + ]\x1b[0m Compile your program using $$(c_types_path) argument\n'

build:
	gcc main.c Libraries/*.c \
	Libraries/String/*.c \
	Libraries/Array/*.c \
	Libraries/Map/*.c \
	-g3 -ggdb