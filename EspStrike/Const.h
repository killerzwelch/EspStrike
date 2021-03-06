#ifndef CONST_H
#define CONST_H

#if defined(__AVR__)
    #include <avr/pgmspace.h>
    #define imagedatatype const uint8_t
#elif defined(__PIC32MX__)
    #define PROGMEM
    #define imagedatatype const unsigned char
#elif defined(__arm__)
    #define PROGMEM
    #define imagedatatype const unsigned char
#endif

imagedatatype heart[] PROGMEM={
0x84, 0x8E, 0x9F, 0xBE, 0xFC, 0xBE, 0x9F, 0x8E, 0x84, 
};


const String __KEY__AMOUNT__ = "amount";
const String __KEY__HEALTH__ = "health";
const String __KEY__LIFE__ = "life";
const String __KEY__VAL__ = "val";
const String __KEY__TEAM__ = "team";
const String __KEY__PLAYER__ = "player";
const String __KEY__HEALSWITCH__ = "heal";
const String __KEY__MAX__ = "max";
/*Keys for sendMessage*/
const String __KEY__TO__ = "to";
const String __KEY__MESSAGE__ = "message";
/*Wildcard characters to replace during runtime*/
const String __VAR__OPPONENTTEAM__ = "%OPPONENTTEAM%";
const String __VAR__PLAYERTEAM__ = "%PLAYERTEAM%";
const String __VAR__PLAYER__ = "%PLAYER%";
const String __VAR__SERVER__ = "%SERVER%";
const String __VAR__OPPONENTPLAYER__ = "%OPPONENTPLAYER%";
const String __VAR__ALL__ = "%ALL%";

const char TRUE = 1;
const char FALSE = 0;


#endif CONST_H
