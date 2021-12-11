#include "../data/ClassCard.hpp"
#include "../data/netWorkUtils.hpp"
#include <SFML/Network.hpp>


sf::Packet& operator <<(sf::Packet& packet, const Card& card) {
    return packet << card.idCard << card.nameCard << card.costCard << card.RaceCard << card.CoinCard
                << card.DamageCard << card.RestoreHPCard << card.TextRule << card.HaveAlliesRule << card.HaveUtilRule
                << card.AlRule.al_CoinCard << card.AlRule.al_DamageCard << card.AlRule.al_RestoreHPCard << card.AlRule.al_TextRule
                << card.UtRule.ut_CoinCard << card.UtRule.ut_DamageCard << card.UtRule.ut_RestoreHPCard << card.UtRule.ut_TextRule
                << card.TargetCard << card.PositionCard_X << card.PositionCard_Y;
}

Card& operator >>(sf::Packet& packet, Card& card) {
    packet >> card.idCard >> card.nameCard >> card.costCard >> card.RaceCard >> card.CoinCard
            >> card.DamageCard >> card.RestoreHPCard >> card.TextRule >> card.HaveAlliesRule >> card.HaveUtilRule
            >> card.AlRule.al_CoinCard >> card.AlRule.al_DamageCard >> card.AlRule.al_RestoreHPCard >> card.AlRule.al_TextRule
            >> card.UtRule.ut_CoinCard >> card.UtRule.ut_DamageCard >> card.UtRule.ut_RestoreHPCard >> card.UtRule.ut_TextRule
            >> card.TargetCard >> card.PositionCard_X >> card.PositionCard_Y;
    return card;
}

void SendToServer() {
    return;
}

void RecieveFromServer() {
    return;
}