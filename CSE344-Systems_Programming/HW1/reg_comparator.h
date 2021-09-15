#ifndef REG_COMPARATOR_H
#define REG_COMPARATOR_H

#include <stdio.h>

// case insensitive
// supporting the following regular expression: +
// str1 regex expression
// str2 text
// returns 1, if comparison is success otherwise 0.
int str_eq_reg(char* str1, char* str2);

#endif
