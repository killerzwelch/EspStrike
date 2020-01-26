#include "UDPNetwork.h"

#include <WiFiUdp.h>
#include <EthernetUdp.h>


String broadcastAddr;
const int udpPort = 5001;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,

int UDPNetwork::messageBufferSize=0;
struct messageBuffer_t UDPNetwork::messageBuffer;
int UDPNetwork::messageCounter;
struct messageBuffer_t* UDPNetwork::lastMessage = &messageBuffer;


//create UDP instance
WiFiUDP udp;

void UDPNetwork::init(String network){
  udp.begin(udpPort);
  initMessageBuffer(5);
  broadcastAddr = network.substring(0,network.lastIndexOf(".")+1) + "255";
}


void UDPNetwork::sendBroadcast(){
  sendMessage("Hello world");  
}

void UDPNetwork::repeatBroadcast(String messageId, String messageText) {
  Serial.println("Resending message '" + messageId + "'" + messageText);
  sendMessage(messageId, messageText);
}

void UDPNetwork::udpListen() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println(packetBuffer);
    UDPNetwork::resendMessage(String(packetBuffer));
  }
}

void UDPNetwork::sendMessage(String message) {
  UDPNetwork::sendMessage(String(esp_random()),broadcastAddr,message);
}
void UDPNetwork::sendMessage(String messageId, String message) {
  UDPNetwork::sendMessage(messageId,broadcastAddr,message);
}


void UDPNetwork::sendMessage(String messageid, String address, String message) {
  const char * bcAdress = address.c_str();
  String finalMessage = messageid +"|"+message;
 
  // Length (with one extra character for the null terminator)
  int str_len = finalMessage.length() + 1; 
 
  // Prepare the character array (the buffer) 
  char char_array[str_len];
 
  // Copy it over 
  finalMessage.toCharArray(char_array, str_len);

  unsigned char* tmpArr = (unsigned char*)finalMessage.c_str();
  addMessageToBuffer(messageid);
  udp.beginPacket(bcAdress, udpPort);
  udp.write(tmpArr, str_len);
  udp.endPacket(); 
}

void UDPNetwork::addMessageToBuffer(String messageId)
{
    lastMessage = lastMessage->next;
    lastMessage->messageId=messageId;
}

void UDPNetwork::initMessageBuffer(int size)
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

void UDPNetwork::resendMessage(String message) {
    int sepPos = message.indexOf("|");
    String messageId = message.substring(0,sepPos);
    String messageText = message.substring(sepPos+1);
    struct messageBuffer_t *curr = &messageBuffer;
    bool found=false;
    for(int i=0;i<messageBufferSize;i++)
    {
        if(curr->messageId==messageId)
        {
            found=true;
            break;
        }
        curr=curr->next;
    }
    if(!found) {
      UDPNetwork::repeatBroadcast(messageId, messageText);
    }
};
