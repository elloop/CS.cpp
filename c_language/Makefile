OBJS = test_printf.o \
	   main.o

TARGET = main.exe
INCLUDES = -I./

vpath %.c ./grammar

all : $(OBJS)
	$(CC) -o $(TARGET) $^

%.o : %.c
	$(CC) $(INCLUDES) -c $(OUTPUT_OPTION) $<

.PHONY : clean
clean:
	-rm $(OBJS) $(TARGET)



