#ifndef PROJECT_CLASSMAINDECK_UTILS_HPP_
#define PROJECT_CLASSMAINDECK_UTILS_HPP_

#include "ClassDeck.hpp"
#include "ClassCard.hpp"
#include <cstddef>
#include <vector>


using namespace std;



class Discard {
public:
    vector <Card> discard;
    

    void get_card(std::vector<sf::RectangleShape> &shape,DeckCard &row, int card_index,Texture &discard_texture);
    void clear();
        

    
    
    
};





class MainDeck {
    vector <Card> Deck;
public:
    MainDeck(int n, char ch){
        if (ch=='m'){
            for (int i=0;i<n;i++){
            if (i%2==0){
                Card card1(154,1);
                Deck.push_back(card1);
            }
            else{
                Card card2(151,1);
                Deck.push_back(card2);
            }   
        }
        }
        else{
        
        for (int i=0;i<n;i++){
            if (i%2==0){
                Card card1(111,1);
                Deck.push_back(card1);
            }
            else{
                Card card2(142,1);
                Deck.push_back(card2);
            }   
        }
        }
    }
    

    void shuffle_deck();
    void append(Card one_card);
    Card operator() (size_t pos);
    size_t getSize();
    void giveHand(DeckCard &hand,Discard &d,int n,Texture &disc_text);
    void pop_back();
    Card del_back();
    Card giveCard(Discard &d);
};





#endif  // PROJECT_CLASSMAINDECK_UTILS_HPP_
