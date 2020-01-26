#include "Player.h"
#include <vector>
#include "Action_TakeDamage.h"
#include "Const.h"

using namespace std;

/*One specific implementation of an action, here the logic of taking damage*/
unsigned char maxDamage;


void Action_TakeDamage::execute(vector<Parameter_t> params) {
  //Expecting parameter "amount" to indicate the health player is losing
  if(System::printSerial) {
    Serial.print("player hit, had " + String(Player::health));
  }
  
  unsigned char dmg;
  unsigned char healswitch;
  //Get parameter of call
  for (unsigned char i =0; i<params.size();i++) {
      if(params[i].parameterKey == __KEY__AMOUNT__)
      {
          dmg=params[i].parameterValue.toInt();
      }
      else if (params[i].parameterKey == __KEY__HEALSWITCH__)
      {
          healswitch=params[i].parameterValue.toInt();
      }
  }
  //Check if attack is a "healing-Gun" or not
  if(healswitch==0) {
      if (dmg>maxDamage) {
          dmg=maxDamage;
      }
      if (Player::health < dmg)
      {
          Player::health =  0;
      }
      else {
          Player::health -=  dmg;
      }
  }
  else if(Player::alive==1){
      int newHealth = Player::health + dmg;
      if (newHealth > Player::maxHealth) {
          Player::health =  Player::maxHealth;
      }
      else {
          Player::health +=  dmg;
      }
      
  }
  else {
      //can only be healswitch != 0 and alive!=1
    if(System::printSerial) {
      Serial.println("cannot heal, already dead");
    }
  }
  //Check if player is still alive
  if (Player::health <=0) 
  {
      //TODO: Implement logic for dying event
      Player::die(params);
  }


  if(System::printSerial) {
    Serial.println(" now has " + String(Player::health));
  }
  

}

void Action_TakeDamage::init(vector<Parameter_t> params) {
  for (unsigned char i =0; i<params.size();i++) {
      if(params[i].parameterKey == __KEY__MAX__) {
          maxDamage = params[i].parameterValue.toInt();
      }
  }
}
void Action_TakeDamage::init() {
   maxDamage=-1;
   //cout << "TakeDamage: init_noParam" <<endl;
  //do nothing;
}
void Action_TakeDamage::execute() {
  if(System::printSerial) {
    Serial.println("ERROR: Not expected call: TakeDamage::execute_noParam");
  }   
}
         
