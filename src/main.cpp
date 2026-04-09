#include <Arduino.h>
#include <WiFi.h>
#include <RecordPlayerHandler.hpp>

#define CLICKER_PIN 12
#define MOVER_PIN 13

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

HTTPHandler httpHandler;
WiFiServer server(80);
Clicker clicker;
RecordPlayerHandler recordPlayerHandler(clicker);

const long timeoutTime = 2000;

void initWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  
  clicker.setupPins(CLICKER_PIN, MOVER_PIN);
  recordPlayerHandler.setupRecordPlayerRoutes(httpHandler);
  
  initWiFi();
  server.begin();
}

void loop(){
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    
    String header = "";
    String currentLine = "";
    unsigned long currentTime = millis();
    unsigned long previousTime = currentTime;
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            httpHandler.processRequest(client, header);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    
    client.stop();
    Serial.println("Client disconnected.\n");
  }
}