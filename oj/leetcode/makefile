
TARGET = main

OBJS = two_sum.o

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = g++

LOCAL_CPP_FLAGS = -std=c++11
				  #-DNDEBUG

INCLUDE_DIRS = -I../../ \
	       -I../../common

#vpath %.cpp ../:../stash:../stack:../build

all : $(OBJS)
	$(COMPILER) -g -o $(TARGET) $^
	echo "all done."

%.o : %.cpp
	$(COMPILER) $(LOCAL_CPP_FLAGS) $(INCLUDE_DIRS) -g -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
		echo "all cleaned!"
