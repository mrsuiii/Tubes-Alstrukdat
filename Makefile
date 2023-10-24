CC=gcc

SRC_MAIN = main.c
OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ_PATH = bin/o

RECURSIVE_WILDCARD=$(foreach f,$(wildcard $1$2),$(call $3,$f)) $(foreach d,$(wildcard $1*),$(call RECURSIVE_WILDCARD,$d/,$2,$3))
ITERATE_SRC = $(call RECURSIVE_WILDCARD,./,*.c,$1)

ID = $1
SRC_ALL := $(call ITERATE_SRC,ID)


COMPILE = $(patsubst %.c,%.o,$1) $1
COMPILE_ALL = $(call ITERATE_SRC,COMPILE)

test: $(COMPILE_ALL)

all: 
	cleanup build run

%.o: %.c
	mkdir -p $(OBJ_PATH)/$(@D)
	$(CC) $(CFLAGS) -c -o $(OBJ_PATH)/$@ $<

compile: $(COMPILE_ALL)

run:
	echo "\033c"
	./bin/main

cleanup:
	rm -rf bin