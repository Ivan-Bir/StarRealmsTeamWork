#ifndef PROJECT_NETWORKUTILS_UTILS_HPP_
#define PROJECT_NETWORKUTILS_UTILS_HPP_

#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "ClassCard.hpp"

enum NetWorkStatus {
    START_GAME,
    YOUR_TURN,
    WAIT,
    OPPONENT_TURN,
    WIN,
    LOSE
};

enum PlayerActions {
    NOTHING = 0,
    PLAY_CARD = 10,
    BUY_CARD,
    UTIL_CARD,
    GET_CARD,
    END_TURN
};

class Actions {
 public:
    Actions() = default;
    int action_status = NOTHING;
    Card action_from_card = {111};
    int position = -1;  // Номер слота где была карта в руке/маркете
};

bool is_invalid_id_card(int number);

#endif  // PROJECT_NETWORKUTILS_UTILS_HPP_
