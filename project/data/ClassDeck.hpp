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
    vector <bool> avaliable;  //if exists==1 ,else ==0

    void append(Card one_card);
    int shuffleDeck();
    size_t getSize();
    Card operator () (size_t pos);
    void make_empty();
    DeckCard(int n, int target){
        avaliable.resize(n);
        for (int i = 0; i < n; i++) {
            Card empty_card(000, target);
            deck_vec.push_back(empty_card);
            avaliable[i] = 1;
        }
    }
};

#endif  // PROJECT_CLASSCARD_UTILS_HPP_
