//14-----5
//12--3--4
//13-----0
// BUTTON 2
#include <Arduino.h>

class Led
{
  public:
    Led(int);
    void On();
    void Off();
    int getPin();

  private:
    int outPin;
    bool on;
};

Led::Led(int outpin)
{
    this->outPin = outpin;
    this->on = false;
}
void Led::On()
{
    digitalWrite(this->outPin, HIGH);
    this->on = true;
}
int Led::getPin()
{
    return this->outPin;
}

void Led::Off()
{
    digitalWrite(this->outPin, LOW);
    this->on = false;
}

Led ledky[]{14,12,13,3,0,4,5};
bool state = false;
int button = 2;
int rndInt = 0;

void blink(){    
    state = !state;
}

void turnOffAll(){
    for(int i = 0;i < 7;i++){
       ledky[i].Off(); // vsechny
    }
}

void cislo(int i){
    if(i == 1 || i == 3 || i == 5){
        ledky[3].On(); // 3
    }
    if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6){
        ledky[2].On(); // 13
        ledky[6].On(); // 5
    }
    if(i == 4 || i == 5 || i == 6){
        ledky[0].On(); // 14
        ledky[4].On(); // 0
    }
    if(i == 6){
        ledky[1].On(); // 12
        ledky[5].On(); // 4
    }
}

void setup()
{
    // put your setup code here, to run once:
    for(int i = 0;i < 7;i++){
       pinMode(ledky[i].getPin(),OUTPUT);
    }
    pinMode(button, LOW);
    attachInterrupt(digitalPinToInterrupt(button), blink, CHANGE);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if(state){
        rndInt = rand() % 6 + 1;
        cislo(rndInt);
        Serial.print("Number: " + rndInt);
        delay(150);
        turnOffAll();   
    }
    else{
        cislo(rndInt);
        delay(500);
    }
}