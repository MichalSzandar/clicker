#include "HTTPHandler.hpp"

void HTTPHandler::on(const String& method, const String& path, ResponseFunction callback) {
    HTTPRequest routeKey = {method, path};
    routeMap[routeKey] = callback;
}

void HTTPHandler::processRequest(WiFiClient& client, const String& rawRequest) {
    int space1 = rawRequest.indexOf(' ');
    if (space1 == -1) {
        send400(client);
        return; 
    }

    int space2 = rawRequest.indexOf(' ', space1 + 1);
    if (space2 == -1) {
        send400(client);
        return; 
    }

    String method = rawRequest.substring(0, space1);
    String path = rawRequest.substring(space1 + 1, space2);

    HTTPRequest incomingRequest = {method, path};

    auto it = routeMap.find(incomingRequest);
    
    if (it != routeMap.end()) {
        it->second(client); 
    } else {
        send404(client);
    }
}

void HTTPHandler::send404(WiFiClient& client) {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("Error 404: The requested route does not exist on this server.");
}

void HTTPHandler::send400(WiFiClient& client) {
    client.println("HTTP/1.1 400 Bad Request");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("Error 400: Malformed HTTP Request.");
}