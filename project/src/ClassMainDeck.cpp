#include "../data/ClassMainDeck.hpp"
#include <time.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

void MainDeck::shuffle_deck() {
    srand(time(NULL));
    random_shuffle(Deck.begin(),Deck.end());

}
void MainDeck::append(Card one_card) {
    Deck.push_back(one_card);
}

size_t MainDeck::getSize() {
    return Deck.size();
}

Card MainDeck::operator() (size_t pos) {
    return Deck.at(pos);
}

void MainDeck::giveHand(DeckCard &hand, Discard &d,int n){
    for (int i=0;i<n;i++){
        hand.deck_vec[i]=Deck[Deck.size()-1];
        hand.avaliable[i]=0;
        hand.deck_vec[i].TargetCard=4;
        Deck.pop_back();
        if (Deck.size()==0){
            Deck.insert(Deck.end(), d.discard.begin(), d.discard.end());
            d.clear();
        }
        

    }
}

Card MainDeck::giveCard(Discard &d){
    if (Deck.size()==0){
        Deck.insert(Deck.end(), d.discard.begin(), d.discard.end());
        d.clear();
    }
    Card card=Deck[Deck.size()-1];
    Deck.pop_back();
    return card;
}
Card MainDeck::del_back(){
    Card card(111,0);
    card=Deck[Deck.size()-1];
    Deck.pop_back();
    return card;

}
void Discard::get_card(std::vector<sf::RectangleShape> &shape,DeckCard &row, int card_index,RectangleShape &Discard_rec){
    discard.push_back(row.deck_vec[card_index]);
    Discard_rec.setTexture(row.deck_vec[card_index].GetTexture());
    row.avaliable[card_index]=1;
    Card empty_card(0,0);
    shape[card_index].setTexture(empty_card.GetTexture());
    row.deck_vec[card_index]=empty_card;
}
void Discard::clear(){
    discard.clear();
}





