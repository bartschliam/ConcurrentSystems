CC = gcc
SRCDIR = src
IDIR = include
CFLAGS = -I$(IDIR) -Wall -lm -fopenmp
ODIR = obj
LDIR = lib
BDIR = bin
EXENAME = app.exe

_DEPS = mytour.h sales.h
DEPS = $(patsubst %, $(IDIR), $(_DEPS))

_OBJ = mytour.o sales.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXENAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXENAME)
