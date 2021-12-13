TARGET = star

HDRS = \
	   project/data/

SRCS = \
	    main.cpp \
		project/src/ClassCard.cpp \
		project/src/ClassDeck.cpp \
		project/include/TableShape.cpp


.PHONY: all check build rebuild clean

all: clean check build clean_o

build: $(TARGET)

rebuild: clean build clean_o

$(TARGET): $(SRCS)
	g++ -c $(SRCS)
	g++ main.o ClassCard.o ClassDeck.o TableShape.o -I $(HDRS) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(TARGET)

clean_o:
	rm -f *.o