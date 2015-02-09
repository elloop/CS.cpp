
TARGET = main

OBJS = stack_test.o

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = g++

LOCAL_CPP_FLAGS = -std=c++11 \
				  -DNDEBUG

INCLUDE_DIRS = -I..

vpath %.cpp ../

all : $(OBJS)
	$(COMPILER) -o $(TARGET) $^

%.o : %.cpp
	$(COMPILER) $(LOCAL_CPP_FLAGS) $(INCLUDE_DIRS) -g -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
