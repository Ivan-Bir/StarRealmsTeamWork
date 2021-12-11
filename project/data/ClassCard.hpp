#ifndef PROJECT_CLASSDECK_UTILS_HPP_
#define PROJECT_CLASSDECK_UTILS_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define PATH_FILE_DATA_BASE "project/include/DataBase.txt"
#define PATH_FILE_IMAGES "project/include/images/"
using namespace std;
using namespace sf;


enum GameTargets {
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

class Card {
    int idCard = 0;
    string nameCard;
    int costCard = 0;
    int RaceCard = 0;
    int CoinCard = 0;
    int DamageCard = 0;
    int RestoreHPCard = 0;
    int TextRule = 0;
    int HaveAlliesRule = 0;
    int HaveUtilRule = 0;

    AlliedProperty AlRule = {0, 0, 0, 0};
    UtilProperty UtRule = {0, 0, 0, 0};

    double PositionCard_X;
    double PositionCard_Y;
    sf::Texture texture;
public:
    int TargetCard;
    Card(int id, int target = MARKET_DECK) {  // 122 Cargo_Pod 3 3 0 0 0 + 0 3 0 0 - 0 3 0 0
        ifstream data_file(PATH_FILE_DATA_BASE);
        string data_line;
        int given_id;
        std::string path_image="project/include/images/"+to_string(id)+".jpg";
        texture.loadFromFile(path_image);
        while (!data_file.eof()) {
            data_file >> given_id;
            getline(data_file, data_line);

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
        if (id!=0){
            cout << "Not Found this Card ID" << endl;
        }
        idCard = 0;

        data_file.close();
    }

    

    Card operator=(Card &card1);
    int GetParameters();
    sf::Texture* GetTexture();
    int getId() {
        return idCard;
    }
};
#endif  // PROJECT_CLASSDECK_UTILS_HPP_
