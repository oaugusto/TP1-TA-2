CC=gcc
CFLAGS=-lm -I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = clinic_list.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = clinic_list.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main.o $(SDIR)/main.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o