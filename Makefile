CC=gcc
IDIR=include
SDIR=src
ODIR=tmp
CFLAGS=-I$(IDIR)

_DEPS=freetalk.h
_OBJ=server.o wrapper.o myerr.o
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)
