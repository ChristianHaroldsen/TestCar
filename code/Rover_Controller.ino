#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int fwd_pin = 4;
int right_pin = 3;
int left_pin = 5;
int reset_pin = 2;
int wait = 250; //ms for delay

void setup()
{
  Serial.begin(9600);
  //radio setup
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter

  //Inputs
  pinMode(fwd_pin, INPUT_PULLUP);
  pinMode(right_pin, INPUT_PULLUP);
  pinMode(left_pin, INPUT_PULLUP);
  pinMode(reset_pin, INPUT_PULLUP);
}

void loop()
{
  //Pin reads LOW when pressed, numpad keys for directions-ish
  int message;
  if (!digitalRead(reset_pin)) message = 555;
  else if (!digitalRead(fwd_pin)) message = 888;
  else if (!digitalRead(right_pin)) message = 666;
  else if (!digitalRead(left_pin)) message = 444;

  //Always send when active, resets watchdog on receiver
  else message = 456;
  radio.write(&message, sizeof(message));  //Send the message to receiver
  Serial.println(message);
  delay(wait);
}
