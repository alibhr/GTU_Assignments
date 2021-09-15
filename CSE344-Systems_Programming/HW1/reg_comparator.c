#include "reg_comparator.h"

int insensitive_cmp(char c1, char c2);
char to_lower(char c);

int str_eq_reg(char* str1, char* str2){

	int repeat = 0;

	if(*str1 == '+') return 0;

	while(*str1 != '\0' && *str2 != '\0'){

		if(*str1 == '\\') ++str1;

		else if(*str1 == '+'){
			repeat = 0;
			while(insensitive_cmp(*(str1-1), *str2) && *str2 != '\0'){
				++str2;
				++repeat;
			}
			++str1;

			if(*str1 == '+') return 0;

			if(*str1 == '\\') ++str1;

			char ref = *(str1-2);
			while(ref == *str1 && repeat > 0){
				--repeat;
				++str1;
				if (*str1 == '+'){
					++str1;
					if (*str1 == '+') return 0;
				}
				if(*str1 == '\\') ++str1; 
			} 

		}

		if(!insensitive_cmp(*str1, *str2)) return 0;

		if(*str1 == '\0' || *str2 == '\0') return !(*str1 - *str2);

		++str1;
		++str2;
	}

	if(*str1 == '+') ++str1;
	return !(*str1 - *str2);
}

int insensitive_cmp(char c1, char c2){
	return to_lower(c1) == to_lower(c2);
}

char to_lower(char c){

	if(c>='A' && c<='Z')
		return c+32;

	return c;
}
