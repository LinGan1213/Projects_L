GS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = hw12
VAL = valgrind --tool=memcheck --leak-check=full --verbose

SRCS = hw12.c 
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS) calc.h
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(GCC) $< -c

test: all
	./$(EXEC) inputs/test1 
	./$(EXEC) inputs/test2 
	./$(EXEC) inputs/test3 
	./$(EXEC) inputs/test4 
	./$(EXEC) inputs/test5 

memory: all
	$(VAL) --log-file=log1 ./$(EXEC) inputs/test1 
	$(VAL) --log-file=log2 ./$(EXEC) inputs/test2
	$(VAL) --log-file=log3 ./$(EXEC) inputs/test3 
	$(VAL) --log-file=log4 ./$(EXEC) inputs/test4 
	$(VAL) --log-file=log5 ./$(EXEC) inputs/test5 

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f log?
