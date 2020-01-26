#include <HTTPClient.h>
#include "Player.h"
#include "Http.h"
#include <vector>

using namespace std;

WebServer server;
int HTTP::messageBufferSize=0;
struct messageBuffer_t HTTP::messageBuffer;
int HTTP::messageCounter;
struct messageBuffer_t* HTTP::lastMessage = &messageBuffer;

void HTTP::callURL(String URL) {
  if((WiFi.isConnected()== true)) {
    HTTPClient http;
    http.begin(URL); //HTTP
       int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
  }
}

void HTTP::initServer() {
    messageCounter=0;
    initMessageBuffer(5);

  
    server.on("/", handleRoot);
    server.on("/green", greenLED);
    server.on("/newConfig", loadConfig);
    server.on("/test", handleTest);
    server.on("/irled", irled);
    server.onNotFound(handleNotFound);
    server.begin();
}

void HTTP::loadConfig(){
  String remoteURL="";
  for (uint8_t i = 0; i < server.args(); i++) {
    if(server.argName(i)=="url") {
      remoteURL=server.arg(i);
    }
  }
  server.send(200, "text/html", "");
  remoteURL = parseURL(remoteURL);
  callURL(remoteURL);
}
/*
%20 <SPACE>
%21  !
%22  "
%23  #
%24  $
%25  %
%26  &
%27  '
%28  (
%29  )
%2A  *
%2B  +
%2C  ,
%2D  -
%2E  .
%2F  /
%3A  :
%3B  ;
%3C  <
%3D  =
%3E  >
%3F  ?
%40  @
%5B  [
%5C  \
%5D  ]
%7B  {
%7C  |
%7D  }

*/

String HTTP::parseURL(String url)
{
  url.replace("%22","\""); 
  url.replace("%26","&");
  url.replace("%2D","-");
  url.replace("%2E",".");
  url.replace("%2F","/");
  url.replace("%3A",":");
  url.replace("%3D","=");
  url.replace("%3C","<");
  url.replace("%3E",">");
  url.replace("%3F","?");
  return url;
}

void HTTP::greenLED (){
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  digitalWrite(14,HIGH);
  server.send(200, "text/html", "");
  delay(1000);
  digitalWrite(14,LOW);
  digitalWrite(16,HIGH);
  delay(1000);
  digitalWrite(16,LOW);
  digitalWrite(17,HIGH);
  delay(1000);
  digitalWrite(17,LOW);
  digitalWrite(18,HIGH);
  delay(1000);
  digitalWrite(18,LOW);
}

void HTTP::irled (){
  pinMode(19,OUTPUT);
  digitalWrite(19,HIGH);
  server.send(200, "text/html", "");
  delay(5000);
  digitalWrite(19,LOW);
}

void HTTP::loop() {
  server.handleClient();
}

void HTTP::handleRoot() {
  Player::printStatus();
  server.send(200, "text/html", "");

}

void HTTP::handleNotFound() {
//      digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
//      digitalWrite(led, 0);
}

void HTTP::handleTest(){
    vector<Parameter_t> params;
    params.push_back(Parameter_t());
    params[0].parameterKey="amount";
    params[0].parameterValue="1";
    params.push_back(Parameter_t());
    params[1].parameterKey="player";
    params[1].parameterValue="2";
    params.push_back(Parameter_t());
    params[2].parameterKey="team";
    params[2].parameterValue="3";
    params.push_back(Parameter_t());
    params[3].parameterKey="heal";
    params[3].parameterValue="4";
    sendMessage(params);
    printBuffer();
    server.send(200, "text/html", "");
}


//Higher Level Methods

void HTTP::sendMessage(vector<Parameter_t> params) {
    String messageId = String(messageCounter++);
    String postdata="?messageId="+messageId + "&";
    for (unsigned char i =0; i<params.size();i++) {
            postdata = postdata + params[i].parameterKey + "=" + params[i].parameterValue + "&";
                        
    }
    HTTP::addMessageToBuffer(messageId,postdata);
    HTTP::sendMessage(postdata);

};
void HTTP::resendMessage(String id) {
    struct messageBuffer_t *curr = &messageBuffer;
    for(int i=0;i<messageBufferSize;i++)
    {
        if(curr->messageId==id)
        {
            HTTP::sendMessage(curr->message);
            break;
        }
        curr=curr->next;
    }
};

void HTTP::printBuffer()
{
  struct messageBuffer_t *curr = &messageBuffer;
  for(int i=0;i<messageBufferSize;i++){
        
    if(System::printSerial) {
      Serial.println(String(i) + ": " + curr->messageId + " - " + curr->message);
    }
    curr = curr->next;
  }
}

void HTTP::sendMessage(String message)
{
  if(System::printSerial) {
    Serial.println("sending: " + message);
  }
};

void HTTP::addMessageToBuffer(String messageId, String message)
{
    lastMessage = lastMessage->next;
    lastMessage->messageId=messageId;
    lastMessage->message=message;
}

void HTTP::initMessageBuffer(int size)
{
    struct messageBuffer_t *curr = &messageBuffer;
    for(int i=1;i<size;i++)
    {
        curr->next = new messageBuffer_t();
        curr=curr->next;
    }
    curr->next=&messageBuffer;
    messageBufferSize=size;
};
void HTTP::testBuffer()
{
    
    //Lets fill the buffer with dump data
    for(int i=0;i<100;i++){
        addMessageToBuffer(String(messageCounter++),"?messageId="+String(messageCounter) + "&");
    }
    printBuffer();
    
}
