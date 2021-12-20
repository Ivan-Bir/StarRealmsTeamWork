#ifndef PROJECT_GRAPHICSUTILS_UTILS_HPP_
#define PROJECT_GRAPHICSUTILS_UTILS_HPP_
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
#include "../data/ClassMainDeck.hpp"

void draw_rec_vector(std::vector<sf::RectangleShape> &v,RenderWindow &window);
int move_card(std::vector<sf::RectangleShape> &shape_from,DeckCard &row_from, std::vector<sf::RectangleShape> &shape_to,DeckCard &row_to,int card_index);
int check_if_clicked(vector <RectangleShape> &vec_shape,Event &event,DeckCard &cards,RenderWindow &window);
void connect_logic_to_graph(vector<RectangleShape>&rec,DeckCard &cards);

void draw(RenderWindow &window,Sprite BackGround,RectangleShape hero_image,
RectangleShape hero_stats,vector<RectangleShape> PlayerHand,RectangleShape playerOneDeck,RectangleShape playerOneDiscard,
vector<RectangleShape> BattleCards,Sprite ShowBIG,vector<RectangleShape> market,RectangleShape MainDeck,RectangleShape endTurnButton,
vector<RectangleShape> EnemyBattleCards, RectangleShape enemyImage,RectangleShape enemyDeck,RectangleShape history,
RectangleShape giveUp,RectangleShape Discard_rec,Text text,Text text_my_hp,Text text_enemy_hp,RectangleShape heroImage,
RectangleShape heroStats,int flag_draw,RectangleShape mainDeck);

#endif  // PROJECT_GRAPHICSUTILS_UTILS_HPP_