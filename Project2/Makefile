###################################
# Makefile
# HW 1
# CS537 - Data Communications - Spring 2013
# Jim Counts
###################################
CC = g++
INCLUDE = -I ../igloo
CFLAGS = -lpthread -Wall
SRCS = *.cpp *.h

all: format project2 check 
	
project2: main.cpp *.h
	g++ main.cpp -o project2 -g $(CFLAGS)

format: 
	astyle -YfDHUbps4yj -k3 $(SRCS)

check: format
	cppcheck -v --inline-suppr --enable=all $(SRCS)

clean:
	rm -f project2 *.orig *.gch

PushdownAutomata.gch: PushdownAutomata.h
	$(CC) -c PushdownAutomata.h $(CFLAGS)

Program.gch: Program.h
	$(CC) -c Program.h $(CFLAGS)

Tests.gch: Tests.h TransitionRule.h
	$(CC) -c Tests.h $(CFLAGS)

TransitionRule.gch: TransitionRule.h
	$(CC) -c TransitionRule.h $(CFLAGS)

TransitionResult.gch: TransitionResult.h
	$(CC) -c TransitionResult.h $(CFLAGS)

# DO NOT DELETE

# CC = g++
# CFLAGS = -O2 

# PROG = CS421_Project2
# HDRS = PushdownAutomata.h Program.h TransitionResult.h Tests.h TransitionRule.h
# SRCS = main.cpp

# OBJS = $(SRCS:.cpp=.o)

# $(PROG) : $(SRCS) $(HDRS)
# 	$(CC) $(SRCS) -o $(PROG) $(CFLAGS)

# clean :
# 	rm -f core $(PROG) $(OBJS)
