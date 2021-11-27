#include <SFML/Graphics.hpp>
 
using namespace sf;
 
int main()
{
	RenderWindow window(VideoMode(1600, 900), "SFML Works!");

	RectangleShape heroImage(Vector2f(220.f, 308.f));
    RectangleShape heroStats(Vector2f(320.f, 160.f));
    RectangleShape handCard1(Vector2f(150.f, 210.f));
    RectangleShape handCard2(Vector2f(150.f, 210.f));
    RectangleShape handCard3(Vector2f(150.f, 210.f));
    RectangleShape handCard4(Vector2f(150.f, 210.f));
    RectangleShape handCard5(Vector2f(150.f, 210.f));
    RectangleShape playerOneDeck(Vector2f(130.f, 90.f));
    RectangleShape playerOneDiscard(Vector2f(130.f, 90.f));

	heroImage.move(20, 572);
    heroStats.move(260, 720);
	handCard1.move(600, 670);
    handCard2.move(770, 670);
    handCard3.move(940, 670);
    handCard4.move(1110, 670);
    handCard5.move(1280, 670);
    playerOneDeck.move(1450, 670);
    playerOneDiscard.move(1450, 790);

    heroImage.setFillColor(Color(175, 180, 240));
    heroStats.setFillColor(Color(175, 180, 240));
	handCard1.setFillColor(Color(175, 180, 240));
    handCard2.setFillColor(Color(175, 180, 240));
    handCard3.setFillColor(Color(175, 180, 240));
    handCard4.setFillColor(Color(175, 180, 240));
    handCard5.setFillColor(Color(175, 180, 240));
    playerOneDeck.setFillColor(Color(175, 180, 240));
    playerOneDiscard.setFillColor(Color(175, 180, 240));

    RectangleShape outpost1(Vector2f(168.f, 120.f));
    RectangleShape outpost2(Vector2f(168.f, 120.f));
    RectangleShape BattleCard1(Vector2f(120.f, 168.f));
    RectangleShape BattleCard2(Vector2f(120.f, 168.f));
    RectangleShape BattleCard3(Vector2f(120.f, 168.f));
    RectangleShape BattleCard4(Vector2f(120.f, 168.f));
    RectangleShape BattleCard5(Vector2f(120.f, 168.f));
    RectangleShape BattleCard6(Vector2f(120.f, 168.f));
    RectangleShape BattleCard7(Vector2f(120.f, 168.f));

    outpost1.move(265, 530);
    outpost2.move(448, 530);
    BattleCard1.move(631, 482);
    BattleCard2.move(766, 482);
    BattleCard3.move(901, 482);
    BattleCard4.move(1036, 482);
    BattleCard5.move(1171, 482);
    BattleCard6.move(1306, 482);
    BattleCard7.move(1441, 482);

    outpost1.setFillColor(Color(175, 180, 240));
    outpost2.setFillColor(Color(175, 180, 240));
    BattleCard1.setFillColor(Color(175, 180, 240));
    BattleCard2.setFillColor(Color(175, 180, 240));
    BattleCard3.setFillColor(Color(175, 180, 240));
    BattleCard4.setFillColor(Color(175, 180, 240));
    BattleCard5.setFillColor(Color(175, 180, 240));
    BattleCard6.setFillColor(Color(175, 180, 240));
    BattleCard7.setFillColor(Color(175, 180, 240));

    RectangleShape additionalMarket(Vector2f(120.f, 168.f));
    RectangleShape market1(Vector2f(120.f, 168.f));
    RectangleShape market2(Vector2f(120.f, 168.f));
    RectangleShape market3(Vector2f(120.f, 168.f));
    RectangleShape market4(Vector2f(120.f, 168.f));
    RectangleShape market5(Vector2f(120.f, 168.f));
    RectangleShape mainDeck(Vector2f(160.f, 120.f));

    additionalMarket.move(265, 294);
    market1.move(400, 294);
    market2.move(535, 294);
    market3.move(670, 294);
    market4.move(805, 294);
    market5.move(940, 294);
    mainDeck.move(1075, 318);

    additionalMarket.setFillColor(Color(175, 180, 240));
    market1.setFillColor(Color(175, 180, 240));
    market2.setFillColor(Color(175, 180, 240));
    market3.setFillColor(Color(175, 180, 240));
    market4.setFillColor(Color(175, 180, 240));
    market5.setFillColor(Color(175, 180, 240));
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
    RectangleShape enemyBattleCard1(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard2(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard3(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard4(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard5(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard6(Vector2f(120.f, 168.f));
    RectangleShape enemyBattleCard7(Vector2f(120.f, 168.f));

    enemyOutpost1.move(265, 154);
    enemyOutpost2.move(448, 154);
    enemyBattleCard1.move(631, 106);
    enemyBattleCard2.move(766, 106);
    enemyBattleCard3.move(901, 106);
    enemyBattleCard4.move(1036, 106);
    enemyBattleCard5.move(1171, 106);
    enemyBattleCard6.move(1306, 106);
    enemyBattleCard7.move(1441, 106);

    enemyOutpost1.setFillColor(Color(175, 180, 240));
    enemyOutpost2.setFillColor(Color(175, 180, 240));
    enemyBattleCard1.setFillColor(Color(175, 180, 240));
    enemyBattleCard2.setFillColor(Color(175, 180, 240));
    enemyBattleCard3.setFillColor(Color(175, 180, 240));
    enemyBattleCard4.setFillColor(Color(175, 180, 240));
    enemyBattleCard5.setFillColor(Color(175, 180, 240));
    enemyBattleCard6.setFillColor(Color(175, 180, 240));
    enemyBattleCard7.setFillColor(Color(175, 180, 240));

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
        window.draw(handCard1);
        window.draw(handCard2);
        window.draw(handCard3);
        window.draw(handCard4);
        window.draw(handCard5);
        window.draw(playerOneDeck);
        window.draw(playerOneDiscard);

        window.draw(outpost1);
        window.draw(outpost2);
        window.draw(BattleCard1);
        window.draw(BattleCard2);
        window.draw(BattleCard3);
        window.draw(BattleCard4);
        window.draw(BattleCard5);
        window.draw(BattleCard6);
        window.draw(BattleCard7);

        window.draw(additionalMarket);
        window.draw(market1);
        window.draw(market2);
        window.draw(market3);
        window.draw(market4);
        window.draw(market5);
        window.draw(mainDeck);

        window.draw(endTurnButton);

        window.draw(enemyOutpost1);
        window.draw(enemyOutpost2);
        window.draw(enemyBattleCard1);
        window.draw(enemyBattleCard2);
        window.draw(enemyBattleCard3);
        window.draw(enemyBattleCard4);
        window.draw(enemyBattleCard5);
        window.draw(enemyBattleCard6);
        window.draw(enemyBattleCard7);

        window.draw(enemyImage);
        window.draw(enemyDeck);
        window.draw(history);
        window.draw(giveUp);

		window.display();
	}
 
	return 0;
}
