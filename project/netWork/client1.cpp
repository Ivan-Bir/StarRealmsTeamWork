#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>

#include "../data/ClassCard.hpp"
#include "../data/ClassDeck.hpp"
#include "../data/netWorkUtils.hpp"

#define CL "CLIENT: "
#define ST "STATUS: "
#define MAX_BUFF 1024
#define DEFAULT_PORT 8093

using namespace std;
int main(int argc, char* argv[]) {
    sf::TcpSocket client_socket;
    cout << CL << "Сокет создан!" << endl;
    sf::Time timeout = sf::seconds(1.f);
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
    if (net_status == START_GAME) {
        for (int i = 0; i < 10; i++) {
            if (client_socket.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalos" << endl;
                return 1;
            }
            packet >> net_status >> card; 
            // cout << net_status << endl;
            player_deck.append(card); // наполняем вектор колоды
        }
    }
    cout << "Получил " << player_deck.getSize() << " карт" << endl;

    if (client_socket.receive(packet) != sf::Socket::Done) {
        cout << " Ne udaloss" << endl;
        return 1;
    }

    Card card_a(141);
    Card card_b(142);
    Card card_c(133);
    Card buff_card(111);
    int action_status = NOTHING;
    int pos;

    packet >> net_status;
    cout << ST << net_status << endl;

    while (true) {
        switch (net_status) {
        case YOUR_TURN: 
            cout << "My turn" << endl; 
            while(true) {
                 /*
                Вставьте свою реализацию действий сюда
                */
                packet.clear();
                packet << action_status << card_a;
                packet << END_TURN << card_a;

                cout << " Пытаюсь отправить..." << endl;
                if (client_socket.send(packet) != sf::Socket::Done) {
                    cout << " Ne udalos1" << endl;
                    return 1;
                }
                cout << "Отправлено действие" << endl;

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
            if (client_socket.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalos2" << endl;
                return 1;
            }
            packet >> net_status;

            if (net_status == YOUR_TURN) {
                break;
            }

            if (net_status == OPPONENT_TURN) {
                packet >> action_status >> buff_card;
                packet >> pos; // Что сделал оппонент, с какой картой и в каком слоте руки/маркета она раньше была
                /*
                Используйте полученные данные, чтобы отобразить действие оппонента
                */
            }
            break;

        case WIN: cout << "CONGRATULATIONS!"; break;
        case LOSE: cout << "Maybe next time..."; break;
        default: cout << "DEFAULT" << endl; break;
        }

    
       
    }
    return 0;
}