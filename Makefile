CC=gcc

MAIN = main.c
MAIN_OUT = $(BIN_PATH)/$(MAIN:.c=)

BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/o

RECUR_WILDCARD=$(foreach f,$(wildcard $1$2),$(call $3,$f)) $(foreach d,$(wildcard $1*),$(call RECUR_WILDCARD,$d/,$2,$3))

SRC_TO_OBJ = $(foreach f,$1,$(call OBJ_FUN,$f))

IGNORE_TEST = $(patsubst %test.c,,$1)
OBJ_FUN = $(OBJ_PATH)/$(patsubst %.c,%.o,$1) 
SRC_LIB = $(call RECUR_WILDCARD,,*.c,IGNORE_TEST)
OBJ_LIB = $(call SRC_TO_OBJ,$(SRC_LIB))

ID = $1
ADT = $(call RECUR_WILDCARD,lib/ADT,*.c,IGNORE_TEST)
OBJ_ADT = $(call SRC_TO_OBJ,$(ADT))

TEST_PATH = lib/ADT/test
TEST_BASE = $(TEST_PATH)/test.c
TEST_BIN = bin/test
OBJ_TEST_BASE = $(call SRC_TO_OBJ,$(TEST_BASE))

TEST = $(call RECUR_WILDCARD,lib/ADT,*_test.c,ID)
OBJ_TEST = $(foreach f,$(TEST),$(call OBJ_FUN,$f))

IS_EXIST = $(wildcard $1)
H_TO_C = $(patsubst %.h,%.c,$1)
H_TO_OBJ = $(OBJ_PATH)/$(patsubst %.h,%.o,$1)
FILTER_C_DEP = $(if $(findstring .h,$1),$(call IS_EXIST,$(call H_TO_C,$1)),)
GET_C_DEP = $(patsubst $1,,$(foreach f,$(shell $(CC) -MM $1),$(call FILTER_C_DEP,$f)))
RECUR_DEP = $(call GET_C_DEP,$1) $(foreach f,$(call GET_C_DEP,$1),$(call RECUR_DEP,$f))

.SECONDARY:
.PHONY: build run clean all recompile

test:
	echo $(call RECUR_DEP,lib/greet.c)

$(TEST_BIN)/% : $(OBJ_PATH)/$(TEST_PATH)/%_test.o $(OBJ_TEST_BASE) $(OBJ_ADT) 
	mkdir -p $(TEST_BIN)
	$(CC) $(CFLAGS) -o $(TEST_BIN)/$* $(OBJ_TEST_BASE) $(OBJ_ADT) $(OBJ_PATH)/$(TEST_PATH)/$*_test.o

$(OBJ_PATH)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OUT) :: $(OBJ_LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LIB)

%.test : $(TEST_BIN)/%
	$(TEST_BIN)/$*

build: $(MAIN_OUT)

run:
	$(MAIN_OUT)

clean:
	rm -rf $(BIN_PATH)

all: build run
recompile: clean all

