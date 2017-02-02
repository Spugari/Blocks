CC=g++
CFLAGS=-c
LDFLAGS= -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
SOURCES= Game.cpp Main.cpp Grid.cpp Gameobject.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ohjelma

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f ohjelma