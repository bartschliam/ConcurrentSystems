CC = gcc
SRCDIR = src
IDIR = include
CFLAGS = -I$(IDIR) -Wall
ODIR = obj
LDIR = lib
BDIR = bin
EXENAME = app.exe

_DEPS = # List Header Files
DEPS = $(patsubst %, $(IDIR), $(_DEPS))

_OBJ = # List desired Object files
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXENAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXENAME)
