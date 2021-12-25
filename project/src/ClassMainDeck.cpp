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

void MainDeck::update_deck() {
    for (int i = 121; i < 158; i++){
        Card card(i);
        if (card.getId() != -1) {
            this -> append(card);
        }
    }
}

size_t MainDeck::getSize() {
    return Deck.size();
}

Card MainDeck::operator() (size_t pos) {
    return Deck.at(pos);
}

void MainDeck::giveHand(DeckCard &hand, Discard &d,int n,Texture &disc_text){
    for (int i=0;i<n;i++){
        hand.deck_vec[i]=Deck[Deck.size()-1];
        cout << "2663";
        hand.deck_vec[i].texture.loadFromFile(hand.deck_vec[i].path_file_img);
        cout << "2664";
        hand.avaliable[i]=0;
        hand.deck_vec[i].TargetCard = PLAYER_HAND;
        Deck.pop_back();
        cout << "2667";
        if (Deck.size()==0){
            for (int j=0;j<d.discard.size();j++){
                Deck.push_back(d.discard[j]);
            }
            this->shuffle_deck();
            disc_text.loadFromFile("../include/images/backplate.jpg");
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
    cout << "Удаляется и возвращается карта ";
    Card card(111, 0);
    card = Deck[Deck.size() - 1];
    Deck.pop_back();
    cout << card.getId() << " ,";
    return card;

}
void Discard::get_card(std::vector<sf::RectangleShape> &shape,DeckCard &row, int card_index,Texture &discard_texture){
    discard.push_back(row.deck_vec[card_index]);
    discard_texture=row.deck_vec[card_index].texture;
    row.avaliable[card_index]=1;
    Card empty_card(0,0);
    empty_card.texture.loadFromFile(empty_card.path_file_img);
    row.deck_vec[card_index].texture=empty_card.texture;
    shape[card_index].setTexture(&(row.deck_vec[card_index].texture));
    row.deck_vec[card_index]=empty_card;
}
void Discard::clear(){
    discard.clear();
}





