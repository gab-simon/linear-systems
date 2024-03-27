TARGET=perfSL
CC=gcc
DEBUG= -g -O0
WARN= -Wall
CCFLAGS=$(DEBUG) $(WARN)
LD=gcc
OBJS= perfSL.o systems.o utils.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CCFLAGS) -lm
	@rm *.o

perfSL.o: perfSL.c
	$(CC) -c $(CCFLAGS) perfSL.c -o perfSL.o

systems.o: systems.c
	$(CC) -c $(CCFLAGS) systems.c -o systems.o

utils.o: utils.c
	$(CC) -c $(CCFLAGS) utils.c -o utils.o

run: all
	./perfSL