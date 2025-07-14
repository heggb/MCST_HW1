CC=clang
CFLAGS=-std=c11 -Wall -O2
SRC=solve_graph.c

BIN_DIR=build
BIN=$(BIN_DIR)/solution
TESTER=test_all.py

.PHONY: all build clean test test1 test2 test3 test4

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

build: $(BIN)

test1: build
	python3 $(TESTER) 1

test2: build
	python3 $(TESTER) 2

test3: build
	python3 $(TESTER) 3

test4: build
	python3 $(TESTER) 4

test: build
	python3 $(TESTER)

clean:
	rm -rf $(BIN_DIR)
