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
           // int c=0;
            for (int i = 121; i < 155; i++){
                Card card(i);
                if (card.getId()!=-1){
                    Deck.push_back(card);
                }
            }
        }
        
    }
    MainDeck(char ch, size_t number_duplicates = 1) {
        if (ch == 'D') {
            for (size_t k = 0; k < number_duplicates; k++) {
                for (int i = 121; i < 155; i++){
                    Card card(i);
                    if (card.getId() != -1) {
                        Deck.push_back(card);
                    }
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
    void update_deck();
};





#endif  // PROJECT_CLASSMAINDECK_UTILS_HPP_
