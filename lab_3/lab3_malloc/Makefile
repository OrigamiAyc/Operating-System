#
# Students' Makefile for the Malloc Lab
# it will generate two executable files
# mmdriver tests the implicit linked-list
# ep_mmdriver tests the explicit linked-list
#

CC = gcc -g
CFLAGS = -Wall

OBJS1 = memlib.o  mmdriver.o mm.o
OBJS2 = memlib.o  ep_mmdriver.o ep_mm.o
OBJS_ALL = memlib.o  mmdriver.o ep_mmdriver.o mm.o ep_mm.o

all : mmdriver ep_mmdriver

mmdriver : $(OBJS1)
	cc -o mmdriver $(OBJS1)
ep_mmdriver : $(OBJS2)
	cc -o ep_mmdriver $(OBJS2)

memlib.o : memlib.h config.h
mm_o :	mm.h memlib.h
ep_mm.o : ep_mm.h memlib.h
mmdriver.o :  mm.h memlib.h 
ep_mmdriver.o : ep_mm.h memlib.h

.PHONY : clean
clean:
	-rm mmdriver ep_mmdriver $(OBJS_ALL) 


