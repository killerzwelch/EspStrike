#include "Player.h"
#include <vector>

using namespace std;

/*Linker issue, need to initialize all static variables outside of any function
@see https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
*/
int Player::health=0;
int Player::maxHealth=0;
int Player::life=0;
int Player::team=0;
int Player::player=0;
int Player::alive=1;

void Player::die(vector<Parameter_t> params){
    if(System::printSerial) {
      Serial.println("player died");
    }
    Player::alive=0;
    if(Player::life > 0) {
        Player::life--;
        //handle resurect
        //executeActions(&on_LifeLoss,params);
    }
    else{
        //handle death
        //executeActions(&on_Death,params);
    }
};
void Player::resurect(){
    if(System::printSerial) {
      Serial.println("player lifes again");
    }
      
    Player::health=Player::maxHealth;
    Player::alive=1;
};
void Player::printStatus(){
    if(System::printSerial) {
      Serial.println("PlayerId " + String(Player::player));
      Serial.println("TeamId " + String(Player::team));
      Serial.println("Health " + String(Player::health));
      Serial.println("maxHealth " + String(Player::maxHealth));
      Serial.println("alive? " + String(Player::alive));
      Serial.println("life " + String(Player::life));
    }
}
