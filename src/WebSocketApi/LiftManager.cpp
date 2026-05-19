#include "LiftManager.h"

LiftManager::LiftManager(LiftCommandScheduler *scheduler,
    WebSocketHandler *webSocketHandler,
    ButtonDriver *floorButton,
    ILedDriver **floorLeds,
    int ledCount) : scheduler(scheduler),
    webSocketHandler(webSocketHandler),
    floorButton(floorButton),
    floorLeds(floorLeds),
    ledCount(ledCount)
{
    floorButton->onPress(std::bind(&LiftManager::onFloorButtonPress, this));
    floorLeds[currentLedIndex]->on();
}

LiftManager::~LiftManager()
{
}

void LiftManager::enqueueCommand(ICommand* command)
{
    scheduler->enqueue(command);
}

void LiftManager::update()
{
    scheduler->processNext();
    floorButton->update();
}

void LiftManager::commandCompleted()
{
    scheduler->commandCompleted();
}

void LiftManager::clearCommands()
{
    scheduler->clearCommands();
}

void LiftManager::onFloorButtonPress()
{
    floorLeds[currentLedIndex]->off();
    currentLedIndex = (currentLedIndex + 1) % ledCount;
    floorLeds[currentLedIndex]->on();

    Serial.println("Floor selected: " + String(currentLedIndex));

    JsonDocument doc;
    doc["event"] = "floorSelected";
    doc["floor"] = currentLedIndex;
    webSocketHandler->sendData(doc);
}