CPPFLAGS += -std=c++20 -Wall

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	BUILD_EXT = .out
else
	ifeq ($(UNAME), Darwin)
		BUILD_EXT = .out
	else
		BUILD_EXT = .exe
	endif
endif

ALL_SOURCES := $(shell find *.cpp)
ALL_EXECUTABLES := $(ALL_SOURCES:.cpp=$(BUILD_EXT))

all: $(ALL_EXECUTABLES)

%.out %.exe: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

%:: $(basename %)$(BUILD_EXT)

clean:
	rm -f *.exe *.out
