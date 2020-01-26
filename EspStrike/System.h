#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "ActionList_t.h"

class System {
    public: 
        static bool printSerial;
        static ActionList_t on_Hit;
        static ActionList_t on_Tick;
        static ActionList_t on_Hit_interrupts;
        static ActionList_t on_LifeLoss;
        static ActionList_t on_Death;
};



struct messageBuffer_t {
    String message;
    String messageId;
    messageBuffer_t *next = 0x0;
};


#endif
