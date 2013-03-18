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

all: format project1 check 
	
project1: main.cpp *.h
	g++ main.cpp -o project1 -g $(CFLAGS)

format: 
	astyle -YfDHUbps4yj -k3 $(SRCS)

check: format
	cppcheck -v --inline-suppr --enable=all $(SRCS)

clean:
	rm -f project1 *.orig *.gch

IFiniteStateMachine.gch: IFiniteStateMachine.h
	$(CC) -c IFiniteStateMachine.h $(CFLAGS)

Machine.gch: Machine.h
	$(CC) -c Machine.h $(CFLAGS)

StateMachineFactory.gch: StateMachineFactory.h TransitionRule.h
	$(CC) -c StateMachineFactory.h $(CFLAGS)

TransitionRule.gch: TransitionRule.h
	$(CC) -c TransitionRule.h $(CFLAGS)

Union.gch: Union.h
	$(CC) -c Union.h $(CFLAGS)

# DO NOT DELETE