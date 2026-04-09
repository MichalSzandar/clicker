#ifndef RECORDPLAYERHANDLER_HPP
#define RECORDPLAYERHANDLER_HPP

#include <HTTPHandler.hpp>
#include <Clicker.hpp>

class RecordPlayerHandler {
public:
    RecordPlayerHandler(Clicker& clicker) : clicker(clicker) {}
    void setupRecordPlayerRoutes(HTTPHandler& httpHandler);
private:
    Clicker& clicker;

    void handlePlay(WiFiClient& client);
    void handlePause(WiFiClient& client);
    void handleStop(WiFiClient& client);
    void handleRoot(WiFiClient& client);

    void send200Response(WiFiClient& client);
};

#endif