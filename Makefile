# Makefile for Dijkstra project

# Compiler and flags
CXX := g++
CXXFLAGS := -O3 -std=c++17 -Wall -Wextra -pedantic
LDFLAGS := -lCatch2Main -lCatch2

# Programs to build
TARGETS := Driver BenchmarkRandomGraphs BenchmarkWorseCaseGraphs Tests

# Detect OS
ifeq ($(OS),Windows_NT)
    EXE := .exe
    RM := del /f
else
    EXE :=
    RM := rm -f
endif

# Check for Catch2 libraries
CATCH2_OK := $(shell ldconfig -p 2>/dev/null | grep -q Catch2 && echo yes)
ifeq ($(CATCH2_OK),)
CATCH2_OK := $(shell $(CXX) -lCatch2Main -lCatch2 -xc /dev/null -o /dev/null 2>/dev/null && echo yes)
endif

ifndef CATCH2_OK
$(warning *** Catch2 library not found. Make sure Catch2 is installed and linkable. ***)
endif

# Default target
all: $(TARGETS)

Driver$(EXE): Driver.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

BenchmarkRandomGraphs$(EXE): BenchmarkRandomGraphs.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

BenchmarkWorseCaseGraphs$(EXE): BenchmarkWorseCaseGraphs.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

Tests$(EXE): Tests.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(addsuffix $(EXE),$(TARGETS))
