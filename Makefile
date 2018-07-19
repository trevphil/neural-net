TARGET	= main
TEST	= test
LIBS	= -lm
CC		= gcc
CFLAGS	= -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst ./src/%.c, ./src/%.o, $(wildcard ./src/*.c))
HEADERS = $(wildcard ./src/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

./tests/generated/%.c: ./tests/checks/%.m
	checkmk $< > $@
CHECKS = $(patsubst ./tests/checks/%.m, ./tests/generated/%.c, $(wildcard ./tests/checks/*.m))
TESTED_FILES = $(filter-out ./src/main.c, $(wildcard ./src/*.c))
$(TEST): $(CHECKS)
	$(foreach check, $(CHECKS), $(CC) $(CFLAGS) $(LIBS) $(TESTED_FILES) -lcheck $(check) -o $@ && ./$@ &&) :

clean:
	find . -name *.o -delete
	-rm -rf $(TARGET) $(TARGET).dSYM
	-rm -rf $(TEST) $(TEST).dSYM
	-rm -f ./tests/generated/*.c
