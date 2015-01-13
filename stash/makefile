LINK_TARGET = main.exe
CC = g++
ALGORITHM_INCLUDE_PATH = "../" 
CPP_INCLUDE_DIRS = -I"../" 
CC_FLAGS = -std=c++11 \
		   #$(CPP_INCLUDE_DIRS)

# todo: check why vpath is invalid
#VPATH = ../common
#vpath %.h ../common:../:./:d:/md/algorithm;

#VPATH = ../common:../
VPATH = ../
#vpath %.h "../common"

OBJS = \
 stash.o \
 main.o 

REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean:
	rm -f $(REBUILDABLES)
	echo clean done!

all: $(LINK_TARGET)
	echo all done!

# link .o to .exe
# equals to following codes:
# main.exe : main.o stash.o
# 	$(CC) -g -o main.exe main.o stash.o
$(LINK_TARGET) : $(OBJS)
	$(CC) -g -o $@ $^


VPATH = ../common
# build all .cpp to .o
# equal to following codes:
#stash.o : stash.cpp
#	$(CC) $(CC_FLAGS) -g -o $@ -c $<

#main.o : main.cpp
#	$(CC) $(CC_FLAGS) -g -o $@ -c $<
#
#	and equals to:
#	stash.o : stash.cpp
#		$(CC) $(CC_FLAGS) -g -o stash.o -c stash.cpp
#
#	main.o : main.cpp
#		$(CC) $(CC_FLAGS) -g -o main.o -c mian.cpp
#%.o : %.cpp
	#$(CC) $(CC_FLAGS) -g -o $@ -c $<

stash.o : stash.cpp print_util.h
	$(CC) $(CC_FLAGS) -g -o $@ -c $<

main.o : main.cpp print_util.h
	$(CC) $(CC_FLAGS) -g -o $@ -c $<


#main.o: stash.h
#stash.o: stash.h




