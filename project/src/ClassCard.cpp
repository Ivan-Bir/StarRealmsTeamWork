#include "../data/ClassCard.hpp"

using namespace std;

int Card::GetParameters() {
        if (idCard == 0) {
            cout << "Card creation error!" << endl;
            return -1;
        }
        cout << "id= " << idCard << endl;
        cout << "name= " << nameCard << endl;
        cout << "cost= " << CostCard << endl;
        cout << "PATH= " << path_file_img << endl;
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
        
        cout << "PositionCard(X, Y) " << PositionCard_X << ", " << PositionCard_Y << endl;
        
        return 1;
    }

sf::Texture* Card::GetTexture(){
    return &texture;
}
Card return_card(int id){
    Card card(id);
    return card;
}