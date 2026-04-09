#include <Arduino.h>
#include <WiFi.h>
#include <RecordPlayerHandler.hpp>
#include <Secrets.hpp>

HTTPHandler httpHandler;
WiFiServer server(80);
Clicker clicker;
RecordPlayerHandler recordPlayerHandler(clicker);

const long timeoutTime = 2000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  
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