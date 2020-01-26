#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "Http.h"
#include "System.h"
#include "UDPNetwork.h"

using namespace std;

const char *ssid = "";
const char *password = "";


const int led = 13;

HTTP webserver;


void setup() {
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //Initialize UDP functionality and send Broadcast
  UDPNetwork::init(WiFi.localIP().toString());
  UDPNetwork::sendBroadcast();

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  webserver.initServer();
  Serial.println("HTTP server started");

}



void loop() {
  // put your main code here, to run repeatedly:
  webserver.loop();
  UDPNetwork::udpListen();
}
