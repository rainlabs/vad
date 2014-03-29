CC         = g++
CXX        = g++
CXXFLAGS   = -c -Wall -std=c++0x
LDFLAGS    = -lsfml-system -lsfml-audio -lsvm
SOURCES    = main.cpp signal.cpp window.cpp c_svm.cpp mfcc.cpp
HEADERS    = signal.h window.h c_svm.h mfcc.h
OBJECTS    = $(SOURCES:.cpp=.o)
EXECUTABLE = vad

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
