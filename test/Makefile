objs = test.o compare_signed.o main.o

a : $(objs)
	g++ -o a $(objs)

test.o : test.cpp
compare_signed.o : compare_signed.cpp
main.o: main.cpp

.PHONY : clean
clean : 
			-rm a $(objs) *.orig
