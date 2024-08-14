# Makefile

ROOTCFLAGS    := $(shell root-config --cflags)
ROOTLIBS      := $(shell root-config --libs) -lGeom
ROOTGLIBS     := $(shell root-config --glibs) -lGeom

TARGET        := sa_digitizer
INCDIR        := include
SRCDIR        := src
SRC           := main.cpp $(wildcard $(SRCDIR)/*.cpp)
OBJ           := $(SRC:.cpp=.o)

CXX           := g++
CXXFLAGS      := -I$(INCDIR) $(ROOTCFLAGS)
LDFLAGS       := $(ROOTLIBS) $(ROOTGLIBS)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean

