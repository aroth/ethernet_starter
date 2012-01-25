#include <Ethernet.h>
#include <EthernetServer.h>
#include <SPI.h>
#include <String.h>

//
// Networking
//

byte mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x75, 0x80 };  
byte ip[]      = { 192, 168, 3, 14 };    
byte gateway[] = { 192, 168, 3, 1 };
byte subnet[]  = { 255, 255, 255, 240 };

EthernetServer server = EthernetServer(777);

//
// Setup
//
void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

//
// Main Loop
//
void loop(){

  EthernetClient client = server.available();
  if (client) {

    while( client.connected() ){
      if( client.available() ){
        String data = recv_data( client );
        Serial.println( data );
        client.print( data );
        client.print('\n');
      }
    }
  
  }
}

// 
// Helper Functions
//
String recv_data(EthernetClient client){
  String data;
  char c = client.read();
  while( c != '\n' ){
    data += c;
    c = client.read();
  }
  return data;
}
