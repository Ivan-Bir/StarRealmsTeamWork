#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define PATH_FILE "DataBase.txt"
using namespace std;
using namespace sf;


enum GameTargets{
    MARKET_DECK = 1,
    MARKET,
    DOP_MARKET,
    PLAYER_HAND,
    PLAYER_DECK,
    PLAYER_DECK_DISCARD,
    UTIL,
    AVANPOST,
    OPPONENT,
};
enum MarketSlots {
    MARKET_SLOT_1 = 1,
    MARKET_SLOT_2,
    MARKET_SLOT_3,
    MARKET_SLOT_4,
    MARKET_SLOT_5
};
enum GameRaces {
    NonRace = 1,
    GreenRace,
    RedRace,
    YellowRace,
    BlueRace,
};
typedef struct AlliedProperty {
    int al_CoinCard;
    int al_DamageCard;
    int al_RestoreHPCard;
    int al_TextRule;
} AlliedProperty;

typedef struct UtilProperty {
    int ut_CoinCard;
    int ut_DamageCard;
    int ut_RestoreHPCard;
    int ut_TextRule;
} UtilProperty;

class Card
{
    int idCard;
    string nameCard;
    int costCard;
    int RaceCard;
    int CoinCard;
    int DamageCard;
    int RestoreHPCard;
    int TextRule = 0;
    int HaveAlliesRule = 0;
    int HaveUtilRule = 0;
    Sprite Shape;
    AlliedProperty AlRule = {0, 0, 0, 0};
    UtilProperty UtRule = {0, 0, 0, 0};

    int TargetCard;
    double PositionCard_X;
    double PositionCard_Y;
public:
    Card(int id, RectangleShape Shape ,int target = MARKET_DECK) {  // 122 Cargo_Pod 3 3 0 0 0 + 0 3 0 0 - 0 3 0 0
        ifstream data_file(PATH_FILE);
        string data_line;
        int given_id;
        Sprite* sprite;
        while (!data_file.eof()) {
            data_file >> given_id;
            getline(data_file, data_line);
            sprite=give_sprite
            if (id == given_id) {
                stringstream line;
                line << data_line;

                idCard = id;
                line >> nameCard;
                line >> costCard; 
                line >> CoinCard;
                line >> DamageCard;
                line >> RestoreHPCard;
                line >> TextRule;

                RaceCard = id % 100 / 10;

                TargetCard = target;
                PositionCard_X = 99.;
                PositionCard_Y = 99.;

                char marker;
                line >> marker;
                if (marker == '+') {
                    HaveAlliesRule = 1;
                    line >> AlRule.al_CoinCard;
                    line >> AlRule.al_DamageCard;
                    line >> AlRule.al_RestoreHPCard;
                    line >> AlRule.al_TextRule;

                    line >> marker;
                    if (marker == '-') {
                        HaveUtilRule = 1;
                        line >> UtRule.ut_CoinCard;
                        line >> UtRule.ut_DamageCard;
                        line >> UtRule.ut_RestoreHPCard;
                        line >> UtRule.ut_TextRule;
                    }
                }
                if (marker == '-') {
                        HaveUtilRule = 1;
                        line >> UtRule.ut_CoinCard;
                        line >> UtRule.ut_DamageCard;
                        line >> UtRule.ut_RestoreHPCard;
                        line >> UtRule.ut_TextRule;
                    }
                return;
            }
        }
        cout << "Not Found this Card ID" << endl;
        idCard = 0;

        data_file.close();
    }

    void GetParameters() {
        if (idCard == 0) {
            cout << "Card creation error!" << endl;
            return;
        }
        cout << "id= " << idCard << endl;
        cout << "name= " << nameCard << endl;
        cout << "cost= " << costCard << endl;
        cout << "Race= ";
        if (RaceCard == 1)
            cout << "Non race";
        if (RaceCard == 2)
            cout << "Green Race";
        if (RaceCard == 3)
            cout << "Red Race";
        if (RaceCard == 4)
            cout << "Yellow Race";
        if (RaceCard == 5)
            cout << "Blue Race";    
        cout << endl;
        cout << "Coin= " << CoinCard << endl;
        cout << "Damage= " << DamageCard << endl;
        cout << "RestoreHP= " << RestoreHPCard << endl;
        cout << "Target= ";
        switch(TargetCard) {
            case (1): cout << "MARKET_DECK"; break;
            case (2): cout << "MARKET"; break;
            case (3): cout << "DOP_MARKET"; break;
            case (4): cout << "PLAYER_HAND"; break;
            case (5): cout << "PLAYER_DECK"; break;
            case (6): cout << "PLAYER_DECK_DISCARD"; break;
            case (7): cout << "UTIL"; break;
            case (8): cout << "AVANPOST"; break;
            case (9): cout << "OPPONENT"; break;
            default: cout << "No Target";
        }
        cout << endl;

        cout << "Are there text rules? - ";
        if (TextRule != 0) cout << "Yes"; else cout << "NO";
        cout << endl; 

        cout << "Are there allies rules? - ";
        if (HaveAlliesRule != 0) cout << "Yes. Race Property - " << RaceCard; else cout << "NO";
        cout << endl;

        cout << "Are there util rules? - ";
        if (HaveUtilRule != 0) cout << "Yes"; else cout << "NO";
        cout << endl;
        
        cout << "PositionCard(X, Y) " << PositionCard_X << ", " << PositionCard_Y; 
    }
};
