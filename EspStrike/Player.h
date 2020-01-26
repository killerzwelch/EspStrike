#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Parameter_t.h"
#include "System.h"

class Player {
    public: 
        static int player;
        static int life;
        static int health;
        static int maxHealth;
        static int team;
        static int alive;
        static void die(std::vector<Parameter_t> params);
        static void resurect();
        static void printStatus();
};
#endif
