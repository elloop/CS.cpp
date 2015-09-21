TARGET = main

OBJS = stash.o \
	   main.o \

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = g++

LOCAL_CPP_FLAGS = -std=c++11 \
				  -DNDEBUG

# searching print_util.h and inc.h for stash.cpp
INCLUDE_DIRS = -I..

# ./stash to find stash.cpp
#VPATH = ./stash
#or 
vpath %.cpp ../:../stash:../stack:../build

all : $(OBJS)
	$(COMPILER) -o $(TARGET) $^

%.o : %.cpp
	$(COMPILER) $(LOCAL_CPP_FLAGS) $(INCLUDE_DIRS) -g -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
