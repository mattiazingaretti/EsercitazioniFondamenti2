CC = gcc
CFLAGS = -Wno-nullability-completeness -g
SRCS = linked_list.c graph.c graph_services.c
OBJS = $(SRCS:.c=.o)
HEADERS = $(SRCS:.c=.h)
MAIN = driver

all:    $(MAIN)
	

$(MAIN): $(OBJS) $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c $(OBJS)

%.o: %.c %.h
	gcc -c $(CFLAGS) $*.c -o $*.o

clean:
	$(RM) *.o $(MAIN)
