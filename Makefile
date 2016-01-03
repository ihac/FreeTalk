CC=gcc
IDIR=include
SDIR=src
ODIR=tmp
DFLAGS=-g
CFLAGS=-I$(IDIR)
CLEANFILES=server tmp/*

_DEPS=freetalk.h
_OBJ=server.o wrapper.o myerr.o cliInfo.o
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(DFLAGS) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) $(DFLAGS) -o $@ $(OBJ) $(CFLAGS)

clean:
	rm -f $(CLEANFILES)
