#include <Arduino.h>
#include <WebSocketApi/WebSocketHandler.h>
#include <WebSocketApi/Commands/RequestLiftHandler.h>
#include "WebSocketApi/CommandRegistry.h"

WebSocketHandler webSocketHandler;
RequestLiftHandler requestLiftHandler;


void setup() 
{
  Serial.begin(9600);
  Serial.println("Hello, World!");

  webSocketHandler.begin();

  RequestLiftCommand command(5);

  // Call the command registry to convert a command name to a handler
  ILiftCommandHandler* handler = CommandRegistry::convertHandler("api/v1/lift/RequestLiftCommand");
  handler->execute(command);
}

void loop() 
{
  webSocketHandler.update();
}
