SRC = shell.c
TARGET = shell.out
LFLAGS = readline

all: build

build:
	@echo "Building"
	gcc -o $(TARGET) $(SRC) -l $(LFLAGS)

clean:
	@echo "Cleaning"
	rm $(TARGET)
