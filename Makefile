CC=gcc

SRC_MAIN = main.c
OBJ_MAIN = $(SRC_MAIN:.c=.o)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SRC_ALL := $(call rwildcard,./,*.c)

all: cleanup build run

build:
	mkdir bin
	gcc $(SRC_ALL) -o bin/main

run:
	echo "\033c"
	./bin/main

cleanup:
	rm -rf bin