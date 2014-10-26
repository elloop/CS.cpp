objs = avl_tree.o avl_test.o

avl_test:$(objs)
	gcc -o avl_test $(objs)

avl_tree.o : avl_tree.c
avl_test.o : avl_test.c

.PHONY : clean
clean :
	-rm avl_test $(objs)
