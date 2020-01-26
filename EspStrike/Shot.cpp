#include "Shot.h"
#include "System.h"
/*
Class to calculate the bitstream for an shot or extract the data from it

byteshifts:
playerId: 0x1F = 31 = x00011111 must result in x11111000
*/

unsigned char byte1;
unsigned char byte2;
unsigned char byte3;
unsigned char byte4;


void Shot::generateData(unsigned char player, unsigned char team, unsigned char damage, unsigned char healswitch){
    //Validation
    if(player > 32) {
        if(System::printSerial) {
          Serial.println("invalid player: " + String(player));
        }
        return;
    }
    if(team > 32) {
        if(System::printSerial) {
          Serial.println("invalid team: " + String(team));
        }
        return;
    }
    if(damage > 255) {
        if(System::printSerial) {
          Serial.println("invalid damage: " + String(damage));
        }
        return;
    }
    if(healswitch > 1) {
        if(System::printSerial) {
          Serial.println("invalid healswitch: " + String(healswitch));
        }
        return;
    }
    
    //Byte1
    byte1 = (player << 3);

    //that was the easy part, now adding teamId, As of structure, the two highest bits of team are needed, 
    // means an and-mask of 00011000 (=0x18) will get the first two highest bits of the 5 bit long value
    unsigned char __tmp =((team & 0x18) >> 2);
    byte1 = byte1 | __tmp;
    byte1 = byte1 | getEcc(byte1);

    //Byte2
    //00000111 Maske anwenden (0x7)
    byte2 = ((team & 0x07) << 5);
    //11110000 = 0xF0
    __tmp = ((damage & 0xF0) >> 3);
    byte2 = byte2 | __tmp;
    byte2 = byte2 | getEcc(byte2);

    //byte3:
    
    byte3=((damage & 0x0F) << 4);
    byte3= byte3 | (healswitch << 3);
    
    
    byte3 = byte3 | getEcc(byte3);

    //byte4 (ecc-Byte)
    byte4 = getOverallEcc(byte1, byte2, byte3);
}
unsigned char Shot::getEcc(unsigned char number) {
    unsigned char count = 0; 
    while (number) { 
        count += number & 1; 
        number >>= 1; 
    } 
    return count % 2; 
}
unsigned char Shot::getOverallEcc(unsigned char num1, unsigned char num2, unsigned char num3) {
    unsigned char ecc = 0; 
    
    for (char i=0;i<8;i++) { 
        ecc <<= 1;
        ecc = ecc |( ((num1 & 0x80) + (num2 & 0x80) + (num3 & 0x80) & 0x80) >> 7); 
        num1 <<= 1; 
        num2 <<= 1; 
        num3 <<= 1; 
    } 
    return ecc; 
}

unsigned char Shot::getTeam() {
    return (byte1 & 0xF8) >> 3;
}
unsigned char Shot::getPlayer() {
    return ((byte1 & 0x6) << 2 | (byte2 & 0xE0)>> 5);
}

unsigned char Shot::getDamage() {
    return ((byte2 & 0x1E) << 3 | (byte3 & 0xF0)>> 4);
}

unsigned char Shot::getHealSwitch() {
    return ((byte3 & 0x8)>> 3);
}
