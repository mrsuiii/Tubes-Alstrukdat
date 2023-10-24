CC=gcc

SRC_MAIN = main.c
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OUT_MAIN = $(SRC_MAIN:.c=)

BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/o


RECURSIVE_WILDCARD=$(foreach f,$(wildcard $1$2),$(call $3,$f)) $(foreach d,$(wildcard $1*),$(call RECURSIVE_WILDCARD,$d/,$2,$3))
ITERATE_SRC = $(call RECURSIVE_WILDCARD,,*.c,$1)

ID = $1
SRC_ALL = $(call ITERATE_SRC,ID)
OBJ = $(OBJ_PATH)/$(patsubst %.c,%.o,$1) 
OBJ_ALL = $(call ITERATE_SRC,OBJ)

COMPILE = $(OBJ) $1
COMPILE_ALL = $(call ITERATE_SRC,COMPILE)

$(OBJ_PATH)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_PATH)/$(OUT_MAIN): $(OBJ_ALL)
	$(CC) $(CFLAGS) -o $@ $^

build: $(BIN_PATH)/$(OUT_MAIN)

run:
	./bin/main

clean:
	rm -rf $(BIN_PATH)

all: build run
force-all: cleanup all

