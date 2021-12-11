#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>
#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
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
            return 1;
        }
    }
    return 0;


}


int main()
{
	RenderWindow window(VideoMode(1600, 900), "SFML Works!");

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


	ConvexShape endTurnButton;
	endTurnButton.setPointCount(8);

	endTurnButton.setPoint(0, Vector2f(1380.f, 294.f));
	endTurnButton.setPoint(1, Vector2f(1330.f, 328.f));
	endTurnButton.setPoint(2, Vector2f(1330.f, 428.f));
	endTurnButton.setPoint(3, Vector2f(1380.f, 462.f));
	endTurnButton.setPoint(4, Vector2f(1500.f, 462.f));
    endTurnButton.setPoint(5, Vector2f(1550.f, 428.f));
    endTurnButton.setPoint(6, Vector2f(1550.f, 328.f));
    endTurnButton.setPoint(7, Vector2f(1500.f, 294.f));
 
	endTurnButton.setFillColor(Color(175, 180, 240));

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



    //Закончили создавать шэйпы теперь создаем спрайты,нэйминг-smailcase
    //g++ -I../data/* -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system  --собираем так
    //g++ -I../data/* -o main main.cpp ClassCard.cpp ClassDeck.cpp  -lsfml-graphics -lsfml-window -lsfml-system -- или вот так если нужны карты
    //ЕЩЕ РАЗ ПОДУМАТЬ НАД МЭЙКФАЙЛОМ
    DeckCard player_hand(3,1);
   // DeckCard enemy_battle_card(&EnemyBattleCards,1);
   // DeckCard market_spr(&market,1);
    //Card card(111,1);
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    if (!texture1.loadFromFile("project/include/images/154.jpg")){
       return 1;
    }
    /*for (int i=0;i<PlayerHand.size();i++){
        PlayerHand[i].setTexture(player_hand.deck_vec[i].GetTexture());
    }*/
    PlayerHand[0].setTexture(player_hand.deck_vec[0].GetTexture());
    if (!texture2.loadFromFile("project/include/images/112.jpg")){
       return 1;
    }
    market[0].setTexture(&texture2);
    market[0].setFillColor(Color(255,255,255));
     if (!texture3.loadFromFile("project/include/images/143.jpg")){
       return 1;
    }
    BattleCards[0].setTexture(&texture3);
    EnemyBattleCards[0].setTexture(&texture1);
    //По какой=то прчиине  Создание DeckCard создает бесконечность шэйпов
    //Разобраться почему!!
    







	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::White);
        window.draw(heroImage);
        window.draw(heroStats);
        draw_rec_vector(PlayerHand,window);
        window.draw(playerOneDeck);
        window.draw(playerOneDiscard);

        window.draw(outpost1);
        window.draw(outpost2);
        draw_rec_vector(BattleCards,window);
        

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

		window.display();
	}
 
	return 0;
}
