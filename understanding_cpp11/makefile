
TARGET = main

OBJS = test.o \
	   compatibility.o

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = g++

LOCAL_CPP_FLAGS = -std=c++11 \
				  #-DNDEBUG

FOR_GDB_DEBUG = -g3 \
				-gdwarf-2



INCLUDE_DIRS = -I..

#vpath %.cpp ../:../stash:../stack:../build

all : $(OBJS)
	$(COMPILER) -g -o $(TARGET) $^
	echo "all done."

%.o : %.cpp
	$(COMPILER) $(LOCAL_CPP_FLAGS) $(INCLUDE_DIRS) $(FOR_GDB_DEBUG) -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
		echo "all cleaned!"
