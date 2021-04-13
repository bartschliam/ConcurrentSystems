CC = gcc
SRCDIR = src
IDIR = include
CFLAGS = -I$(IDIR) -Wall -fopenmp 
ODIR = obj
LDIR = lib
BDIR = bin
EXENAME = app.exe
LIBS = -lm

_DEPS = mytour.h sales.h
DEPS = $(patsubst %, $(IDIR), $(_DEPS))

_OBJ = mytour.o sales.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXENAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LDIR) $(LIBS)

.PHONY: clean
.PHONY: test
.PHONY: petty

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXENAME)

test:
	./$(BDIR)/$(EXENAME) 10
	./$(BDIR)/$(EXENAME) 50
	./$(BDIR)/$(EXENAME) 100
	./$(BDIR)/$(EXENAME) 1000
	./$(BDIR)/$(EXENAME) 10000
	./$(BDIR)/$(EXENAME) 100000
