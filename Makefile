CC         = gcc
CXX        = g++
CXXFLAGS   = -c -Wall -std=c++0x
LDFLAGS    = -lsndfile -lfftw3 -lm -lsvm
SOURCES    = vad.cpp signal.cpp window.cpp c_svm.cpp mfcc.cpp
INCLUDES   = -I./
HEADERS    = signal.h window.h c_svm.h mfcc.h
OBJECTS    = $(SOURCES:.cpp=.o)
BUILDDIR   = build
EXECUTABLE = vad

### Debug ENVIRONMENT
debug: CXX += -DDEBUG -g
debug: CC += -DDEBUG -g
###

### Test ENVIRONMENT
TEST_SRC = ./tests/TestRunner.cpp ./tests/MFCCTest.cpp ./tests/SVMTest.cpp $(SOURCES)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TESTS    = $(EXECUTABLE)_test
#test: INCLUDES += -I./tests/
build-tests: CXXFLAGS += -g $(INCLUDES)

$(TESTS): $(TEST_OBJ)
	$(CXX) $(LDFLAGS) -lcppunit $(TEST_OBJ) -o $@
###

all: release build-tests test gz
release: main.cpp $(SOURCES) $(EXECUTABLE)
debug: release
build-tests: $(TEST_SRC) $(TESTS)
test:
	./vad_test

$(EXECUTABLE): main.o $(OBJECTS)
	$(CXX) $(LDFLAGS) main.o $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) main.o $(OBJECTS) $(TESTS) $(TEST_OBJ) cppunitresults.xml gnuplot_* *.gz out*

gz:
	tar czvf tests.tar.gz gnuplot_*


### NetBeans autogenerate

#
#  There exist several targets which are by default empty and which can be
#  used for execution of your targets. These targets are usually executed
#  before and after some main targets. They are:
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage


# build tests
#build-tests: .build-tests-post

#.build-tests-pre:
# Add your pre 'build-tests' code here...

#.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
#test: .test-post

#.test-pre:
# Add your pre 'test' code here...

#.test-post: .test-impl
# Add your post 'test' code here...