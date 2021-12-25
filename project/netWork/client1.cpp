#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <thread>
#include <chrono>
 

#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
#include "../data/ClassMainDeck.hpp"
#include "../data/graphicsUtils.hpp"
#include "../data/netWorkUtils.hpp"

#define CL "CLIENT: "
#define ST "STATUS: "
#define MAX_BUFF 1024
#define DEFAULT_PORT 8080

using namespace std;




int main(int argc, char* argv[]) {

    chrono::steady_clock sc;   // create an object of `steady_clock` class
    
    sf::TcpSocket client_socket;
    cout << CL << "Сокет создан!" << endl;
    sf::Time timeout = sf::seconds(45.f);
    sf::Socket::Status status = client_socket.connect("127.0.0.1", DEFAULT_PORT, timeout);
    //___________________________________________________________________________________________________________________________________________
    // Объявления переменных для графики
    Card empty_card(0);
    sf::ContextSettings settings;
    sf::Texture empty_texture;
    Texture save;
    empty_texture.loadFromFile("../include/images/0.jpg");
    settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1600, 900), "Star Realms", sf::Style::Default, settings);

	RectangleShape heroImage(Vector2f(220.f, 308.f));
    RectangleShape heroStats(Vector2f(320.f, 160.f));

    std::vector <RectangleShape> PlayerHand;
    for (int i = 0; i < 5; i++){
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

    /*heroImage.setFillColor(Color::Transparent);*/
    heroStats.setFillColor(Color::Transparent);

    for (int i=0;i<PlayerHand.size();i++){
        PlayerHand[i].setFillColor(Color(175, 180, 240));
    }

    playerOneDeck.setFillColor(Color::Transparent);
    playerOneDiscard.setFillColor(Color::Transparent);


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

    outpost1.setFillColor(Color::Transparent);
    outpost2.setFillColor(Color::Transparent);
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

    additionalMarket.setFillColor(Color::Transparent);

    /*for (int i=0;i<market.size();i++){
        market[i].setFillColor(Color::Transparent);
    }*/

    //mainDeck.setFillColor(Color::Transparent);


	
    RectangleShape endTurnButton(Vector2f(130.f, 90.f));
    endTurnButton.move(Vector2f(1380.f, 294.f));
	endTurnButton.setFillColor(Color::White);
    sf::Texture endTurn_start;
    sf::Texture endTurn_end;
    endTurn_start.loadFromFile("../include/images/end_turn_start.jpg");
    endTurn_end.loadFromFile("../include/images/end_turn_end.jpg");
    sf::Texture endTurn = endTurn_start;
    endTurnButton.setTexture(&endTurn);
    RectangleShape Discard_rec(Vector2f(150.f, 210.f));
    Discard_rec.move(1380.f, 400.f);
    //Discard_rec.setFillColor(Color(175, 180, 240));
    RectangleShape enemyOutpost1(Vector2f(168.f, 120.f));
    RectangleShape enemyOutpost2(Vector2f(168.f, 120.f));

    std::vector <RectangleShape> EnemyBattleCards;
    for (int i = 0; i < 5; i++){
        EnemyBattleCards.push_back(RectangleShape(Vector2f(120.f, 168.f)));
    }

    enemyOutpost1.move(265, 154);
    enemyOutpost2.move(448, 154);
    EnemyBattleCards[0].move(631, 106);
    EnemyBattleCards[1].move(766, 106);
    EnemyBattleCards[2].move(901, 106);
    EnemyBattleCards[3].move(1036, 106);
    EnemyBattleCards[4].move(1171, 106);
    for (int i=0;i<EnemyBattleCards.size();i++){
        EnemyBattleCards[i].setFillColor(Color(175, 180, 240));
    }

    //enemyOutpost1.setFillColor(Color(175, 180, 240));
    //enemyOutpost2.setFillColor(Color(175, 180, 240));

    RectangleShape enemyImage(Vector2f(220.f, 308.f));
    RectangleShape enemyDeck(Vector2f(220.f, 90.f));
    RectangleShape history(Vector2f(220.f, 45.f));
    RectangleShape giveUp(Vector2f(220.f, 45.f));

    enemyImage.move(20, 20);
    enemyDeck.move(260, 20);
    history.move(1120, 20);
    giveUp.move(1360, 20);

    //enemyImage.setFillColor(Color(175, 180, 240));
    enemyDeck.setFillColor(Color::Transparent);
    //history.setFillColor(Color(175, 180, 240));
    //giveUp.setFillColor(Color::Transparent);





    ///////ЧИТАТЬ КОД СЛЕДУЕТ НАЧИНАЯ С ЭТОЙ СТРОКИ(ну и почитайте функции пожожда)
    // int hp=0;
    // int damage=0;
    // int coin=0;
    sf::Sprite ShowBIG(empty_texture);
    ShowBIG.setScale(0.7,0.7);
    ShowBIG.move(Vector2f(20.f, 330.f));

    Texture cross;
    cross.loadFromFile("../include/images/cross.png");
    sf::Sprite Cross(cross);
    Cross.setScale(0.5,0.5);
    Cross.move(Vector2f(20.f, 330.f));

    sf::Texture background_first;
    sf::Texture background_sec;
    sf::Texture button_history;
    sf::Texture button_giveup;
    sf::Texture coin_texture;
    background_first.loadFromFile("../include/images/background_first.jpg");
    background_sec.loadFromFile("../include/images/background_sec.jpg");
    button_history.loadFromFile("../include/images/History_button.png");
    button_giveup.loadFromFile("../include/images/Give_up_button.png");
    coin_texture.loadFromFile("../include/images/coin.png");
    IntRect backgr_rect(0, 0, 100000, 10000);
    sf::Sprite BackGroundFirst(background_first);
    sf::Sprite BackGroundSec(background_sec);
    history.setTexture(&button_history);
    giveUp.setTexture(&button_giveup);
    sf::Sprite coin(coin_texture);
    coin.move(260,720);
    BackGroundFirst.setTextureRect(backgr_rect);
    BackGroundSec.setTextureRect(backgr_rect);
    sf::Texture hero_image;
    hero_image.loadFromFile("../include/images/Hero1.jpg");
    heroImage.setTexture(&hero_image);
    sf::Texture enemy_image;
    enemy_image.loadFromFile("../include/images/Hero2.jpg");
    enemyImage.setTexture(&enemy_image);
    sf::Texture backplate;
    backplate.loadFromFile("../include/images/backplate.jpg");
    mainDeck.setTexture(&backplate);
    sf::Texture discrad_texture;

    discrad_texture.loadFromFile("../include/images/backplate.jpg");
    Discard_rec.setTexture(&discrad_texture);


    Font font;
    font.loadFromFile("../include/Fonts/NesobriteScLt Regular.ttf");
    Text text("",font,20);
    text.setColor(Color::Black);
    text.setStyle(Text::Bold);
    text.setPosition(1410.f,320.f);
    Text text_my_hp("", font, 30);
    text_my_hp.setColor(Color::Green);
    text_my_hp.setStyle(Text::Bold);
    text_my_hp.setPosition(20.f,520.f);

    Text text_enemy_hp("", font, 30);
    text_enemy_hp.setColor(Color::Black);
    text_enemy_hp.setStyle(Text::Bold);
    text_enemy_hp.setPosition(20.f,340.f);

    Text coin_count("",font,30);
    coin_count.setColor(Color::Black);
    coin_count.setStyle(Text::Bold);
    coin_count.setPosition(275,730);

    Text damage("",font,50);
    damage.setColor(Color::Red);
    damage.setStyle(Text::Bold);


    DeckCard player_hand(5,1);
    DeckCard battle_cards(5,1);
    DeckCard market_cards(5,1);
    DeckCard enemy_battle_cards(5,1);
    Discard d;
    for (int i=0;i<BattleCards.size();i++){
        battle_cards.deck_vec[i]=empty_card;
    }
    connect_logic_to_graph(BattleCards,battle_cards);
    connect_logic_to_graph(PlayerHand,player_hand);
    connect_logic_to_graph(EnemyBattleCards, enemy_battle_cards);
    MainDeck Deck(0,'m');
    Deck.shuffle_deck();
    //MainDeck MarketDeck(6,'m');
    //Deck.giveHand(player_hand,d,5,discrad_texture);
    //MarketDeck.giveHand(market_cards,d,5,discrad_texture);
    //connect_logic_to_graph(PlayerHand,player_hand);
    //connect_logic_to_graph(market,market_cards);

    int flag_draw = 0;
	//while (window.isOpen()){
        Event event;
		//while (window.pollEvent(event)){
            
    //'_________________________________________________________'

            Card buff_card(111);
            int net_status = 0;
            sf::Packet packet;
            int pos = 0;
            int buff_card_id = 0;
            int less_card = 0;
            //DeckCard player_deck(5,1);

            // if (client_socket.receive(packet) != sf::Socket::Done) {  //Получен статус на начало игры
            //     cout << " Ne udalos" << endl;
            //     //return 1;
            // }
            int rec=0;
            for (int i = 0; i < 5; i++){ // Получаем 5 карт в маркет
                client_socket.receive(packet);
                packet >> net_status >> buff_card_id;
                buff_card=return_card(buff_card_id);
                packet >> pos;
                market_cards.deck_vec[i] = buff_card;
                market_cards.deck_vec[i].texture.loadFromFile(buff_card.path_file_img);
                cout << "получено в маркет - " << market_cards.deck_vec[i].getId() << endl;
            }
            connect_logic_to_graph(market, market_cards);
            //_____________________________________________ Идет отрисовка полученного в начале игры на маркет
            /*window.clear(Color::White);
            window.draw(BackGround);
            draw_rec_vector(PlayerHand,window);
            window.draw(heroImage);
            window.draw(heroStats);
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
            window.draw(text);
            window.draw(text_my_hp);
            window.draw(text_enemy_hp);
            window.display();*/
            draw(window,BackGroundFirst,heroImage,heroStats,PlayerHand,playerOneDeck,playerOneDiscard,
            BattleCards,ShowBIG,market,mainDeck,endTurnButton,EnemyBattleCards,
            enemyImage,enemyDeck,history,giveUp,Discard_rec,text,
            text_my_hp,text_enemy_hp,heroImage,heroStats,flag_draw,mainDeck);
            //________________________________________________________
            rec = client_socket.receive(packet);
            if (rec != sf::Socket::Done) {
                cout << " Ne udalos" << endl;
            }
            if (net_status == START_GAME) {
                packet >> net_status >> buff_card_id;
                buff_card = return_card(buff_card_id);
                buff_card.texture.loadFromFile(buff_card.path_file_img);
                //player_deck.append(card);
                Deck.append(buff_card);
            }

            if (net_status == START_GAME) {
                for (int i = 0; i < 9; i++) {
                    rec=client_socket.receive(packet);
                    if (rec != sf::Socket::Done) {
                        cout << " Ne udalos" << endl;
                        //return 1;
                    }
                    packet >> net_status >> buff_card_id;
                    buff_card=return_card(buff_card_id);
                    buff_card.texture.loadFromFile(buff_card.path_file_img);
                    //cout << net_status << endl;
                    buff_card.TargetCard = PLAYER_DECK;
                    //player_deck.append(card); // наполняем вектор колоды
                    Deck.append(buff_card);
                }
            }
            cout << "Получил " << Deck.getSize() << " карт" << endl;
            for (int i = 0; i < 10 ;i++) {
                cout << Deck(i).getId() << ", ";
            }
            rec = client_socket.receive(packet);
            if (rec != sf::Socket::Done) { // Ожидаем статус YOUR_TURN или WAIT
                cout << " Ne udaloss" << endl;
            }

            //Card buff_card(111);
            int action_status = NOTHING;
            int number_card = 0;
            pos = -1;

            packet >> net_status;
            cout << ST << net_status << endl;
            int coins_per_turn = 0;
            int my_hp = 30;
            int enemy_hp = 30;
            int heal_per_turn = 0;
            int dmg_per_turn = 0;

            packet.clear();
            packet << NOTHING;
            client_socket.setBlocking(false);

            chrono::steady_clock scc;
            std::chrono::_V2::steady_clock::time_point start; 
            while (true) {
                switch (net_status) {
                case YOUR_TURN:
                {   swap(hero_image,enemy_image);
                    coins_per_turn = 100;
                    cout << "My turn";
                    endTurn=endTurn_start;
                    Deck.giveHand(player_hand, d, (5 - less_card), discrad_texture);
                    less_card = 0;
                    connect_logic_to_graph(PlayerHand, player_hand);

                    // ###############################################
                   
                    while(true) { // Todo Таймер на 45 сек
                        action_status = NOTHING;
                        while (window.pollEvent(event)){
                            if (event.type==Event::MouseMoved){
                                continue;
                            }

                        
                        window.clear(Color::White);
                        window.draw(BackGroundFirst);
                        window.draw(heroImage);
                        window.draw(heroStats);
                        draw_rec_vector(PlayerHand,window);
                        window.draw(playerOneDeck);
                        window.draw(playerOneDiscard);

                        window.draw(coin);
                        draw_rec_vector(BattleCards,window);
                        text_my_hp.setString("HP:"+to_string(my_hp));
                        text_enemy_hp.setString("HP:"+to_string(enemy_hp));
                        coin_count.setString(to_string(coins_per_turn));
                        window.draw(text_my_hp);
                        window.draw(coin_count);
                        window.draw(text_enemy_hp);
                        window.draw(text);
                        if (flag_draw == 1){
                            window.draw(ShowBIG);
                        }
                        if (flag_draw == 2){
                            window.draw(ShowBIG);
                            window.draw(Cross);
                        }
                        draw_rec_vector(market,window);
                    
                        window.draw(mainDeck);

                        window.draw(endTurnButton);

                        draw_rec_vector(EnemyBattleCards,window);
                        window.draw(enemyImage);
                        window.draw(enemyDeck);
                        window.draw(history);
                        window.draw(giveUp);
                        window.draw(Discard_rec);

                        window.display();
                       
                        if (event.type == Event::Closed)
                            window.close();

                        if (event.type == Event::MouseButtonPressed){
                            
                            ShowBIG.setTexture(empty_texture);
                            IntRect sprite_rect(0, 0, 300, 420);
                            ShowBIG.setTextureRect(sprite_rect);
                            flag_draw = 0;
                            
                            if (event.mouseButton.button == sf::Mouse::Left) { // Розыгрыш карты
                                int pos = check_if_clicked(PlayerHand, event, player_hand, window);
                                cout << "Message LKM" << endl;
                                if (pos!=-1) {

                                    action_status = PLAY_CARD;
                                    packet.clear();
                                    buff_card_id = player_hand.deck_vec[pos].getId();

                                    buff_card = return_card(buff_card_id);
                                    packet << action_status << buff_card_id << pos;

                                    move_card(PlayerHand, player_hand, BattleCards, battle_cards, pos);
                                    break;
                                }
                                //EndTurn
                                if (endTurnButton.getGlobalBounds().contains(   
                                        window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                                    
                                    
                                    packet.clear();
                                    action_status = END_TURN;
                                    packet << action_status;
                                    for (int i = 0; i < PlayerHand.size(); i++){
                                        if (player_hand.deck_vec[i].getId() != 0){
                                            d.get_card(PlayerHand,player_hand,i,discrad_texture);
                                        }
                                    }
                                    for (int i = 0; i < BattleCards.size(); i++){
                                        if (battle_cards.deck_vec[i].getId() != 0){
                                            d.get_card(BattleCards,battle_cards,i,discrad_texture);
                                        }
   
                                    }
                                    for (int i=0;i<EnemyBattleCards.size();i++){
                                        enemy_battle_cards.deck_vec[i]=empty_card;
                                    }
                                    connect_logic_to_graph(EnemyBattleCards,enemy_battle_cards);


                                    connect_logic_to_graph(PlayerHand,player_hand);
                                    break;
                                }

                                //Покупка с Маркета
                                pos = check_if_clicked(market, event, market_cards, window); 
                                if (pos != -1) {
                                    if (market_cards.deck_vec[pos].CostCard <= coins_per_turn) {
                                        cout << "было " << coins_per_turn << endl;
                                        coins_per_turn -= market_cards.deck_vec[pos].CostCard;
                                        cout << "Стало" << coins_per_turn << endl;

                                        packet.clear();
                                        buff_card_id = market_cards.deck_vec[pos].getId();
                                        action_status = BUY_CARD;
                                        packet << action_status << buff_card_id << pos;
                                        cout << "Message 10" << endl;

                                        d.get_card(market,market_cards,pos,discrad_texture);
                                        connect_logic_to_graph(market,market_cards);

                                        market_cards.deck_vec[pos]=buff_card;
                                        connect_logic_to_graph(market,market_cards);
                                        
                                        break;
                                    } else { cout << "Not enought money " << endl; }
                                }
                            }
                            // auto end = scc.now();
                            // auto time_span = static_cast<chrono::duration<double>>(end - start);
                            // cout<<"Operation took: "<< time_span.count()<<" seconds !!!" << endl;


                            if (event.mouseButton.button == sf::Mouse::Middle){
                                //Добавить  просмотр вывода карт противника
                                int pos = check_if_clicked(PlayerHand,event,player_hand,window);
                                if (pos!=-1) {
                                    flag_draw = 1;
                                    ShowBIG.setTexture(*(player_hand.deck_vec[pos].GetTexture()));
                                }
                                pos = check_if_clicked(BattleCards,event,battle_cards,window);
                                if (pos!=-1) {
                                    flag_draw = 1;
                                    ShowBIG.setTexture(*(battle_cards.deck_vec[pos].GetTexture()));
                                }
                                pos = check_if_clicked(market,event,market_cards,window);
                                if (pos!=-1) {
                                    flag_draw=1;
                                    ShowBIG.setTexture(*(market_cards.deck_vec[pos].GetTexture()));
                                }
                                pos = check_if_clicked(EnemyBattleCards,event,enemy_battle_cards,window);
                                if (pos!=-1) {
                                    flag_draw=1;
                                    ShowBIG.setTexture(*(enemy_battle_cards.deck_vec[pos].GetTexture()));
                                }
                            }
                            if (event.mouseButton.button == sf::Mouse::Right){
                                pos=check_if_clicked(PlayerHand,event,player_hand,window);
                                if (pos!=-1){
                                    save=*PlayerHand[pos].getTexture();
                                    ShowBIG.setTexture(save);
                                    buff_card = return_card(player_hand.deck_vec[pos].getId());
                                    packet.clear();
                                    action_status = UTIL_CARD;
                                    packet << UTIL_CARD <<  player_hand.deck_vec[pos].getId() << pos;
                                    player_hand.deck_vec[pos]=empty_card;
                                    connect_logic_to_graph(PlayerHand,player_hand);
                                    flag_draw = 2;
                                    break;
                                }
                            }
                        }
                    }
                        //cout << "Message 12" << endl;
                        //######################################

                        // auto start = scc.now();
                            
                        //cout << " Пытаюсь отправить... " << action_status << endl;
                        if (action_status == NOTHING) {
                            //cout << "NOTHING. line 515" << endl;
                            continue;
                        }
                        if (client_socket.send(packet) != sf::Socket::Done) { // Отправляем Action на сервер
                            
                            cout << " Ne udalos1" << endl;
                        }

    
                        start = scc.now();
                        cout << "Message 1" << endl;

                        if (action_status == END_TURN) {
                            //net_status = WAIT;
                            rec = client_socket.receive(packet);

                            while (rec == sf::Socket::NotReady){
                                rec = client_socket.receive(packet);
                                usleep(100000);
                            }
                            cout << "Получен конец хода" << endl;
                            if (rec != sf::Socket::Done) {
                                cout << " Ne udalos1" << endl;
                                return 1;
                            }
                            packet >> net_status >> my_hp >> enemy_hp >> heal_per_turn >> dmg_per_turn;
                            if (net_status == WAIT) {
                                cout << "orghu4hihnu4bh4u4o5h38kchg45hg4h4o4jhoj5ohj4o" << endl;
                            }
                            action_status = NOTHING;
                            break;
                        }
                        cout << "Message 2" << endl;

                        if (action_status == PLAY_CARD && buff_card.CoinCard != 0) {
                            coins_per_turn += buff_card.CoinCard;
                            cout << "$$ Получено монет с розыгрыша= " << buff_card.CoinCard
                                << "$$ Монет на текущий момент = " << coins_per_turn << endl;
                        }
                        //cout << "Message 14" << endl;

                        if (action_status == UTIL_CARD && buff_card.UtRule.ut_CoinCard != 0) {
                            coins_per_turn += buff_card.UtRule.ut_CoinCard;
                            cout << "$$ Получено монет при удалении = " << buff_card.UtRule.ut_CoinCard
                                << " $$ Монет на текущий момент = " << coins_per_turn << endl;
                        }
                        //cout << "Message 15" << endl;

                        if (action_status == BUY_CARD) { // Если карту купили, то нужно принять от сервера какую нужно выложить в свободный слот маркета
                            cout << "Жду карту от сервера" << endl;
                            rec = client_socket.receive(packet);

                            while (rec == sf::Socket::NotReady){
                                rec = client_socket.receive(packet);
                                usleep(100000);
                            }

                            if (rec != sf::Socket::Done) {
                                cout << " Ne udalos1" << endl;
                                return 1;
                            }

                            packet >> action_status;
                            packet >> buff_card_id;
                            buff_card = return_card(buff_card_id);
                            buff_card.texture.loadFromFile(buff_card.path_file_img);
                            packet >> pos;
                            cout << " Получена карта, pos = " << pos << buff_card.getId() << endl;
                            if (action_status == GET_CARD) {
                                market_cards.deck_vec[pos] = buff_card;
                                connect_logic_to_graph(market, market_cards);
                                cout << " Добавлено в маркет " << endl;
                            }
                        }
                       

                        auto end = scc.now(); 
                        auto time_span = static_cast<chrono::duration<double>>(end - start);
                        cout<< "Main loop took: "<< time_span.count()<<" seconds !!!" << endl;

                        action_status = NOTHING;
                    }
                    break; //Выход из кейса YOUR_TURN
                }

                case WAIT: 
                {   swap(hero_image,enemy_image);
                    endTurn = endTurn_end;
                    cout << "wait" << endl;
                    //window.clear(Color::Blue);
                    //connect_logic_to_graph(PlayerHand,player_hand);
                    window.clear();
                    window.draw(BackGroundSec);
                    window.draw(heroImage);
                    window.draw(heroStats);
                    draw_rec_vector(PlayerHand,window);
                    window.draw(playerOneDeck);
                    window.draw(playerOneDiscard);

                    //window.draw(outpost1);
                    //window.draw(outpost2);
                    draw_rec_vector(BattleCards,window);
                    if (flag_draw == 1 ){
                        window.draw(ShowBIG);
                    }
                    if (flag_draw == 2){
                        window.draw(ShowBIG);
                        window.draw(Cross);
                    }
                    window.draw(additionalMarket);
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
                    text_my_hp.setString("HP:"+to_string(my_hp));
                    text_enemy_hp.setString("HP:"+to_string(enemy_hp));
                    coin_count.setString(to_string(coins_per_turn));
                    window.draw(coin);
                    window.draw(text);
                    window.draw(text_my_hp);
                    window.draw(text_enemy_hp);
                    window.draw(coin_count);
                    window.display();

                    rec = client_socket.receive(packet);
                    
                    while (rec == sf::Socket::NotReady){
                        rec = client_socket.receive(packet);

                        sleep(1);
                        window.display();
                    }
                    if (rec  != sf::Socket::Done) { // Ожидаем запрос на отрисовку, либо о начале нашего хода
                        cout << " Ne udalos2" << endl;
                    }

                    packet >> net_status;
                    cout << "Получено: " << ST << net_status << endl;

                    /*if (net_status != YOUR_TURN && net_status != OPPONENT_TURN) {
                        //cout << "Бред получили";
                        return 1;
                    }*/
                    
                    if (net_status == YOUR_TURN) {
                        packet >> my_hp >> enemy_hp >> less_card;
                        action_status = NOTHING;
                        cout << "Смена хода " << endl;
                        break;
                    }

                    if (net_status == OPPONENT_TURN) {

                        packet >> action_status;
                        if (action_status == NOTHING) {
                            net_status = WAIT;
                            break;
                        }
                        packet >> buff_card_id;
                        buff_card = return_card(buff_card_id);
                        buff_card.texture.loadFromFile(buff_card.path_file_img);
                        packet >> pos; // Что сделал оппонент, с какой картой и в каком слоте руки/маркета она раньше была
                        cout << "action_status = " << action_status << "ID = " << buff_card_id << "pos = " << pos << endl;
                        /*
                        Используйте полученные данные, чтобы отобразить действие оппонента
                        */
                        if (action_status == PLAY_CARD) {//Карты оппонента пустые и отображаются карты из маркета ,Пофиксить
                            enemy_battle_cards.deck_vec[pos]=buff_card;
                            EnemyBattleCards[pos].setTexture(&enemy_battle_cards.deck_vec[pos].texture);
                            enemy_battle_cards.avaliable[pos]=1;
                            cout<<"GOT CARD";

                        }

                        if (action_status == UTIL_CARD) {
                            save = buff_card.texture;
                            ShowBIG.setTexture(save);
                            flag_draw = 2 ;

                        }

                        if (action_status == BUY_CARD) { // Новую карту в маркете тоже нужно отрисовать

                            market_cards.deck_vec[pos] = empty_card;
                            connect_logic_to_graph(market, market_cards);
        
                            rec = client_socket.receive(packet);
                            while (rec==sf::Socket::NotReady){
                                rec = client_socket.receive(packet);
                                usleep(100000);
                            }

                            if (rec != sf::Socket::Done) {
                                cout << " Ne udalos1" << endl;
                                return 1;
                            }
                            
                            packet >> action_status;
                            packet >> buff_card_id;
                            buff_card = return_card(buff_card_id);
                            buff_card.texture.loadFromFile(buff_card.path_file_img);
                            packet >> pos;
                            //cout << " Получена карта макета, pos = " << pos << buff_card.getId() << endl;

                            if (action_status == GET_CARD) {
                                cout << "Получена карта на отрисовку - " << buff_card.nameCard << endl;
                                market_cards.deck_vec[pos] = buff_card;
                                connect_logic_to_graph(market,market_cards);
                            }
                        }
                        action_status = NOTHING;
                        net_status = WAIT;
                    }
                    break;
                }

                case WIN: 
                {   
                    cout << "CONGRATULATIONS!" << endl;  
                    Sprite victory;
                    Texture vict;
                    vict.loadFromFile("../include/images/victory_screen.png");
                    victory.setTexture(vict);
                    victory.setPosition(window.getPosition().x+100,window.getPosition().y);
                    window.draw(victory);
                    window.display();
                    while (window.pollEvent(event)){
                        if (event.type == Event::Closed)
                            window.close();
                        else{
                            continue;
                        }
                        
                    }
                    break;
                }
                case LOSE:
                {
                    cout << "Maybe next time..." << endl; 
                    Sprite defeat;
                    Texture def;
                    def.loadFromFile("../include/images/defeat_screen.png");
                    defeat.setPosition(window.getPosition().x+300,window.getPosition().y);
                    defeat.setTexture(def);
                    window.draw(defeat);
                    window.display();
                    while (window.pollEvent(event)){
                        if (event.type == Event::Closed)
                            window.close();
                        else{
                            continue;
                        }
                    }
                   

                }
                default: cout << "DEFAULT" << endl; break;
                }
                cout << net_status << endl;
            }

    return 0;
}