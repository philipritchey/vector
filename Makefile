CXX = g++
STD = -std=c++17
WARNINGS = -Wall -Wextra -Weffc++
ERRORS = -pedantic-errors 
SANITIZERS = -fsanitize=address,undefined
COVERAGE = --coverage
DEBUGGING = -g
CXXFLAGS = $(STD) $(WARNINGS) $(ERRORS) $(DEBUGGING)

default: test

test: main.cpp vector.cpp
	$(CXX) $(CXXFLAGS) main.cpp vector.cpp

coverage: clean main.cpp vector.cpp
	$(CXX) $(STD) $(DEBUGGING) $(COVERAGE) main.cpp vector.cpp

leaktest: main.cpp vector.cpp
	$(CXX) $(STD) $(DEBUGGING) $(SANITIZERS) main.cpp vector.cpp

.PHONY: clean

clean:
	rm -f *.gcda *.gcno *.gcov a.out


