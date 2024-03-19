# PROGRAMA
    PROG = perfEG

# Compilador
    CC     = gcc
    CFLAGS = -o0
    LFLAGS = -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

# OBJETOS
	OBJS = $(PROG).o system.o utils.o

.PHONY: all clean purge dist

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OBJS) $(LFLAGS)

$(PROG).o: $(PROG).c
	@echo "Compilando $(PROG) ..."
	@$(CC) $(CFLAGS) -o $(PROG) $(PROG).c $(LFLAGS)

system.o: system.c
	@echo "Compilando system ..."
	@$(CC) $(CFLAGS) -o system.o system.c $(LFLAGS)

utils.o: utils.c
	@echo "Compilando utils ..."
	@$(CC) $(CFLAGS) -o utils.o utils.c $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
