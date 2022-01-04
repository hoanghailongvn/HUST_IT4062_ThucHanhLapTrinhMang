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
SERVER_OBJECTS = $(OBJDIR)/server.o $(OBJDIR)/Server.o $(OBJDIR)/Room.o $(OBJDIR)/Game.o
CLIENT_OBJECTS = $(filter-out $(SERVER_OBJECTS), $(OBJECTS))

all: $(BINDIR)/server $(BINDIR)/client $(BINDIR)/sfml

$(BINDIR)/server: $(SERVER_OBJECTS) $(OBJDIR)/Message.o $(OBJDIR)/UserClient.o  $(OBJDIR)/User.o
	$(CXX) $^ -o $@ -pthread

$(BINDIR)/client: $(CLIENT_OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@ -pthread

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@

clear:
	rm -f $(OBJECTS)