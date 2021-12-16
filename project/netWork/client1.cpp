#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>

#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
#include "../data/netWorkUtils.hpp"

#define CL "CLIENT: "
#define ST "STATUS: "
#define MAX_BUFF 1024
#define DEFAULT_PORT 8080

using namespace std;
int main(int argc, char* argv[]) {
    sf::TcpSocket client_socket;
    cout << CL << "Сокет создан!" << endl;
    sf::Time timeout = sf::seconds(45.f);
    sf::Socket::Status status = client_socket.connect("127.0.0.1", DEFAULT_PORT, timeout);
    if (status != sf::Socket::Done) {
        cout << CL << "Произошла ошибка соединения с сервером" << endl;
    } else {
        cout << CL << "Подключился к серверу " << client_socket.getRemoteAddress()
                << " На порту " << client_socket.getRemotePort() << endl;
    }

    Card card(111);
    int net_status = 0;
    sf::Packet packet;
    DeckCard player_deck;

    if (client_socket.receive(packet) != sf::Socket::Done) {  //Получен статус на начало игры
        cout << " Ne udalos" << endl;
        return 1;
    }
    if (net_status == START_GAME) {
        packet >> net_status >> card; 
        player_deck.append(card);
    }
    
    if (net_status == START_GAME) {
        for (int i = 0; i < 9; i++) {
            if (client_socket.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalos" << endl;
                return 1;
            }
            packet >> net_status >> card; 
            //cout << net_status << endl;
            card.TargetCard = PLAYER_DECK;
            player_deck.append(card); // наполняем вектор колоды
        }
    }
    cout << "Получил " << player_deck.getSize() << " карт" << endl;

    if (client_socket.receive(packet) != sf::Socket::Done) { // Ожидаем статус YOUR_TURN или WAIT
        cout << " Ne udaloss" << endl;
        return 1;
    }

    Card card_a(141);
    Card card_b(142);
    Card card_c(133);
    Card buff_card(111);

    int action_status = NOTHING;
    int number_card = 0;
    int pos = -1;

    packet >> net_status;
    cout << ST << net_status << endl;
    int coins_per_turn = 0;

    while (true) {
        switch (net_status) {
        case YOUR_TURN: 
            cout << "My turn" << endl;
            coins_per_turn = 0;

            while(true) { // Todo Таймер на 45 сек
                 /*
                Вставьте свою реализацию действий сюда
                */

                /*
                Здесь же должны покупаться карты
                */

                //Todo Механику покупки карты
                Card purchasable_card(111);
                if (coins_per_turn >= purchasable_card.CostCard) {
                    coins_per_turn -= purchasable_card.CostCard;
                    purchasable_card.TargetCard = PLAYER_DECK_DISCARD;
                }

                cin >> action_status >> number_card >> pos;
                Card buff_card(number_card);

                if (action_status == PLAY_CARD && buff_card.CoinCard != 0) {
                    coins_per_turn += buff_card.CoinCard;
                    cout << "$$ Получено монет с розыгрыша= " << buff_card.CoinCard
                        << "$$ Монет на текущий момент = " << coins_per_turn << endl;
                }

                packet.clear();
                packet << action_status << buff_card << pos;

                cout << " Пытаюсь отправить..." << endl;
                if (client_socket.send(packet) != sf::Socket::Done) { // Отправляем Action на сервер
                    cout << " Ne udalos1" << endl;
                    return 1;
                }
                cout << "Отправлено действие" << endl;

                if (action_status == UTIL_CARD && buff_card.UtRule.ut_CoinCard != 0) {
                    coins_per_turn += buff_card.UtRule.ut_CoinCard;
                    cout << "$$ Получено монет при удалении = " << buff_card.UtRule.ut_CoinCard
                        << " $$ Монет на текущий момент = " << coins_per_turn << endl;
                }

                if (action_status == BUY_CARD) { // Если карту купили, то нужно принять от сервера какую нужно выложить в свободный слот маркета
                    if (client_socket.receive(packet) != sf::Socket::Done) {
                        cout << " Ne udalos1" << endl;
                        return 1;
                    }
                    packet >> action_status >> buff_card;
                    if (action_status == GET_CARD) {
                        /*
                        Добавьте карту в свободный слот маркета по-братски
                        */
                    }
                }

                if (action_status == END_TURN) {
                    net_status = WAIT;
                    break;
                }
            }
            break;

        case WAIT: 
            cout << "wait" << endl;
            if (client_socket.receive(packet) != sf::Socket::Done) { // Ожидаем запрос на отрисовку, либо о начале нашего хода
                cout << " Ne udalos2" << endl;
                return 1;
            }
            packet >> net_status;
            cout << ST << net_status << endl;

            if (net_status == YOUR_TURN) {
                break;
            }

            if (net_status == OPPONENT_TURN) {
                packet >> action_status >> buff_card;
                packet >> pos; // Что сделал оппонент, с какой картой и в каком слоте руки/маркета она раньше была
                /*
                Используйте полученные данные, чтобы отобразить действие оппонента
                */
               cout << action_status << " -- " << buff_card.nameCard << " -- " << pos << endl;
               net_status = WAIT;
            }
            break;

        case WIN: cout << "CONGRATULATIONS!" << endl; return 1;
        case LOSE: cout << "Maybe next time..." << endl; return 2;
        default: cout << "DEFAULT" << endl; break;
        }
        cout << net_status << endl;
    }


    return 0;
}