OBJS_l = lines.l

OBJS_c = lex.yy.c

OUTPUT = a.out

FLEX_CC = flex

CC = gcc

all :
	$(FLEX_CC) $(OBJS_l)
	$(CC) $(OBJS_c)
	./$(OUTPUT)

