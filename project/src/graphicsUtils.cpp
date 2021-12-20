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


void draw(RenderWindow &window,Sprite BackGround,RectangleShape hero_image,
RectangleShape hero_stats,vector<RectangleShape> PlayerHand,RectangleShape playerOneDeck,RectangleShape playerOneDiscard,
vector<RectangleShape> BattleCards,Sprite ShowBIG,vector<RectangleShape> market,RectangleShape MainDeck,RectangleShape endTurnButton,
vector<RectangleShape> EnemyBattleCards, RectangleShape enemyImage,RectangleShape enemyDeck,RectangleShape history,
RectangleShape giveUp,RectangleShape Discard_rec,Text text,Text text_my_hp,Text text_enemy_hp,RectangleShape heroImage,
RectangleShape heroStats,int flag_draw,RectangleShape mainDeck){
                        window.clear(Color::White);
                        window.draw(BackGround);
                        window.draw(heroImage);
                        window.draw(heroStats);
                        draw_rec_vector(PlayerHand,window);
                        window.draw(playerOneDeck);
                        window.draw(playerOneDiscard);

                       // window.draw(outpost1);
                        //window.draw(outpost2);
                        draw_rec_vector(BattleCards,window);
                        if (flag_draw){
                            window.draw(ShowBIG);
                        }
                        //window.draw(additionalMarket);

                        draw_rec_vector(market,window);
                    
                        window.draw(mainDeck);

                        window.draw(endTurnButton);

                        //window.draw(enemyOutpost1);
                        //window.draw(enemyOutpost2);
                        draw_rec_vector(EnemyBattleCards,window);
                        window.draw(enemyImage);
                        window.draw(enemyDeck);
                        window.draw(history);
                        window.draw(giveUp);
                        window.draw(Discard_rec);
                        window.draw(text);
                        window.draw(text_my_hp);
                        window.draw(text_enemy_hp);
                        window.display();
}