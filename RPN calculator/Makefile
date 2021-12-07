GS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = hw13
VAL = valgrind --tool=memcheck --leak-check=full --verbose

SRCS = hw13.c expressionTree.c scanner.c tree.c  
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS) expressionTree.h scanner.h tree.h
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(GCC) $< -c

test: all
	./$(EXEC) inputs/test1 output1
	diff output1 expected1 
	./$(EXEC) inputs/test2 output2
	diff output2 expected2
	./$(EXEC) inputs/test3 output3
	diff output3 expected3
	./$(EXEC) inputs/test4 output4
	diff output4 expected4

memory: all
	$(VAL) --log-file=log1 ./$(EXEC) inputs/test1 output1
	$(VAL) --log-file=log2 ./$(EXEC) inputs/test2 output2
	$(VAL) --log-file=log3 ./$(EXEC) inputs/test3 output3
	$(VAL) --log-file=log4 ./$(EXEC) inputs/test4 output4

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f output?
	rm -f log?
