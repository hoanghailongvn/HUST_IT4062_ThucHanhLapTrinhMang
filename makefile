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

$(BINDIR)/server: $(OBJDIR)/server.o $(OBJDIR)/Server.o $(OBJDIR)/User.o $(OBJDIR)/Message.o
	$(CXX) $^ -o $@

$(BINDIR)/client: $(OBJDIR)/client.o $(OBJDIR)/Client.o $(OBJDIR)/Message.o $(OBJDIR)/Textbox.o $(OBJDIR)/Button.o $(OBJDIR)/IntroWindow.o $(OBJDIR)/RegisterWindow.o $(OBJDIR)/LoginWindow.o $(OBJDIR)/Notification.o $(OBJDIR)/LobbyWindow.o
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@
