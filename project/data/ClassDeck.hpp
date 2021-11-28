//#include "ClassCard.hpp"
#include <cstddef>
#include <vector>
//#include "ClassCard.hpp"

using namespace std;

class DeckCard {
    vector<Card> deck_vec;
public:
    void append(Card one_card);
    int shuffleDeck();
    size_t getSize();
    Card operator () (size_t pos);
};
