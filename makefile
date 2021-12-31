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
CLIENT_OBJECTS = $(filter-out $(OBJDIR)/server.o $(OBJDIR)/Server.o, $(OBJECTS))

all: $(BINDIR)/server $(BINDIR)/client $(BINDIR)/sfml

$(BINDIR)/server: $(OBJDIR)/server.o $(OBJDIR)/Server.o $(OBJDIR)/User.o $(OBJDIR)/Message.o $(OBJDIR)/Room.o $(OBJDIR)/UserClient.o
	$(CXX) $^ -o $@ -pthread

$(BINDIR)/client: $(CLIENT_OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@ -pthread

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@

clear:
	rm -f $(OBJECTS)