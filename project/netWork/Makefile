all: clean_all server client1 client2 clean

server:
	g++ -c server.cpp netWorkUtils.cpp ../src/ClassCard.cpp ../src/ClassDeck.cpp ../src/ClassMainDeck.cpp
	g++ server.o netWorkUtils.o ClassCard.o ClassDeck.o ClassMainDeck.o -o server -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -w

client1:
	g++ -c client1.cpp netWorkUtils.cpp ../src/ClassCard.cpp ../src/ClassDeck.cpp ../src/ClassMainDeck.cpp
	g++ client1.o netWorkUtils.o ClassCard.o ClassDeck.o ClassMainDeck.o -o client1 -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -w

client2:
	g++ -c client2.cpp netWorkUtils.cpp ../src/ClassCard.cpp ../src/ClassDeck.cpp ../src/ClassMainDeck.cpp
	g++ client2.o netWorkUtils.o ClassCard.o ClassMainDeck.o -o client2 -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -w

clean:
	rm -rf *.o

clean_all:
	rm -rf *.o server client1 client2