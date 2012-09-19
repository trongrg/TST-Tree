CC=gcc
CFLAGS=-ansi -Wall -pedantic -g

APP1=main-tree
APP2=main-list

.PHONY: all

all: $(APP1) $(APP2)

$(APP1): tstnode.o wordset_tree.o main_tree.o
	$(CC) $(CFLAGS) tstnode.o wordset.o main.o -o $(APP1)

wordset_tree.o: wordset.c
	$(CC) $(CFLAGS) -c -DTYPE=\"tstnode.h\" wordset.c

main_tree.o: main.c
	$(CC) $(CFLAGS) -c -DTYPE=\"tstnode.h\" main.c

$(APP2): llnode.o wordset_list.o main_list.o
	$(CC) $(CFLAGS) llnode.o wordset.o main.o -o $(APP2)

wordset_list.o: wordset.c
	$(CC) $(CFLAGS) -c -DTYPE=\"llnode.h\" wordset.c

main_list.o: main.c
	$(CC) $(CFLAGS) -c -DTYPE=\"llnode.h\" main.c

.PHONY: clean
clean: 
	$(RM) *.o *.swp *~ a.out core $(APP1) $(APP2)

