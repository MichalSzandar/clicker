#include <Clicker.hpp>

void Clicker::setupPins(int clickerPin, int moverPin) {
    this->clickerPin = clickerPin;
    this->moverPin = moverPin;
    pinMode(clickerPin, OUTPUT);
    pinMode(moverPin, OUTPUT);
    clickerServo.attach(clickerPin);
    moverServo.attach(moverPin);
}

void Clicker::clickPlay() {
    if (currentState != PLAYING) {
        moveToPosition(180);
        click();
        currentState = PLAYING;
    }
}

void Clicker::clickPause() {
    if (currentState == PLAYING) {
        moveToPosition(90);
        click();
        currentState = PAUSED;
    }
}

void Clicker::clickStop() {
    if (currentState != STOPPED) {
        moveToPosition(0);
        click();
        currentState = STOPPED;
    }
}

void Clicker::moveToPosition(int target)
{
    
}

void Clicker::click()
{
    clickerServo.write(90);
    delay(200);
    clickerServo.write(0);
}
