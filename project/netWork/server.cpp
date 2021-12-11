#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>

#include "../data/ClassCard.hpp"
#include "../data/netWorkUtils.hpp"

#define SER "SERVER: "
#define MAX_BUFF 1024
#define DEFAULT_PORT 8093

using namespace std;


int main(int argc, char* argv[]) {
    srand(time(NULL));
    sf::TcpListener listener;
    cout << SER << "Сокет создан!" << endl;
    if (listener.listen(DEFAULT_PORT) != sf::Socket::Done) {
        cout << SER << "Ошибка при создании прослушивающего канала" << endl;
    }
    sf::TcpSocket player_1;
    if (listener.accept(player_1) != sf::Socket::Done) {
        cout << SER << "Ошибка при подключении клиента" << endl;
    }
    cout << SER << "Ура, у меня гости" << endl;
    cout << SER << "Жду второго" << endl;

    sf::TcpSocket player_2;
    if (listener.accept(player_2) != sf::Socket::Done) {
        cout << SER << "Ошибка при подключении клиента №2" << endl;
    }
    cout << SER << "Все на месте" << endl;

    char buffer[MAX_BUFF];

    vector<int> deck;
    for (size_t i = 0; i < 10; i ++) {
        deck.push_back(rand() % 100);
    }

    cout << "Создаю карту" << endl;
    Card a(111);
    Card b(112);
    cout << "Создал" << endl;
    sf::Packet packet;
    cout << "Записываю" << endl;

    int net_status = START_GAME;
    packet << net_status << a;

    cout << "Записал" << endl;
    cout << "Отправляю" << endl;

    for (int i = 0; i < 8; i++) {
        if (player_1.send(packet)!= sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }
        if (player_2.send(packet)!= sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }
    }

    packet.clear();
    packet << net_status << b;

    for (int i = 0; i < 2; i++) {
        if (player_1.send(packet)!= sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }
        if (player_2.send(packet)!= sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }
    }
    packet.clear();
    packet << YOUR_TURN;
    bool player_1_active = true;

    if (player_1.send(packet) != sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }

    packet.clear();
    packet << WAIT;
    bool player_2_active = false;

    if (player_2.send(packet) != sf::Socket::Done) {
            cout << "не отправлено" << endl;
            return 1;
        }

    // if (client_socket.receive(packet) != sf::Socket::Done) {
    //     cout << " Ne udalosot clienta" << endl;
    //     return 1;
    // }
    // packet >> net_status;

    int active_status = NOTHING;

    Actions buff_act;
    vector<Actions> turn_log;
    vector<vector<Actions>> battle_log;

    cout << "Жду активности от клиентов" << endl;
    while (true) {
        while (player_1_active) {
            if (player_1.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }

            packet >> buff_act.action_status;
            packet >> buff_act.action_from_card;
            packet >> buff_act.position;
            turn_log.push_back(buff_act);

            if (active_status == BUY_CARD) {
                packet.clear();
                packet << GET_CARD << b;  // << market_top_card;  Добавьте верхнюю карту из деки рынка
                if (player_1.receive(packet) != sf::Socket::Done) {
                    cout << " Ne udalosot clienta" << endl;
                    return 1;
                }
            }

            if (active_status == END_TURN) {
                player_1_active = false;
                player_2_active = true;
                break;
            }
            // cout << "nov zahod" << endl;
            // active_status = END_TURN;
        }

        for (size_t i = 0; i < turn_log.size(); i++) {
            if (turn_log.at(i).action_status == PLAY_CARD) {
                turn_log.at(i).action_from_card;
            }
        }
    }
    return 0;
}