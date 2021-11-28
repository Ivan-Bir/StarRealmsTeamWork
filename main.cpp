#include "project/data/ClassCard.hpp"
//#include "project/data/ClassDeck.hpp"
#include "project/data/utils.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
 
using namespace sf;
using namespace std;
 
int main() {
	TableShapesDraw();
	// DeckCard market_deck;
	vector<Card> market_deck;
	for (int i = 110; i < 156; i++) { //Создаю все карты, прописанные в Базе данных
		Card a(i);
		if (a.GetParameters() == 1) {
			cout << endl;
			cout << "------------------------------------------";
			cout << endl;
			market_deck.push_back(a);
		}
	}

	cout << "Печатаю карты колоды в стандартном порядке!!!" << endl;
	for (size_t i = 0; i < market_deck.size(); i++) {
		//cout << market_deck.at(i).getId() << " -- ";
		market_deck.at(i).GetParameters();
	}

	cout << "Печатаю индексы карт перемешанной колоды!!!" << endl;
	srand(time(NULL));
	random_shuffle(market_deck.begin(), market_deck.end());
	
	for (size_t i = 0; i < market_deck.size(); i++) {
		cout << market_deck.at(i).getId() << " -- ";
		//market_deck.at(i).GetParameters();
	}
	
	return 0;
}