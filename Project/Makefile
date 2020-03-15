XXFLAGS = -g -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

SOURCEDIR = source
BUILDIR = build

LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -ldl 

EXECUTABLE = jurassicPlayer

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp) 

DEPENDENCIES = $(wildcard $(SOURCEDIR)/*.hpp) 

_OBJECTS = $(SOURCES:.cpp=.o)

OBJECTS = $(patsubst $(SOURCEDIR)/%,$(BUILDIR)/%,$(_OBJECTS)) 

$(BUILDIR)/%.o: $(SOURCEDIR)/%.cpp $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS) $(BUILDIR)/glad.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

.PHONY : cleanobj clean

cleanobj:
	rm $(OBJECTS)
clean:
	rm $(EXECUTABLE)
