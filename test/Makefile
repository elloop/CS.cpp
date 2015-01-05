objs = main.o 

a.out: $(objs)
	g++ -o a.out $(objs)

main.o: main.cpp
	g++ -c main.cpp

.PHONY : clean
clean:
		-rm a.out $(objs) *.orig
