TARGET = star

HDRS = \
	   /include

SRCS = \
	   main.cpp

.PHONY: all check build rebuild clean start

all: clean check build start

build: $(TARGET)

rebuild: clean build

$(TARGET): $(SRCS)
	g++ -c main.cpp
	g++ main.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

start: ./$(TARGET)

clean:
	rm -f $(TARGET)