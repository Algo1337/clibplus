.PHONY: all

all:
	gcc main.c Libraries/*.c \
	Libraries/String/*.c \
	Libraries/Array/*.c \
	Libraries/Map/*.c \
	-g3 -ggdb