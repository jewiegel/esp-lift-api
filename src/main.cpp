#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/Commands/RequestLiftHandler.h>

WebSocketHandler webSocketHandler;
RequestLiftHandler requestLiftHandler;


void setup() 
{
  Serial.begin(9600);
  Serial.println("Hello, World!");

  webSocketHandler.begin();

  RequestLiftCommand command(5);
  requestLiftHandler.execute(command);
}

void loop() 
{
  webSocketHandler.update();
}
