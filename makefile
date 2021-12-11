# TARGET = projectname

# CXX = g++

# SRCDIR = src
# OBJDIR = obj
# LIBDIR = include
# BINDIR = bin

# SOURCES := $(wildcard $(SRCDIR/*.cpp))
# INCLUDES := $(wildcard $(LIBDIR/*.h))
# OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
# rm = rm -f

# $(BINDIR)/$(TARGET): $(OBJECTS)


# sfml-app: main.o
# 	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

# main.o: main.cpp
# 	g++ -c main.cpp

# main: server.cpp client.cpp
# 	g++ -o server src/server.cpp
# 	g++ -o client src

# clean rm -f *.o *~

test.o: test.cpp