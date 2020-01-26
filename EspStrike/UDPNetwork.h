#ifndef NETWORKREGISTER_H
#define NETWORKREGISTER_H

#include <Arduino.h>
#include "System.h"

using namespace std;

class UDPNetwork{
  public:
    static void init(String network);
    static void sendBroadcast();
    static void repeatBroadcast(String messageId, String messageText);
    static void udpListen();
    static void sendMessage(String message);
    static void sendMessage(String messageId, String message);
    static void sendMessage(String messageid, String address, String message);
    static void addMessageToBuffer(String messageId);
    static void initMessageBuffer(int size);
    static void resendMessage(String message);

    static int messageBufferSize;
    static struct messageBuffer_t messageBuffer;
    static int messageCounter;
    static struct messageBuffer_t* lastMessage;
};

#endif
