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

%.c: %.check
	checkmk $< > $@
CHECKS = $(patsubst ./tests/%.check, ./tests/%.c, $(wildcard ./tests/*.check))
TESTED_FILES = $(filter-out ./src/main.c, $(wildcard ./src/*.c))
$(TEST): $(CHECKS)
	$(foreach check, $(CHECKS), $(CC) $(CFLAGS) $(LIBS) $(TESTED_FILES) -lcheck $(check) -o $@ && ./$@ &&) :

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f $(TEST)
	-rm -f ./tests/*.c