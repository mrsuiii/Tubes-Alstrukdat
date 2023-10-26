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
GET_TEST_PATH = $(TEST_PATH)/$1_test.c

IS_EXIST = $(wildcard $1)
H_TO_C = $(patsubst %.h,%.c,$1)
H_TO_OBJ = $(OBJ_PATH)/$(patsubst %.h,%.o,$1)
FILTER_C_DEP = $(if $(findstring .h,$1),$(call IS_EXIST,$(call H_TO_C,$1)),)
GET_C_DEP = $(patsubst $1,,$(foreach f,$(shell $(CC) -MM $1),$(call FILTER_C_DEP,$f)))
RECUR_DEP = $(call GET_C_DEP,$1) $(foreach f,$(call GET_C_DEP,$1),$(call RECUR_DEP,$f))
RECUR_DEP_OBJ = $(call SRC_TO_OBJ,$(call RECUR_DEP,$1) $1)

FILTER_RECUR_DEP = $(if $(findstring $1,$2),,$1)
RECUR_DEP_N = $(call RECUR_DEP_N1,$1,$(call GET_C_DEP,$1))
RECUR_DEP_N1 = $(call RECUR_DEP_N2,$1,$(foreach f,$2,$(call FILTER_RECUR_DEP,$f,$1)))
RECUR_DEP_N2 = $1 $(foreach f,$2,$(call RECUR_DEP_N,$1 $2,$f))

RECUR_DEP_F = $(call SRC_TO_OBJ,$(call RECUR_DEP_M,,$1))
RECUR_DEP_M = $2 $(call RECUR_DEP_M1,$2 $1,$(call GET_C_DEP,$2))
RECUR_DEP_M1 = $(call RECUR_DEP_M2,$1,$(foreach f,$2,$(if $(findstring $f,$1),,$f)))
RECUR_DEP_M2 = $(foreach f,$2,$(call RECUR_DEP_M,$1 $2,$f))

.SECONDARY:
.SECONDEXPANSION:
.PHONY: build run clean all recompile

$(TEST_BIN)/% : $$(call RECUR_DEP_OBJ,$$(call GET_TEST_PATH,$$*))
	mkdir -p $(TEST_BIN)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_PATH)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OUT) : $(call RECUR_DEP_F,$(MAIN))
	$(CC) $(CFLAGS) -o $@ $^

%.test : $(TEST_BIN)/%
	$(TEST_BIN)/$*

build: $(MAIN_OUT)

run:
	$(MAIN_OUT)

clean:
	rm -rf $(BIN_PATH)

all: build run
recompile: clean all