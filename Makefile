CC=clang
CFLAGS = -std=c11 -Wall -Wextra -O2 -Iinclude -MMD
LDFLAGS = 
TARGET = build/solution
SRCDIR = src
OBJDIR = build/obj
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPFILES = $(OBJS:.o=.d)

TESTER=test_all.py

.PHONY: all build clean test test1 test2 test3 test4

all: $(TARGET)

$(TARGET): $(OBJS) | build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) build:
	mkdir -p $@
	
test1: $(TARGET)
	python3 $(TESTER) 1

test2: $(TARGET)
	python3 $(TESTER) 2

test3: $(TARGET)
	python3 $(TESTER) 3

test4: $(TARGET)
	python3 $(TESTER) 4

test: $(TARGET)
	python3 $(TESTER)

clean:
	rm -rf $(BIN_DIR)
	
-include $(DEPFILES)
