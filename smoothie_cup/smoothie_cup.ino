#include <Arduino.h>
#include <SBUS2.h>

uint8_t FrameErrorRate = 0;
int16_t channel[18] = {0};

// constants won't change
const int RELAY_PIN = 3;  // the Arduino pin, which connects to the IN pin of relay

// configure loop
const unsigned int relaisCloseDuration = 2000;
const unsigned int relaisLockoutDuration = 1800000;

void setup()
{
  // put your setup code here, to run once:
  SBUS2_Setup();        // Default Pin Number and Atmega328

  // we use the led to see if its working
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize digital pin as an output.
  pinMode(RELAY_PIN, OUTPUT);
}

void loop()
{
    static unsigned char relaisState = LOW;
    static unsigned long relaisCameOn = 0;
    static unsigned long relaisLockoutUntil = 0;

    // check if the relay has to be shut off
    if(relaisState == HIGH)
    {
      if(millis()-relaisCameOn > relaisCloseDuration)
      {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(RELAY_PIN, LOW);
        relaisState = LOW;
        relaisLockoutUntil = millis() + relaisLockoutDuration;
      }
    }
    
    if(SBUS_Ready()){                               // SBUS Frames available -> Ready for getting Servo Data
      for(uint8_t i = 0; i<10; i++){
        channel[i] = SBUS2_get_servo_data(i);        // Channel = Servo Value of Channel 5
      }
      if(channel[0] > 1000) {
        if (relaisState == LOW && relaisLockoutUntil < millis()) {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          digitalWrite(RELAY_PIN, HIGH);
          relaisState = HIGH;
          relaisCameOn = millis();
        }
      }
      FrameErrorRate = SBUS_get_FER();
    }

} // End of Loop()
