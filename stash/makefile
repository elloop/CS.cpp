LINK_TARGET = main.exe
CC = g++
ALGORITHM_INCLUDE_PATH = "../" 
CC_FLAGS = -I$(ALGORITHM_INCLUDE_PATH)

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
%.o : %.cpp
	$(CC) $(CC_FLAGS) -g -o $@ -c $<





