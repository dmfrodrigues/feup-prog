MKDIR=mkdir -p
RMDIR=rm -rf

PROG=main

SDIR=./src
IDIR=./include
ODIR=./obj

SRCMAIN=$(SDIR)/main.cpp

CC  =g++
CFLAGS=-Wall
IFLAGS=-I$(IDIR)

O_FILES=$(ODIR)/address.o $(ODIR)/agency.o $(ODIR)/agencyclient.o $(ODIR)/agencypack.o $(ODIR)/client.o \
        $(ODIR)/date.o $(ODIR)/globaldefs.o $(ODIR)/helpers.o $(ODIR)/name.o $(ODIR)/travelpack.o \
		$(ODIR)/vat.o

all: $(PROG)

$(PROG): $(O_FILES) $(SRCMAIN)
	$(CC) $(CFLAGS) $(IFLAGS) $(O_FILES) $(SRCMAIN) -o $(PROG)

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(ODIR):
	$(MKDIR) $@

clean:
	$(RMDIR) $(ODIR)
	$(RM) $(PROG)
