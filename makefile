CC := gcc
CFLAGS := -Wall -O0 -std=c99 -g
CLIBFLAG := -c

OUTDIR := build

INCLUDE := include
SRC	:= src

EXECUTABLE := $(OUTDIR)/main.exe
EXEC_SOURCE := $(wildcard *.c)
SOURCES := $(wildcard $(SRC)/*.c)
INCLUDES := $(wildcard $(INCLUDE)/*.h)

OBJECTS := $(patsubst $(SRC)/%.c, $(OUTDIR)/%.o, $(SOURCES))


.PHONY: build-debug clean all run run-debug

all: build-debug

$(EXECUTABLE): $(OBJECTS) $(EXEC_SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o: $(SRC)/%.c
	$(CC) $(CLIBFLAG) -I$(INCLUDE) $(CFLAGS) -o $@ $^

build-debug: $(OUTDIR) $(EXECUTABLE)
	@echo EXE: $(EXECUTABLE)
#	@echo SOURCES: $(SOURCES)
#	@echo INCLUDES: $(INCLUDES)
	@echo OBJECTS: $(OBJECTS)


$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	del $(OUTDIR)

run:
	./$(EXECUTABLE)

run-debug:
	gdb $(EXECUTABLE)