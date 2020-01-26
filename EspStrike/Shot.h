#ifndef SHOT_H
#define SHOT_H

class Shot {
    public:
        void generateData(unsigned char player, unsigned char team, unsigned char damage, unsigned char healswitch);
        unsigned char getEcc(unsigned char number);
        unsigned char getOverallEcc(unsigned char num1, unsigned char num2, unsigned char num3);
        unsigned char getTeam();
        unsigned char getPlayer();
        unsigned char getDamage();
        unsigned char getHealSwitch();
};
#endif
