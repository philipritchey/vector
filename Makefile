CXX = g++
STD = -std=c++17
WARNINGS = -Wall -Wextra -Weffc++
ERRORS = -pedantic-errors 
SANITIZERS = -fsanitize=address,undefined
COVERAGE = --coverage
DEBUGGING = -g
CXXFLAGS = $(STD) $(WARNINGS) $(ERRORS) $(DEBUGGING)

default: build

build: main.cpp vector.hpp
	$(CXX) $(CXXFLAGS) main.cpp

test: main.cpp vector.hpp
	$(CXX) $(CXXFLAGS) main.cpp && ./a.out

coverage: clean main.cpp vector.hpp
	$(CXX) $(STD) $(DEBUGGING) $(COVERAGE) main.cpp && ./a.out && gcov -mr main.cpp

memoryerrortest: main.cpp vector.hpp
	$(CXX) $(STD) $(DEBUGGING) $(SANITIZERS) main.cpp && ./a.out

.PHONY: clean

clean:
	rm -f *.gcda *.gcno *.gcov a.out


