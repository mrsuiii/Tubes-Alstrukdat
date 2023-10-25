CC=gcc

SRC_MAIN = main.c
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OUT_MAIN = $(SRC_MAIN:.c=)

BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/o


FUNCTION_COMPOSITION = $(call $1,$(call $2,$3))
RECURSIVE_WILDCARD=$(foreach f,$(wildcard $1$2),$(call $3,$f)) $(foreach d,$(wildcard $1*),$(call RECURSIVE_WILDCARD,$d/,$2,$3))

IGNORE_TEST = $(patsubst %test.c,,$1)
OBJ_FUN = $(OBJ_PATH)/$(patsubst %.c,%.o,$1) 
SRC_ALL = $(call RECURSIVE_WILDCARD,,*.c,IGNORE_TEST)
OBJ_ALL = $(foreach f,$(SRC_ALL),$(call OBJ_FUN,$f))
COMPILE_ALL = $(foreach f,$(SRC_ALL),$(call OBJ_FUN,$f) $f)

test:
	echo $(SRC_ALL)

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

