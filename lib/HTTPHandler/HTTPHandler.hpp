#ifndef HTTPHANDLER_HPP
#define HTTPHANDLER_HPP

#include <map>
#include <Arduino.h>
#include <WiFi.h>

/// @brief Type definition for a response function that takes a WiFiClient reference.
typedef std::function<void(WiFiClient&)> ResponseFunction;

/// @brief Struct to represent an HTTP request with method and path, used as a key in the route map.
struct HTTPRequest {
    String method;
    String path;

    bool operator<(const HTTPRequest& other) const {
        if (method != other.method) return method < other.method;
        return path < other.path;
    }
};

/// @brief HTTPHandler class to manage HTTP routes and process incoming requests.
class HTTPHandler {
public:
    HTTPHandler() = default;

    void on(const String& method, const String& path, ResponseFunction callback);
    void processRequest(WiFiClient& client, const String& rawRequest);

private:
    std::map<HTTPRequest, ResponseFunction> routeMap;

    void send404(WiFiClient& client);
    void send400(WiFiClient& client);
};

#endif