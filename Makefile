TARGET=perfEG
CC=gcc
DEBUG= -g -O0
WARN= -Wall
CCFLAGS=$(DEBUG) $(WARN)
LD=gcc
OBJS= perfEG.o systems.o utils.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CCFLAGS)
	@rm *.o

perfEG.o: perfEG.c
	$(CC) -c $(CCFLAGS) perfEG.c -o perfEG.o

systems.o: systems.c
	$(CC) -c $(CCFLAGS) systems.c -o systems.o

utils.o: utils.c
	$(CC) -c $(CCFLAGS) utils.c -o utils.o

run: all
	./perfEG