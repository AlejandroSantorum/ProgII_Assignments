CC = gcc
CFLAGS = -Wall -g
EXE = a4_e2_test

all : $(EXE)

.PHONY : clean text
clean :
	rm -f *.o core $(EXE)

text :
	rm -f *.txt core $(EXE)

$(EXE) : % : %.o tree.o functions.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o -lm tree.o functions.o node.o
	
functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c $<

tree.o : tree.c tree.h
	$(CC) $(CFLAGS) -c $<
	
node.o : node.c node.h
	$(CC) $(CFLAGS) -c $<
