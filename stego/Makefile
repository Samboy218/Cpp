AutomatedMakefile = am
CC = g++

FILES =	stego.o lodepng.o
EXECUTABLE = stego

INC_DIRS =
LIB_DIRS =
LIBS =
FLAGS = -std=c++11 -Wall -Werror


COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

all: Project

Project:			$(FILES)
					$(LINK) $(EXECUTABLE) $(FILES) $(LIBS) $(FLAGS)
					
stego.o:			stego.cpp lodepng.h
					$(COMPILE) $(FLAGS) stego.cpp

lodepng.o:			lodepng.h lodepng.cpp
					$(COMPILE) $(FLAGS) lodepng.cpp
