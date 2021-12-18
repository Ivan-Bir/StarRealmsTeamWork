TARGET = star

HDRS = \
	   project/data/

SRCS = \
		project/src/main.cpp \
		project/src/ClassCard.cpp \
		project/src/ClassDeck.cpp \
		project/include/TableShape.cpp \
		project/src/ClassMainDeck.cpp


.PHONY: all check build rebuild clean

all: clean check build clean_o

build: $(TARGET)

rebuild: clean build clean_o

$(TARGET): $(SRCS)
	g++ -c $(SRCS)
	g++ main.o ClassCard.o ClassDeck.o TableShape.o ClassMainDeck.o -I $(HDRS) -o  $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

start: ./$(TARGET)
	g++ main.o ClassCard.o ClassDeck.o TableShape.o -I $(HDRS) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(TARGET)

clean_o:
	rm -f *.o