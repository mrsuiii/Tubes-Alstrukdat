#ifndef STRING_H
#define STRING_H

#include "ADT/boolean.h"

void string_copy(char* from, char* to, int max);
int string_compare(char* a, char* b);
int string_length(char* a);
boolean isAllBlank(char* a);

#endif