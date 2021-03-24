/*
Basic test for robot car. Input with 4 motors, only controlling left and right side 0-100% power via PWM. On/off switch as a parking brake holding 0, button to reset to 0 (but doesn't hold).
Inputs: Left wheels power up, left wheels power down, right wheels power up, right wheels power down, set to 0, safety switch
*/

//Pin OUTPUTS
int motorLeft = 3; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int motorRight = 6; //Must be a PWM Pins:3, 5, 6, 9, 10, 11
int safetyLight = 7; //13 supposed to be board LED

//Pin INPUTS
int leftFwd = 12;
int leftRear = 9;
int rightFwd = 13;
int rightRear = 11;
int reset = 10;
int safety = 8;

//initalize variables
const int inc = 64; //25 is 10%, 64 is 25%
const int wait = 500;
const int powerMax = 255;
const int powerMin = 0;
int powerRight = 0;
int powerLeft = 0;

void setup() {
    Serial.begin(9600);

    //inputs
    pinMode(leftFwd, INPUT_PULLUP);
    pinMode(leftRear, INPUT_PULLUP);
    pinMode(rightFwd, INPUT_PULLUP);
    pinMode(rightRear, INPUT_PULLUP);
    pinMode(reset, INPUT_PULLUP);
    pinMode(safety, INPUT_PULLUP);

    //outputs
    pinMode(motorLeft, OUTPUT);
    pinMode(motorRight, OUTPUT);
    pinMode(safetyLight, OUTPUT);
}

void loop() {

    //while safety is in OFF position
    while (digitalRead(safety) == LOW)
    {
      //turn off light by safety
      digitalWrite(safetyLight, LOW);
      digitalWrite(LED_BUILTIN, LOW);

      //Check buttons using IFs in order up, down, reset.
      if (digitalRead(leftFwd) == LOW)
      {
        powerLeft += inc;
        if (powerLeft > powerMax)
        {
          powerLeft = powerMax;
        }
      }

      if (digitalRead(rightFwd) == LOW)
      {
        powerRight += inc;
        if (powerRight > powerMax)
        {
          powerRight = powerMax;
        }
      }

      if (digitalRead(leftRear) == LOW)
      {
        powerLeft -= inc;
        if (powerLeft < powerMin)
        {
          powerLeft = powerMin;
        }
      }

      if (digitalRead(rightRear) == LOW)
      {
        powerRight -= inc;
        if (powerRight < powerMin)
        {
          powerRight = powerMin;
        }
      }

      if (digitalRead(reset) == LOW)
      {
        powerLeft = 0;
        powerRight = 0;

      }

      //buttons analyzed, write PWM (analog) signal
      analogWrite(motorLeft, powerLeft);
      analogWrite(motorRight, powerRight);

      //serial debug
      Serial.println("L: " + String(powerLeft) + "\tR: " + String(powerRight));

      //Debounces and prevents multiple inputs by user.
      delay(wait);
    }

  //Safety is in ON position, zero out power
  powerLeft = 0;
  powerRight = 0;
  analogWrite(motorLeft, powerLeft);
  analogWrite(motorRight, powerRight);

  //Turn safety light on
  digitalWrite(safetyLight, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

  //serial debug
  Serial.println("L: " + String(powerLeft) + "%\tR: " + String(powerRight) + "\tSafety ON");

  //Debounces and prevents multiple inputs by user.
  delay(wait);
}
