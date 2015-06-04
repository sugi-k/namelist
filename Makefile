CC		= gcc
CFLAGS	= -O -Wall
OBJS	= main.o
FILES	= Makefile main.c
PROGRAM = namelist

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS) $(HDRS)
			$(CC) $(OBJS) $(LDGLASGS) -o $(PROGRAM)

clean:;		rm -f *.o *~ *\#
