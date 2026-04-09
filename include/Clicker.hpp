#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <Arduino.h>
#include <ESP32Servo.h>

enum PlayerState { STOPPED, PLAYING, PAUSED };

class Clicker {
public:
    Clicker() = default;
    void setupPins(int clickerPin, int moverPin);
    void clickPlay();
    void clickPause();
    void clickStop();
    PlayerState getCurrentState() const { return currentState; }
private:
    PlayerState currentState = STOPPED;
    Servo clickerServo, moverServo;
    int clickerPin, moverPin, position = 0;
    void moveToPosition(int target);
    void click();
};

#endif