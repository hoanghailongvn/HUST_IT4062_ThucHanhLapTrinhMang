TARGET = final

CXX = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
OBJDIR = obj
LIBDIR = include
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(LIBDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm = rm -f

all: $(BINDIR)/server $(BINDIR)/client $(BINDIR)/sfml

$(BINDIR)/server: $(OBJDIR)/server.o
	$(CXX) $^ -o $@

$(BINDIR)/client: $(OBJDIR)/client.o
	$(CXX) $^ -o $@

$(BINDIR)/sfml: $(OBJDIR)/sfml.o $(OBJDIR)/Game.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@
