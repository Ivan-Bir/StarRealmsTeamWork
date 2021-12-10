#include "../data/ClassDeck.hpp"
// #include "../data/ClassCard.hpp"
#include <time.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

int DeckCard::shuffleDeck() {
    srand(time(NULL));
    random_shuffle(deck_vec.begin(),deck_vec.end());
    return 1;
}
void DeckCard::append(Card one_card) {
    deck_vec.push_back(one_card);
}

size_t DeckCard::getSize() {
    return deck_vec.size();
}

Card DeckCard::operator() (size_t pos) {
    return deck_vec.at(pos);
}

void DeckCard::make_empty(){
    for (int i=0;i<deck_vec.size();i++){
        aval[i]=0;
    }
}