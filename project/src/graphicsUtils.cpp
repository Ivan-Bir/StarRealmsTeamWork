#include "../data/graphicsUtils.hpp"

void draw_rec_vector(std::vector<sf::RectangleShape> &v,RenderWindow &window){
    for (int i=0;i<v.size();i++){
        window.draw(v[i]);
    }
    return;
}

int move_card(std::vector<sf::RectangleShape> &shape_from,DeckCard &row_from, std::vector<sf::RectangleShape> &shape_to,DeckCard &row_to,int card_index){
    //if returns 1-successfull,else-not sucessful
    for (int i=0;i<shape_to.size();i++){
        if (row_to.avaliable[i]){
            Card card_to_move=row_from.deck_vec[card_index];
            Card empty_card(000,0);
            row_to.deck_vec[i]=card_to_move;
            row_from.deck_vec[card_index]=empty_card;
            row_to.avaliable[i]=0;
            row_from.avaliable[i]=1;
            shape_from[card_index].setTexture(row_from.deck_vec[card_index].GetTexture());
            shape_to[i].setTexture(row_to.deck_vec[i].GetTexture());
            row_to.deck_vec[i].TargetCard=5;
            return 1;
        }
    }
    return 0;


}
int check_if_clicked(vector <RectangleShape> &vec_shape,Event &event,DeckCard &cards,RenderWindow &window){
    
    for (int i=0;i<vec_shape.size();i++){
        if ( cards.deck_vec[i].getId()!=0 && vec_shape[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) ){
            return i;
        }
    }
                
    
    return -1;
}
void connect_logic_to_graph(vector<RectangleShape>&rec,DeckCard &cards){
    for (int i = 0; i < rec.size(); ++i) {
        rec[i].setTexture(cards.deck_vec[i].GetTexture());
    }
}