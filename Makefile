TARGET = star

HDRS = \
	   /include

SRCS = \
	   tets_sf.cpp

.PHONY: all check build rebuild clean start

all: clean check build start

build: $(TARGET)

rebuild: clean build

$(TARGET): $(SRCS)
	g++ -c tets_sf.cpp
	g++ tets_sf.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

start: ./$(TARGET)

clean:
	rm -f $(TARGET)