CXX = g++
STD = -std=c++17
WARNINGS = -Wall -Wextra -Weffc++
ERRORS = -pedantic-errors 
SANITIZERS = -fsanitize=address,undefined
COVERAGE = --coverage
DEBUGGING = -g
CXXFLAGS = $(STD) $(WARNINGS) $(ERRORS) $(DEBUGGING)

default: build

build: main.cpp vector.cpp
	$(CXX) $(CXXFLAGS) main.cpp vector.cpp

test: main.cpp vector.cpp
	$(CXX) $(CXXFLAGS) main.cpp vector.cpp && ./a.out

coverage: clean main.cpp vector.cpp
	$(CXX) $(STD) $(DEBUGGING) $(COVERAGE) main.cpp vector.cpp && ./a.out && gcov -mr vector.cpp

memoryerrortest: main.cpp vector.cpp
	$(CXX) $(STD) $(DEBUGGING) $(SANITIZERS) main.cpp vector.cpp && ./a.out

.PHONY: clean

clean:
	rm -f *.gcda *.gcno *.gcov a.out


