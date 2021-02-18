FLEX_CC = flex
CC = gcc

OBJS_L = gpp_lexer.l
OUTPUT_L = gpp_lexer.c


OBJS_C = $(OUTPUT_L)
OUTPUT_C = gpp_lexer.out

all :
	$(FLEX_CC) -o $(OUTPUT_L) $(OBJS_L)
	$(CC) -o $(OUTPUT_C) $(OBJS_C)
#	./$(OUTPUT)

