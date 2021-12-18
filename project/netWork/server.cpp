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
#define DEFAULT_PORT 8081

using namespace std;


// int GetCoins() {
//     return;
// }

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

    // vector<int> deck;
    // for (size_t i = 0; i < 10; i ++) {
    //     deck.push_back(rand() % 100);
    // }

    cout << "Создаю карту" << endl;
    Card a(111, PLAYER_HAND);
    Card b(112, PLAYER_HAND);
    Card c(113, PLAYER_HAND);

    int player_1_hp = 20;
    int player_2_hp = 20;

    int total_dmg = 0;
    int less_card = 0;
    int restore_hp = 0;
    int coins_per_turn = 0;

    cout << "Создал" << endl;
    sf::Packet packet;
    cout << "Записываю" << endl;

    int net_status = START_GAME;
    packet << net_status << a;

    cout << "Записал" << endl;
    cout << "Отправляю" << endl;

    for (int i = 0; i < 4; i++) {
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
    packet << net_status << c;

    for (int i = 0; i < 4; i++) {
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

    int active_status = NOTHING;
    int is_played_green_race = 0;
    int is_played_red_race = 0;
    int is_played_yellow_race = 0;
    int is_played_blue_race = 0;

    Actions buff_act;
    vector<Actions> turn_log;
    vector<vector<Actions>> battle_log;

    cout << "Жду активности от клиентов" << endl;
    while (true) {
        while (player_1_active) {
            cout << "Готов обработать Action" << endl;
            if (player_1.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }
            cout << "@Получил Action" << endl;

            // Принимаем пакет от активного игрока
            packet >> active_status;
            buff_act.action_status = active_status;
            packet >> buff_act.action_from_card;
            packet >> buff_act.position;
            turn_log.push_back(buff_act);

            // Инфу о действии отсылаем другому игроку на отрисовку
            cout << "Отсылаю на отрисовку" << endl;
            packet.clear();
            packet << OPPONENT_TURN << buff_act.action_status << buff_act.action_from_card << buff_act.position;
            if (player_2.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }
            cout << "Отправлено на отрисовку" << endl;

            if (buff_act.action_status == BUY_CARD) {
                cout << "##Нужно выложить карту из маркета" << endl;
                packet.clear();
                packet << GET_CARD << b;  // << market_top_card;  Добавьте верхнюю карту из деки рынка
                if (player_1.send(packet) != sf::Socket::Done) { // Отправляем обоим что выложено с рынка
                    cout << " Ne udalosot clienta 2" << endl;
                    return 1;
                }
                packet.clear();
                packet << GET_CARD << b;
                if (player_2.send(packet) != sf::Socket::Done) {
                    cout << " Ne udalosot clienta 2" << endl;
                    return 1;
                }
                cout << "##Отправил запрос маркету" << endl;
            }

            if (active_status == END_TURN) {
                cout << "Поступил END_TURN" << endl;
                player_1_active = false;
                player_2_active = true;
                break;
            }
            cout << "nov zahod" << endl;
            // active_status = END_TURN;
        }

        // Обработка действий за ход
        cout << "Конец хода первого" << endl;

        battle_log.push_back(turn_log);

        is_played_green_race = 0;
        is_played_red_race = 0;
        is_played_yellow_race = 0;
        is_played_blue_race = 0;

        for (size_t i = 0; i < turn_log.size(); i++) { // Посмотрим какие карты вообще сыгрались
            if (turn_log.at(i).action_status == PLAY_CARD) {
                switch (turn_log.at(i).action_from_card.idCard % 100 / 10) {
                    case GreenRace: is_played_green_race += 1; break;   
                    case RedRace: is_played_red_race += 1; break;    
                    case YellowRace: is_played_yellow_race += 1; break;
                    case BlueRace: is_played_blue_race += 1; break;
                    default: break;
                }
            }
        }

        for (size_t i = 0; i < turn_log.size(); i++) {
            
            if (turn_log.at(i).action_status == PLAY_CARD) {
                total_dmg += turn_log.at(i).action_from_card.DamageCard;
                less_card += turn_log.at(i).action_from_card.TextRule / 10;
                restore_hp += turn_log.at(i).action_from_card.RestoreHPCard;
                // Обработчик союзных свойств [если условие срабатывает, то остальные не проверяются]
                if (is_played_green_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == GreenRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_red_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == RedRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_yellow_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == YellowRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_blue_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == BlueRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }

            }
            if (turn_log.at(i).action_status == UTIL) {
                // Говорим колоде игрока, чтобы карта удалилась 
                // Todo....
                total_dmg += turn_log.at(i).action_from_card.UtRule.ut_DamageCard;
                less_card += turn_log.at(i).action_from_card.UtRule.ut_TextRule / 10;
                restore_hp += turn_log.at(i).action_from_card.UtRule.ut_RestoreHPCard;
            }
        }

        player_2_hp -= total_dmg;
        player_1_hp += restore_hp;
        // Не забудьте дать на less_card меньше игроку в его некст ход
        cout << "-- Урон за ход второму игроку = " << total_dmg << endl;
        cout << " ++ Восстановлено первым за ход = " << restore_hp << endl;
        cout << " << На " << less_card  << " карт меньше в раздаче в следующем ходу" << endl;

        total_dmg = 0;
        restore_hp = 0;
        less_card = 0;
        coins_per_turn = 0;
        turn_log.clear();

        if (player_2_hp <= 0) {
            packet.clear();
            packet << WIN;
            if (player_1.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }

            packet.clear();
            packet << LOSE;
            if (player_2.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }

            break;
        }
        
        // Ход второго игрока
        //
        packet.clear();
        packet << YOUR_TURN;
        if (player_2.send(packet) != sf::Socket::Done) { 
            cout << " Ne udalosot clienta 2" << endl;
            return 1;
        }

        while (player_2_active) {
            cout << "Готов обработать Action2" << endl;
            if (player_2.receive(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }
            cout << "@Получил Action" << endl;

            // Принимаем пакет от активного игрока
            packet >> active_status;
            buff_act.action_status = active_status;
            packet >> buff_act.action_from_card;
            packet >> buff_act.position;
            turn_log.push_back(buff_act);

            // Инфу о действии отсылаем другому игроку на отрисовку
            cout << "Отсылаю на отрисовку" << endl;
            packet.clear();
            packet << OPPONENT_TURN << buff_act.action_status << buff_act.action_from_card << buff_act.position;
            if (player_1.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }
            cout << "Отправлено на отрисовку" << endl;

            if (buff_act.action_status == BUY_CARD) {
                cout << "##Нужно выложить карту из маркета" << endl;
                packet.clear();
                packet << GET_CARD << b;  // << market_top_card;  Добавьте верхнюю карту из деки рынка
                if (player_2.send(packet) != sf::Socket::Done) { // Отправляем обоим что выложено с рынка
                    cout << " Ne udalosot clienta 2" << endl;
                    return 1;
                }
                packet.clear();
                packet << GET_CARD << b;
                if (player_1.send(packet) != sf::Socket::Done) {
                    cout << " Ne udalosot clienta 2" << endl;
                    return 1;
                }
                cout << "##Отправил запрос маркету" << endl;
            }

            if (active_status == END_TURN) {
                cout << "Поступил END_TURN" << endl;
                player_2_active = false;
                player_1_active = true;
                break;
            }
            cout << "nov zahod" << endl;
            // active_status = END_TURN;
        }

        // Обработка действий за ход
        cout << "Конец хода первого" << endl;

        battle_log.push_back(turn_log);

        is_played_green_race = 0;
        is_played_red_race = 0;
        is_played_yellow_race = 0;
        is_played_blue_race = 0;

        for (size_t i = 0; i < turn_log.size(); i++) { // Посмотрим какие карты вообще сыгрались
            if (turn_log.at(i).action_status == PLAY_CARD) {
                switch (turn_log.at(i).action_from_card.idCard % 100 / 10) {
                    case GreenRace: is_played_green_race += 1; break;   
                    case RedRace: is_played_red_race += 1; break;    
                    case YellowRace: is_played_yellow_race += 1; break;
                    case BlueRace: is_played_blue_race += 1; break;
                    default: break;
                }
            }
        }

        for (size_t i = 0; i < turn_log.size(); i++) {
            
            if (turn_log.at(i).action_status == PLAY_CARD) {
                total_dmg += turn_log.at(i).action_from_card.DamageCard;
                less_card += turn_log.at(i).action_from_card.TextRule / 10;
                restore_hp += turn_log.at(i).action_from_card.RestoreHPCard;
                // Обработчик союзных свойств [если условие срабатывает, то остальные не проверяются]
                if (is_played_green_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == GreenRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_red_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == RedRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_yellow_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == YellowRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }
                else if (is_played_blue_race >= 2 && turn_log.at(i).action_from_card.idCard % 100 / 10 == BlueRace) {
                    total_dmg += turn_log.at(i).action_from_card.AlRule.al_DamageCard;
                    less_card += turn_log.at(i).action_from_card.AlRule.al_TextRule / 10;
                    restore_hp += turn_log.at(i).action_from_card.AlRule.al_RestoreHPCard;
                }

            }
            if (turn_log.at(i).action_status == UTIL) {
                // Говорим колоде игрока, чтобы карта удалилась 
                // Todo....
                total_dmg += turn_log.at(i).action_from_card.UtRule.ut_DamageCard;
                less_card += turn_log.at(i).action_from_card.UtRule.ut_TextRule / 10;
                restore_hp += turn_log.at(i).action_from_card.UtRule.ut_RestoreHPCard;
            }
        }

        player_1_hp -= total_dmg;
        player_2_hp += restore_hp;
        // Не забудьте дать на less_card меньше игроку в его некст ход
        cout << "-- Урон за ход второму игроку = " << total_dmg << endl;
        cout << " ++ Восстановлено первым за ход = " << restore_hp << endl;
        cout << " << На " << less_card  << " карт меньше в раздаче в следующем ходу" << endl;

        total_dmg = 0;
        restore_hp = 0;
        less_card = 0;
        coins_per_turn = 0;
        turn_log.clear();

        if (player_1_hp <= 0) {
            packet.clear();
            packet << WIN;
            if (player_2.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }

            packet.clear();
            packet << LOSE;
            if (player_1.send(packet) != sf::Socket::Done) {
                cout << " Ne udalosot clienta" << endl;
                return 1;
            }

            break;
        }

        packet.clear();
        packet << YOUR_TURN;
        if (player_1.send(packet) != sf::Socket::Done) { // Даём разрешение на ход первому игроку
            cout << " Ne udalosot clienta 2" << endl;
            return 1;
        }
    }

    //Желательно бы иметь возможность выводить весь баттл лог, для отладок
    cout << "Конец игры!" << endl;
    return 0;
}