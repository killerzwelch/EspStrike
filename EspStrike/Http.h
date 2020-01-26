#ifndef HTTP_H
#define HTTP_H

#include "Parameter_t.h"

#include <WebServer.h>
#include <vector>
#include "System.h"
class HTTP {
 
    
  public:
    static void callURL(String URL);
    void initServer();
    void loop();
 
  private:
    static void handleRoot();
    static void greenLED();
    static void handleNotFound();
    static void loadConfig();
    static void handleTest();
    static void irled();
    static String parseURL(String url);
    static void sendMessage(vector<Parameter_t> params);
    static void resendMessage(String id);
    static void printBuffer();
    static void sendMessage(String message);
    static void addMessageToBuffer(String messageId, String message);
    static void initMessageBuffer(int size);
    static void testBuffer();

    static int messageBufferSize;
    static struct messageBuffer_t messageBuffer;
    static int messageCounter;
    static struct messageBuffer_t* lastMessage;


};


#endif
