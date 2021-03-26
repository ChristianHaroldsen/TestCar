#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin OUTPUTS
int motorLeft = 5; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int motorRight = 6; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int led_pin = 2;

//initalize variables
const int powerMax = 255;
int state = 2;
//States are integers to make things easier and they correspond to the keypad/diagram
//2 NoPower
//5 HalfPower
//4 HalfTurnL
//6 HalfTurnR
//7 FullTurnL
//9 FullTurnR
//8 FullPower

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

//prototype functions
void PerformState (int state);
void Up (int s);
void Down (int s);
void Left (int s);
void Right (int s);
void Horn (void);
void powerMotor(float left, float right);

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
          DownBut(state);
          digitalWrite(led_pin, LOW);
          break;

          case 444:
          LeftBut(state);
          digitalWrite(led_pin, LOW);
          break;

          case 666:
          RightBut(state);
          digitalWrite(led_pin, LOW);
          break;

          case 888:
          UpBut(state);
          digitalWrite(led_pin, LOW);
          break;

          case 456:
          //ack
          digitalWrite(led_pin, LOW);
          break;

          default:
          break;
        }

        //Takes state and applys motor values
        PerformState(state);
      }
    delay(5);

    //Light off, no signal!
    digitalWrite(led_pin, HIGH);
  }

  void PerformState (int state)
  {
    switch (state)
    {
      case 2:
      powerMotor(0, 0);
      break;

      case 4:
      powerMotor(0, 50);
      break;

      case 5:
      powerMotor(50, 50);
      break;

      case 6:
      powerMotor(50, 0);
      break;

      case 7:
      powerMotor(10, 100);
      break;

      case 8:
      powerMotor(100, 100);
      break;

      case 9:
      powerMotor(100, 10);
      break;
    }
  }

  void DownBut (int s)
  {
    switch (s)
    {
      case 8:
      state = 5;
      break;

      case 9:
      state = 6;
      break;

      case 7:
      state = 4;
      break;

      case 5:
      state = 2;
      break;

      case 6:
      state = 2;
      break;

      case 4:
      state = 2;
      break;
    }
  }

  void UpBut (int s)
  {
    switch (s)
    {
      case 2:
      state = 5;
      break;

      case 5:
      state = 8;
      break;

      case 6:
      state = 9;
      break;

      case 4:
      state = 7;
      break;

      case 8:
      Horn();
      break;
    }
  }

  void LeftBut (int s)
  {
    switch (s)
    {
      case 8:
      state = 7;
      break;

      case 9:
      state = 8;
      break;

      case 5:
      state = 4;
      break;

      case 6:
      state = 5;
      break;

      case 2:
      state = 4;
      break;
    }
  }

  void RightBut (int s)
  {
    switch (s)
    {
      case 7:
      state = 8;
      break;

      case 8:
      state = 9;
      break;

      case 4:
      state = 5;
      break;

      case 5:
      state = 6;
      break;

      case 2:
      state = 6;
      break;
    }
  }

//Blows a single tone horn
  void Horn (void)
  {

  }

//Takes in percentage of left and right motors and outputs to analog
  void powerMotor(float left, float right)
  {
    //Multiply input (percentage) by powermax to get equivalent integer
    int powerLeft = (left / 100) * powerMax;
    int powerRight = (right / 100) * powerMax;

    //write to motors
    analogWrite(motorLeft, powerLeft);
    analogWrite(motorRight, powerRight);
  }
