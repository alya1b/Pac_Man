CXXFLAGS = -Isrc/include
LDFLAGS = -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

all: compile link

compile:
	g++ $(CXXFLAGS) -c main.cpp

link:
	g++ main.o -o main $(LDFLAGS)
