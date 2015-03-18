
TARGET = main

OBJS = test.o \
	   compatibility.o \
	   constructor_test.o \
		 pod_test.o
		 # thread_test.o \

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = g++

LOCAL_CPP_FLAGS = -std=c++11 \
				  #-DNDEBUG


LINK_FLAGS = #-lpthread 

# -g3 -gdwarf-2 is for gdb to expand and print macro value.
FOR_GDB_DEBUG = -g3 \
				-gdwarf-2



INCLUDE_DIRS = -I..

#vpath %.cpp ../:../stash:../stack:../build

all : $(OBJS)
	$(COMPILER) -g -o  $(TARGET) $^ $(LINK_FLAGS)
	echo "all done."

%.o : %.cpp
	$(COMPILER) $(LOCAL_CPP_FLAGS) $(INCLUDE_DIRS) $(FOR_GDB_DEBUG) -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
		echo "all cleaned!"
