//motor 1 connected between A01 and A02
//motor 2 connected between B01 and B02

int STBY = 10;    //standby
int gear = 4;
int aux = 13;
int handBoard = 2;

//Motor 1
int PWMA = 3;     //Speed control 
int AIN1 = 9;     //Direction
int AIN2 = 8;     //Direction

//Motor 2
int PWMB = 5;     //Speed control
int BIN1 = 11;    //Direction
int BIN2 = 12;    //Direction

int ch1;          // Left stick
int ch2;          // Right stick
int ch3;
int ch4;
int turn;         // Left stick
int turn2;        // Right stick
int buttonPress;
int switchFlip;

int val;
int val2;
int val3;
int val4;

void setup(){
  pinMode(6, INPUT);                      // Throttle
  pinMode(7, INPUT);                      // Elevation
  pinMode(13, INPUT);                     // AUX1
  pinMode(4, INPUT);                      // Gear
  pinMode(2, OUTPUT);                     // power to hand board

  pinMode(STBY, OUTPUT);                  // Standby

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);                  // pin for motor 1
  pinMode(AIN2, OUTPUT);                  // pin for motor 1

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);                  // pin for motor 2
  pinMode(BIN2, OUTPUT);                  // pin for motor 2
  Serial.begin(57600);                    // baud rate for serial monitor
  }
void loop(){
  ch1 = pulseIn(6, HIGH, 25000);          // interpriting the signal from the transmitter (Throttle)
  ch2 = pulseIn(7, HIGH, 25000);          // interpriting the signal from the transmitter (Elevation)
  ch3 = pulseIn(4, HIGH, 25000);          // interpriting the signal from the transmitter (Gear)
  ch4 = pulseIn(13, HIGH, 25000);         // interpriting the signal from the transmitter (Aux1)

  turn = map(ch1, 1000,2000, -500, 500);  // turning the ch1 values to -500, 500
  turn = constrain(turn, -255, 255);      // turning -500 to -255 and 500 to 255
  
  turn2 = map(ch2, 1000,2000, -500, 500); // turning the ch2 values to -500, 500
  turn2 = constrain(turn2, -255, 255);    // turning -500 to -255 and 500 to 255

  switchFlip = map(ch3, 1000,2000, -500, 500); // turning the ch2 values to -500, 500
  switchFlip = constrain(switchFlip, -255, 255);    // turning -500 to -255 and 500 to 255

  buttonPress = map(ch4, 1000,2000, -500, 500); // turning the ch2 values to -500, 500
  buttonPress = constrain(buttonPress, -255, 255);    // turning -500 to -255 and 500 to 255

  if (buttonPress == 255)
  {
    if(turn >= 50)
    {
      val = turn;                           // val = value of the ch1 (-255 to 255)
      move(1, val/3, 0);                      // move(motor 1, speed of val, clockwise)
    }
    if(turn <= -50)
    {
      val2 = turn;                          // val2 = value of the ch1 (-255 to 255)
      val2 = map(val2, -255, 255, 255, 0 ); // Inverting the speed from negative to positive
      move(1, val2/3, 1);                     // move(motor 1, speed of val2, counter-clockwise)
    }
   // if(turn >= 49 && turn <= -49)
   // {
     // move(1,0,1);
   // }
    delay(30);

    if(turn2 >= 50)
    {
      val3 = turn2;                            // val3 = value of the ch2 (-255 to 255)
      move(2, val3/3, 0);                     // move(motor 2, speed of val3, clockwise)
    }
    if(turn2 <= -50)
    {
      val4 = turn2;                         // val4 = value of the ch2 (-255 to 255)
      val4 = map(val4, -255, 255, 255, 0 ); // Inverting the speed from negative to positive
      move(2, val4/3, 1);                     // move(motor 2, speed of val4, counter-clockwise)
    }
   // if(turn2 >= 49 && turn2 <= -49)
    //{
     // move(2,0,1);
   // }
    delay(30);
  }
  else
  {
    move(1, 0, 0);
    move(2, 0, 0);
  }
  
  if(switchFlip <=5)
  {
    digitalWrite (handBoard, HIGH);
  }
  else
  {
    digitalWrite (handBoard, LOW);
  }
}
  void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 1 for B, 2 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }if(motor == 2){
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
  Serial.print("turn:");   //Serial debugging stuff
  Serial.println(turn);

  Serial.print("turn2:");  //Serial debugging stuff
  Serial.println(turn2);

  Serial.print("AUX1:");  //Serial debugging stuff
  Serial.println(buttonPress);
  }

void stop(){
//enable standby  
  digitalWrite(STBY, LOW);
}
