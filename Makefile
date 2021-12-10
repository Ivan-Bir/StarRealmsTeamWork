TARGET = star

HDRS = \
	   project/data/

SRCS = \
	    main.cpp \
		project/src/ClassCard.cpp \
		project/src/ClassDeck.cpp \
		project/include/TableShape.cpp


.PHONY: all check build rebuild clean start

all: clean check build start

build: $(TARGET)

rebuild: clean build

$(TARGET): $(SRCS)
	g++ -c $(SRCS)
	g++ main.o ClassCard.o ClassDeck.o TableShape.o -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

start: ./$(TARGET)

clean:
	rm -f $(TARGET)