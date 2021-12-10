#ifndef PROJECT_CLASSCARD_UTILS_HPP_
#define PROJECT_CLASSCARD_UTILS_HPP_

#include "ClassCard.hpp"
#include <cstddef>
#include <vector>
//#include "ClassCard.hpp"

using namespace std;


class DeckCard {
public:
    vector <Card> deck_vec;
    vector <bool> aval;  //if exists==1 ,else ==0
    vector <sf::RectangleShape> row;
    void append(Card one_card);
    int shuffleDeck();
    size_t getSize();
    Card operator () (size_t pos);
    void make_empty();
    DeckCard(int n,int target){
        aval.resize(n);
        for (int i=0;i<n;i++){
            Card empty_card(111,target);
            deck_vec.push_back(empty_card);
        }
        row.resize(n);
    }
    DeckCard(vector<sf::RectangleShape> &copy,int target){
        aval.resize(copy.size());
         for (int i=0;i<copy.size();i++){
            Card empty_card(111,target);
            deck_vec.push_back(empty_card);
        }
        row.resize(copy.size());
        for (int i=0;i<copy.size();i++){
            row[i]=copy[i];
        }
    }
};

#endif  // PROJECT_CLASSCARD_UTILS_HPP_
