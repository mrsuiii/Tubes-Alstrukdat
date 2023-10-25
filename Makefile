CC=gcc

MAIN = main.c
MAIN_OUT = $(BIN_PATH)/$(MAIN:.c=)

BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/o

RECURSIVE_WILDCARD=$(foreach f,$(wildcard $1$2),$(call $3,$f)) $(foreach d,$(wildcard $1*),$(call RECURSIVE_WILDCARD,$d/,$2,$3))

SRC_TO_OBJ = $(foreach f,$1,$(call OBJ_FUN,$f))

IGNORE_TEST = $(patsubst %test.c,,$1)
OBJ_FUN = $(OBJ_PATH)/$(patsubst %.c,%.o,$1) 
SRC_LIB = $(call RECURSIVE_WILDCARD,,*.c,IGNORE_TEST)
OBJ_LIB = $(call SRC_TO_OBJ,$(SRC_LIB))

ID = $1
ADT = $(call RECURSIVE_WILDCARD,lib/ADT,*.c,IGNORE_TEST)
OBJ_ADT = $(call SRC_TO_OBJ,$(ADT))

TEST_PATH = lib/adt/test
TEST_BASE = $(TEST_PATH)/test.c
OBJ_TEST_BASE = $(call SRC_TO_OBJ,$(TEST_BASE))

TEST = $(call RECURSIVE_WILDCARD,lib/ADT,*_test.c,ID)
OBJ_TEST = $(foreach f,$(TEST),$(call OBJ_FUN,$f))

$(OBJ_PATH)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OUT): $(OBJ_LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LIB)

build: $(MAIN_OUT)

run:
	./bin/main

clean:
	rm -rf $(BIN_PATH)

all: build run
force-all: cleanup all

