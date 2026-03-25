#include <Arduino.h>
#include <api.h>

int delayInterval = 750;
api *apiInstance;

const char* wifi_ssd = "FMI ImProvia Guest";
const char* wifi_password = "Welcomeguest!";

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");

  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  apiInstance = new api(wifi_ssd, wifi_password);
  apiInstance->connectToWiFi();
}

void loop() {
  apiInstance->server->handleClient();
}
