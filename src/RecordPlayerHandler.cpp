#include "RecordPlayerHandler.hpp"

void RecordPlayerHandler::setupRecordPlayerRoutes(HTTPHandler &httpHandler) {
    httpHandler.on("GET", "/", [this](WiFiClient& c) { this->handleRoot(c); });
    httpHandler.on("GET", "/play", [this](WiFiClient& c) { this->handlePlay(c); });
    httpHandler.on("GET", "/pause", [this](WiFiClient& c) { this->handlePause(c); });
    httpHandler.on("GET", "/stop", [this](WiFiClient& c) { this->handleStop(c); });
}

void RecordPlayerHandler::handlePlay(WiFiClient &client) {
    clicker.clickPlay();
    handleRoot(client);
}

void RecordPlayerHandler::handlePause(WiFiClient &client) {
    clicker.clickPause();
    handleRoot(client);
}

void RecordPlayerHandler::handleStop(WiFiClient &client) {
    clicker.clickStop();
    handleRoot(client);
}

void RecordPlayerHandler::handleRoot(WiFiClient& client) {
    send200Response(client);
    
    PlayerState state = clicker.getCurrentState();
    String stateStr = (state == PLAYING) ? "Playing" : (state == PAUSED) ? "Paused" : "Stopped";

    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(".button-pause {background-color: #ff9800;}");
    client.println(".button-stop {background-color: #f44336;}</style></head>");
    
    client.println("<body><h1>Record Player Controller</h1>");
    client.println("<p>Current State: <strong>" + stateStr + "</strong></p>");
    
    client.println("<p><a href=\"/play\"><button class=\"button\">Play</button></a></p>");
    client.println("<p><a href=\"/pause\"><button class=\"button button-pause\">Pause</button></a></p>");
    client.println("<p><a href=\"/stop\"><button class=\"button button-stop\">Stop</button></a></p>");
    client.println("</body></html>");
    client.println();
}


void RecordPlayerHandler::send200Response(WiFiClient &client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
}
