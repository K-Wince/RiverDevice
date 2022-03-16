// Demo Prototype Code : 12.15.2021 : Kaden Wince
// Description: Interfaces the arduino with multiple sensors for the RFP project which include: hall effect sensor(water flow),
// magnetic reed switch(water toxicity), and ultrasonic sensor(water level)

// Num Includes
#include <LiquidCrystal.h>
#include <math.h>

// Variables Used
  // Reed Switch
  bool reedOn = false; // Boolean value for whether the reed switch is open or closed
  // Potentiometer
  int potMode = 1;     // 1 = Hall Effect Sensor, 2 = Ultrasonic Sensor, 3 = Reed Switch
  // LCD Screen
  const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11; // Labels the pins for the LCD display
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    // Creates the LCD display using those pins and sets it to an object
  // Ultrasonic Sensor
  long duration;              // Duration measures the time between sound waves sent and receive
  int distance;               // Distance is the distance between the speakers and object its measuring
  // Hall Effect Sensor
  int count;                  // The count of the hall effect pulses
  const int interval = 1000;  // The interval of when it calculates the rpm in milliseconds
  int prevMillis = 0;         // Storing of the previous millisecond mark to keep track of time
  bool onState = false;       // Debounce variable
  float velocity = 0;


// Pins for the sensors
  // Digital Pins
  const int hallEffectPin = 2;
  const int reedPin = 3;
  const int trigPin = 6;
  const int echoPin = 7;
  // Analog Pins
  const int analogPotPin = 1;


void setup() {
  Serial.begin(9600);

  // Set pin mode and initalize the LCD and also set the interrupt
  pinMode(reedPin, INPUT_PULLUP);                                                   // Set the pin the magnetic reed switch is in to INPUT_PULLUP
  pinMode(trigPin, OUTPUT);                                                         // Set the pin the trigger part of ultrasonic is in to OUTPUT
  pinMode(echoPin, INPUT);                                                          // Set the pin the echo part of ultrasonic is in to INPUT
  pinMode(hallEffectPin, INPUT);                                                    // Set the pin the  hall effect sensor is put in to INPUT
  attachInterrupt(digitalPinToInterrupt(hallEffectPin), detectMagnetOpen, CHANGE);  // Set the interrupt pin to a function and have it activate when the voltage changes
  lcd.begin(16,2);                                                                  // Begin the LCD with 16 columms and 2 rows
}

void loop() {
  // Do the checking for the reed switch to see if it had been activated
  if(digitalRead(reedPin) == 1){
    reedOn = true;               // If the reed switch is closed and there is voltage going through then set the on state to true
  } else {
    reedOn = false;              // Else set it to false
  }
  
  // Do the checking of the potentiometer to see what value it is
  if(analogRead(analogPotPin) >= 666){ potMode = 1; }                                    // If the pot is in the left 1/3 then set it to Water Flow mode
  if(analogRead(analogPotPin) >= 333 && analogRead(analogPotPin) <= 666){ potMode = 2; } // If the pot is in the middle 1/3 then set it to Water Level mode
  if(analogRead(analogPotPin) >= 0 &&  analogRead(analogPotPin) <= 333){ potMode = 3; }  // If the pot is in the right 1/3 then set it to Water Toxicity mode

  // Do the calculations from the hall effect sensor to gather the water flow rate
  int currentMillis = millis();                 // Set a value to what the current millisecond is so you can compare
  if(currentMillis - prevMillis >= interval){
    // Rpm is calculated by taking the count of pulses from sensor and dividing by 4 since there is that many in a rotation and 6then dividing by time passed to get rps
    // and then multiplying by 60 to get rpm
    double rpm = ((count / 4) * 60) / ((currentMillis - prevMillis) / 1000); 
    prevMillis = currentMillis;           // Resets the timer
    count = 0;                            // Resets the count of pulses
    velocity = (2 * M_PI * 0.034 * rpm) / 60;
  }
  
  // Print out the stuff to the lcd screen
  if(potMode == 1){                  // Water Flow LCD Mode
    lcd.setCursor(0,0);              // Sets the cursor to the 1st column in the first row
    lcd.print("Water Flow:    ");    // Prints the string to that location
    lcd.setCursor(0,1);              // Moves the cursor to the 1st column in the second row
    lcd.print(velocity);             // Prints at the location
    lcd.print(" m/s");               // Prints at the location
  }
  if(potMode == 2){                  // Water Level Mode
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Printing to the lcd the distance from the sensor
    lcd.setCursor(0,0);              // Set the cursor to 1st column of 1st row
    lcd.print("Water Level:   ");    // Print the string at that location
    lcd.setCursor(0,1);              // Set the cursor to 1st column of 2nd row
    lcd.print("                  "); // Clear that column
    lcd.setCursor(0,1);              // Set it again
    lcd.print(distance);             // Print out the distance
    lcd.print(" cm");                // Print the measurement after it
  }
  if(potMode == 3){
    lcd.setCursor(0,0);                                  // Set the cursor to 1st column of 1st row
    lcd.print("Water Toxicity:");                        // Print the string at that location
    lcd.setCursor(0,1);                                  // Set the cursor to 1st column of 2nd row
    if(!reedOn){ lcd.print("Not Toxic          "); }    // Print the string at the location if the switch is open
    if(reedOn){ lcd.print("Toxic!!             "); }    // Print the string at the location if the switch is not open
  }

  delay(200);
}

void detectMagnetOpen(){                                     // Interrupt Function set on INTERRUPT pin 0
  if(onState == false && digitalRead(hallEffectPin) == 1){   // If the hall effect sensor is not on and the pin shows as having 5V
    onState = true;                                          // Sets the onState to true to debounce and prevent misinputs
    count++;                                                 // Sets the count of the pulse up by one
    delay(200);                                              // Gives a slight wait time before it allows another pulse to be read to prevent misinputs
  }
  if(onState == true && digitalRead(hallEffectPin) == 0){    // If the hall effect sensor is on and the pin shows as having 0V
    onState = false;                                         // Sets the onState to false to debounce and prevent misinputs
  }
}
