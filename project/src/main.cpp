#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>
#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
#include "../data/ClassMainDeck.hpp"
using namespace sf;






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
    for (int i=0;i<rec.size();i++){
        rec[i].setTexture(cards.deck_vec[i].GetTexture());
    }
}

int main()
{   sf::ContextSettings settings;
    sf::Texture empty_texture;
    empty_texture.loadFromFile("project/include/images/0.jpg");
    settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1600, 900), "SFML Works!",sf::Style::Default, settings);

	RectangleShape heroImage(Vector2f(220.f, 308.f));
    RectangleShape heroStats(Vector2f(320.f, 160.f));

    std::vector <RectangleShape> PlayerHand;
    for (int i=0;i<5;i++){
        PlayerHand.push_back(RectangleShape(Vector2f(150.f, 210.f)));
    }

    RectangleShape playerOneDeck(Vector2f(130.f, 90.f));
    RectangleShape playerOneDiscard(Vector2f(130.f, 90.f));
	heroImage.move(20, 572);
    heroStats.move(260, 720);
    
	PlayerHand[0].move(600, 670);
    PlayerHand[1].move(770, 670);
    PlayerHand[2].move(940, 670);
    PlayerHand[3].move(1110, 670);
    PlayerHand[4].move(1280, 670);
    playerOneDeck.move(1450, 670);
    playerOneDiscard.move(1450, 790);

    heroImage.setFillColor(Color(175, 180, 240));
    heroStats.setFillColor(Color(175, 180, 240));

    for (int i=0;i<PlayerHand.size();i++){
        PlayerHand[i].setFillColor(Color(175, 180, 240));
    }

    playerOneDeck.setFillColor(Color(175, 180, 240));
    playerOneDiscard.setFillColor(Color(175, 180, 240));


    std::vector <RectangleShape> BattleCards;
    for (int i=0;i<5;i++){
        BattleCards.push_back(RectangleShape(Vector2f(120.f, 168.f)));
    }
    RectangleShape outpost1(Vector2f(168.f, 120.f));
    RectangleShape outpost2(Vector2f(168.f, 120.f));
    outpost1.move(265, 530);
    outpost2.move(448, 530);

    BattleCards[0].move(631, 482);
    BattleCards[1].move(766, 482);
    BattleCards[2].move(901, 482);
    BattleCards[3].move(1036, 482);
    BattleCards[4].move(1171, 482);
    BattleCards[5].move(1306, 482);
    BattleCards[6].move(1441, 482);

    outpost1.setFillColor(Color(175, 180, 240));
    outpost2.setFillColor(Color(175, 180, 240));
    for (int i=0;i<BattleCards.size();i++){
        BattleCards[i].setFillColor(Color(175, 180, 240));
    }

    RectangleShape additionalMarket(Vector2f(120.f, 168.f));

    std::vector <RectangleShape> market;
    for (int i=0;i<5;i++){
        market.push_back(RectangleShape(Vector2f(120.f, 168.f)));
    }

    RectangleShape mainDeck(Vector2f(160.f, 120.f));
    additionalMarket.move(265, 294);
    
    market[0].move(400, 294);
    market[1].move(535, 294);
    market[2].move(670, 294);
    market[3].move(805, 294);
    market[4].move(940, 294);
    mainDeck.move(1075, 318);

    additionalMarket.setFillColor(Color(175, 180, 240));

     for (int i=0;i<market.size();i++){
        market[i].setFillColor(Color(175, 180, 240));
    }

    mainDeck.setFillColor(Color(175, 180, 240));


	
    RectangleShape endTurnButton(Vector2f(130.f, 90.f));
    endTurnButton.move(Vector2f(1380.f, 294.f));
	endTurnButton.setFillColor(Color(175, 180, 240));
    RectangleShape Discard_rec(Vector2f(150.f, 210.f));
    Discard_rec.move(1380.f, 400.f);
    Discard_rec.setFillColor(Color(175, 180, 240));
    RectangleShape enemyOutpost1(Vector2f(168.f, 120.f));
    RectangleShape enemyOutpost2(Vector2f(168.f, 120.f));

    std::vector <RectangleShape> EnemyBattleCards;
    for (int i=0;i<7;i++){
        EnemyBattleCards.push_back(RectangleShape(Vector2f(120.f, 168.f)));
    }


    enemyOutpost1.move(265, 154);
    enemyOutpost2.move(448, 154);
    EnemyBattleCards[0].move(631, 106);
    EnemyBattleCards[1].move(766, 106);
    EnemyBattleCards[2].move(901, 106);
    EnemyBattleCards[3].move(1036, 106);
    EnemyBattleCards[4].move(1171, 106);
    EnemyBattleCards[5].move(1306, 106);
    EnemyBattleCards[6].move(1441, 106);
    for (int i=0;i<EnemyBattleCards.size();i++){
        EnemyBattleCards[i].setFillColor(Color(175, 180, 240));
    }

    enemyOutpost1.setFillColor(Color(175, 180, 240));
    enemyOutpost2.setFillColor(Color(175, 180, 240));

    RectangleShape enemyImage(Vector2f(220.f, 308.f));
    RectangleShape enemyDeck(Vector2f(220.f, 90.f));
    RectangleShape history(Vector2f(220.f, 45.f));
    RectangleShape giveUp(Vector2f(220.f, 45.f));

    enemyImage.move(20, 20);
    enemyDeck.move(260, 20);
    history.move(1120, 20);
    giveUp.move(1360, 20);

    enemyImage.setFillColor(Color(175, 180, 240));
    enemyDeck.setFillColor(Color(175, 180, 240));
    history.setFillColor(Color(175, 180, 240));
    giveUp.setFillColor(Color(175, 180, 240));





    ///////ЧИТАТЬ КОД СЛЕДУЕТ НАЧИНАЯ С ЭТОЙ СТРОКИ(ну и почитайте функции пожожда)
    int hp=0;
    int damage=0;
    int coin=0;
    sf::Sprite ShowBIG(empty_texture);
    ShowBIG.setScale(0.7,0.7);
    ShowBIG.move(Vector2f(20.f, 330.f));
    sf::Texture background;
    background.loadFromFile("project/include/images/background.jpg");
    IntRect backgr_rect(0,0,100000,10000);
    sf::Sprite BackGround(background);
    BackGround.setTextureRect(backgr_rect);
    sf::Texture hero_image;
    hero_image.loadFromFile("project/include/images/Hero1.jpg");
    heroImage.setTexture(&hero_image);
    sf::Texture enemy_image;
    enemy_image.loadFromFile("project/include/images/Hero2.jpg");
    enemyImage.setTexture(&enemy_image);
    sf::Texture backplate;
    backplate.loadFromFile("project/include/images/backplate.jpg");
    mainDeck.setTexture(&backplate);
    sf::Texture discrad_texture;
    discrad_texture.loadFromFile("project/include/images/backplate.jpg");
    Discard_rec.setTexture(&discrad_texture);
    //Font font();
   // Text text("Здоровье персонажа"+to_string(hp),Font);
    DeckCard player_hand(5,1);
    DeckCard battle_cards(5,1);
    DeckCard market_cards(5,1);
    DeckCard enemy_battle_cards(5,1);
    Discard d;
   
    
    
    MainDeck Deck(30,'d');
    MainDeck MarketDeck(60,'m');
    Deck.giveHand(player_hand,d,5,discrad_texture);
    MarketDeck.giveHand(market_cards,d,5,discrad_texture);
    connect_logic_to_graph(PlayerHand,player_hand);
    connect_logic_to_graph(market,market_cards);



    
    
    int flag_draw=0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
            if (event.type == Event::MouseButtonPressed){
                    ShowBIG.setTexture(empty_texture);
                    IntRect sprite_rect(0,0,300,420);
                    ShowBIG.setTextureRect(sprite_rect);
                    flag_draw=0;
                if (event.mouseButton.button == sf::Mouse::Left){
                    int pos=check_if_clicked(PlayerHand,event,player_hand,window);

                    if (pos!=-1){
            
                        move_card(PlayerHand,player_hand,BattleCards,battle_cards,pos);
                    
                    }
                    if (endTurnButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        //EndTurn
                        for (int i=0;i<PlayerHand.size();i++){
                            if (player_hand.deck_vec[i].getId()!=0){
                                d.get_card(PlayerHand,player_hand,i,discrad_texture);
                                //cout<<discrad_texture.getNativeHandle()<<" ";
                            }
                           
                        }
                         for (int i=0;i<BattleCards.size();i++){
                            if (battle_cards.deck_vec[i].getId()!=0){
                                d.get_card(BattleCards,battle_cards,i,discrad_texture);
                            }
                            
                        }
                        Deck.giveHand(player_hand,d,5,discrad_texture);
                        connect_logic_to_graph(PlayerHand,player_hand);
                    }
                    pos=check_if_clicked(market,event,market_cards,window); //Проверяем что покупаем с маркета
                    if (pos!=-1){
                        d.get_card(market,market_cards,pos,discrad_texture);
                        market_cards.deck_vec[pos]=MarketDeck.giveCard(d);
                        connect_logic_to_graph(market,market_cards);
                    }

                }
                if (event.mouseButton.button == sf::Mouse::Middle){
                    //Добавить  просмотр вывода карт противника
                    int pos=check_if_clicked(PlayerHand,event,player_hand,window);
                    if (pos!=-1){
                        flag_draw=1;
                        ShowBIG.setTexture(*(player_hand.deck_vec[pos].GetTexture()));
                    }
                    pos=check_if_clicked(BattleCards,event,battle_cards,window);
                    if (pos!=-1){
                        flag_draw=1;
                        ShowBIG.setTexture(*(battle_cards.deck_vec[pos].GetTexture()));
                    }
                    pos=check_if_clicked(market,event,market_cards,window);
                    if (pos!=-1){
                        flag_draw=1;
                        ShowBIG.setTexture(*(market_cards.deck_vec[pos].GetTexture()));
                    }
                    pos=check_if_clicked(EnemyBattleCards,event,enemy_battle_cards,window);
                    if (pos!=-1){
                        flag_draw=1;
                        ShowBIG.setTexture(*(enemy_battle_cards.deck_vec[pos].GetTexture()));
                    }
                }
            }
           

            

		}

		window.clear(Color::White);
        window.draw(BackGround);
        window.draw(heroImage);
        window.draw(heroStats);
        draw_rec_vector(PlayerHand,window);
        window.draw(playerOneDeck);
        window.draw(playerOneDiscard);

        window.draw(outpost1);
        window.draw(outpost2);
        draw_rec_vector(BattleCards,window);
        if (flag_draw){
            window.draw(ShowBIG);
        }
        window.draw(additionalMarket);

        draw_rec_vector(market,window);
       
        window.draw(mainDeck);

        window.draw(endTurnButton);

        window.draw(enemyOutpost1);
        window.draw(enemyOutpost2);
        draw_rec_vector(EnemyBattleCards,window);
        window.draw(enemyImage);
        window.draw(enemyDeck);
        window.draw(history);
        window.draw(giveUp);
        window.draw(Discard_rec);
		window.display();
	}
 
	return 0;
}
