objs = odr.o main.o small_test_set.o

a.out: $(objs)
	g++ -o a.out $(objs)

cppflags = -std=c++11

main.o: main.cpp
	g++ -c $(cppflags) main.cpp

odr.o: odr.cpp
	g++ -c $(cppflags) odr.cpp

small_test_set.o : small_test_set.cpp

# .phony defines a fake-target. no matter file named `clean` or not, clean will always be a fake-target.
.PHONY : clean
clean:
	# `-` precede rm means ignore error, and execute until end.
		-rm a.out $(objs) *.orig


