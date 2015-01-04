objs = odr.o main.o

a: $(objs)
	g++ -o a $(objs)

main.o: main.cpp
	g++ -c main.cpp

odr.o: odr.cpp
	g++ -c odr.cpp

.PHONY : clean
clean:
		-rm a $(objs) *.orig


