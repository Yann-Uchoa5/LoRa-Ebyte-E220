#include "Arduino.h"
#include "LoRa_E220.h"
 
 LoRa_E220 e220ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1
 

void setup() {
  Serial.begin(9600);
  delay(500);
 
  // Startup all pins and UART
  e220ttl.begin();
 
  Serial.println("Hi, I'm going to send message!");
 
  // Send message
  ResponseStatus rs = e220ttl.sendBroadcastFixedMessage(23, "Hello, world?");
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
}
 
void loop() {
    // If something available
  if (e220ttl.available()>1) {
      // read the String message
#ifdef ENABLE_RSSI
    ResponseContainer rc = e220ttl.receiveMessageRSSI();
#else
    ResponseContainer rc = e220ttl.receiveMessage();
#endif
    // Is something goes wrong print error
    if (rc.status.code!=1){
        Serial.println(rc.status.getResponseDescription());
    }else{
        // Print the data received
        Serial.println(rc.status.getResponseDescription());
        Serial.println(rc.data);
#ifdef ENABLE_RSSI
        Serial.print("RSSI: "); Serial.println(rc.rssi, DEC);
#endif
    }
  }
  if (Serial.available()) {
      String input = Serial.readString();
      ResponseStatus rs = e220ttl.sendBroadcastFixedMessage(23, input);
      // Check If there is some problem of succesfully send
      Serial.println(rs.getResponseDescription());
  }
}
