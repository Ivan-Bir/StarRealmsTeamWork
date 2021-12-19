#include "../data/ClassCard.hpp"
#include "../data/netWorkUtils.hpp"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

// sf::Packet& operator <<(sf::Packet& packet, const sf::Texture& texture) {
//     return packet << texture; 
// }

// sf::Packet& operator >> (sf::Packet& packet, const sf::Texture& texture) {
//     return packet >> texture; 
// }

sf::Packet& operator <<(sf::Packet& packet, const Card& card) {
    packet << card.idCard << card.nameCard << card.CostCard << card.RaceCard << card.CoinCard
                << card.DamageCard << card.RestoreHPCard << card.TextRule << card.HaveAlliesRule << card.HaveUtilRule
                << card.AlRule.al_CoinCard << card.AlRule.al_DamageCard << card.AlRule.al_RestoreHPCard << card.AlRule.al_TextRule
                << card.UtRule.ut_CoinCard << card.UtRule.ut_DamageCard << card.UtRule.ut_RestoreHPCard << card.UtRule.ut_TextRule
                << card.TargetCard << card.PositionCard_X << card.PositionCard_Y << card.path_file_img;
                //packet << card.texture;
    return packet;
}

Card& operator >>(sf::Packet& packet, Card& card) {
    packet >> card.idCard >> card.nameCard >> card.CostCard >> card.RaceCard >> card.CoinCard
            >> card.DamageCard >> card.RestoreHPCard >> card.TextRule >> card.HaveAlliesRule >> card.HaveUtilRule
            >> card.AlRule.al_CoinCard >> card.AlRule.al_DamageCard >> card.AlRule.al_RestoreHPCard >> card.AlRule.al_TextRule
            >> card.UtRule.ut_CoinCard >> card.UtRule.ut_DamageCard >> card.UtRule.ut_RestoreHPCard >> card.UtRule.ut_TextRule
            >> card.TargetCard >> card.PositionCard_X >> card.PositionCard_Y >> card.path_file_img; //>> card.texture;
    return card;
}

bool is_invalid_id_card(int number) {
    ifstream data_file(PATH_FILE);
    string data_line;
    int given_id;
    while (!data_file.eof()) {
        data_file >> given_id;
        getline(data_file, data_line);
        if (number == given_id) {
            return false;
        }
    }
    return true;
}

void SendToServer() {
    return;
}

void RecieveFromServer() {
    return;
}