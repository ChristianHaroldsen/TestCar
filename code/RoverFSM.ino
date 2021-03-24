#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin OUTPUTS
int motorLeft = 5; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int motorRight = 6; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int led_pin = 2;

//initalize variables
const int powerMax = 255;
int powerRight = 0;
int powerLeft = 0;
char *state = "Starting State"; //Just allocated enough memory for a long string

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

void setup()
  {
    //radio setup
    radio.begin();
    radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
    radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
    radio.startListening();              //This sets the module as receiver

    //outputs
    pinMode(motorLeft, OUTPUT);
    pinMode(motorRight, OUTPUT);
    pinMode(led_pin, OUTPUT);
  }

void loop()
  {
    //looks for data
    while (radio.available())
      {
        //save data to message
        int message;
        radio.read(&message, sizeof(message));

        //Use message to control
        switch (message)
        {
          case 555:
          Down(state);
          digitalWrite(led_pin, LOW);
          break;

          case 444:
          Left(state);
          digitalWrite(led_pin, LOW);
          break;

          case 666:
          Right(state);
          digitalWrite(led_pin, LOW);
          break;

          case 888:
          Up(state);
          digitalWrite(led_pin, LOW);
          break;

          case 456:
          //ack
          digitalWrite(led_pin, LOW);
          break;

          default:
          break;
        }

        //push values to motor speed
        analogWrite(motorLeft, powerLeft);
        analogWrite(motorRight, powerRight);
      }
    delay(5);

    //Light off, no signal!
    digitalWrite(led_pin, HIGH);
  }

  void Down (char *, state);
  {

  }
