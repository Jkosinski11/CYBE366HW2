#MAKEFILE
CC = g++
CFLAGS = -g
RM = rm -f

default: all

all: homework2

homework2: homework2.cpp
		$(CC) $(CFLAGS) -o homework2 homework2.cpp

clean:
		$(RM) homework2 *~