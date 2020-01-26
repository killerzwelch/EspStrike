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
        static bool configReceived; //Flag that system only starts up when server has send configuration
        static String ipaddress; //Flag that system only starts up when server has send configuration
};



struct messageBuffer_t {
    String message;
    String messageId;
    messageBuffer_t *next = 0x0;
};


#endif
