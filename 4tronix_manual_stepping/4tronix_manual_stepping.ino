// mostly pulled from http://www.4tronix.co.uk/arduino/Stepper-Motors.php lol

int motorPin1 = 8;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)

int motorSpeed = 1200;  // stepper speed
int countsperrev = 512; // number of steps per full revolution
int revs_per_door_action = 0; // need to figure this out!
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int light_detector_pin = 12;
int light_detector_value = 0;
int previous_detector_value = 0;

//////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(light_detector_pin, INPUT);
  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////
void loop() {
  light_detector_value = digitalRead(light_detector_pin);
  
  if (light_detector_value == previous_detector_value) {
    return;
  }

  previous_detector_value = light_detector_value;
  
  for (int i = 0; i < countsperrev; i++) {
    if (light_detector_value == HIGH) {
      clockwise();
    } else {
      counterclockwise();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)
void counterclockwise() {
  for(int i = 0; i < 8; i++) {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise() {
  for(int i = 7; i >= 0; i--) {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out) {
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
