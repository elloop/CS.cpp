TARGET = main

OBJS = main.o \
	   myls.o \
	   inc.o

REBUILDABLE = $(TARGET) $(OBJS)

COMPILER = gcc

LOCAL_C_FLAGS = -std=c11 \
				  #-DNDEBUG

INCLUDE_DIRS = -I.

LDDIR = -L./lib/

LDLIBS = ./lib/libapue.a $(EXTRALIBS)

#vpath %.cpp ../:../stash:../stack:../build

myls : myls.o inc.o
	$(COMPILER) -g -o $@ $^ $(LDDIR) $(LDLIBS)

all : $(OBJS)
	$(COMPILER) -g -o $(TARGET) $^ $(LDLIBS)
	echo "all done."

%.o : %.c
	$(COMPILER) $(LOCAL_C_FLAGS) $(INCLUDE_DIRS) -g -o $@ -c $<

.PHONY : clean
clean:
		-rm $(REBUILDABLE)
		echo "all cleaned!"

