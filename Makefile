CFLAGS=-O2

start: build
	build/gameoflife

build: src/main.cpp
	clang++ src/main.cpp $(CFLAGS) -o build/gameoflife

