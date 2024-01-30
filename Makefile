CFLAGS= -g -Wall -Wvla -fsanitize=address
all:
	make allobj
	make ls
	make tree
	make find
ls: sort.c ls.c
	gcc $(CFLAGS) ls.o sort.o -o ls


find: find.c
	gcc $(CFLAGS) find.o grepcpy.o -o find

tree: tree.c
	gcc $(CFLAGS) tree.o -o tree

cleanobj:
	rm *.o

allobj:
	gcc sort.c -c
	gcc find.c -c
	gcc tree.c -c
	gcc grepcpy.c -c 
	gcc ls.c -c

clean:
	rm find
	rm tree
	rm ls
