# README

A `vector` is a sequence container that encapsulates dynamic size arrays.  The storage of the vector is handled automatically, being expanded as needed.  Access (`at`, `front`, `back`) is O(1).  Insert/remove at the back (`push_back`, `pop_back`) is amortized O(1), otherwise `insert`/`remove` is O(n).

## run
press `Ctrl` `Enter` or click ![the Run button](assets/run.png) to build and run correctness tests.

## make
```sh
# make default (same as make build)
make

# to build only (do not run, default)
make build

# to build and test correctness:
make test

# to build and test coverage
make coverage

# to build and check for memory errors
make leaktest

# to clean up (remove executable, coverage files)
make clean
```

## files

* `main.cpp`: unit tests and main()
* `assets/run.png`: image of the Run button
* `.gitignore`: defines files for Git to ignore
* `.replit`: defines operation of Run button
* `Makefile`: build instructions for make
* `readme.md`: this file
* `todo.md`: todo list 
* `vector.cpp`: definitions of vector methods
* `vector.hpp`: declaration of vector struct and methods