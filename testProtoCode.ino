// Testing prototype code file

int count;                  // The count of the hall effect pulses
const int interval = 1000;  // The interval of when it calculates the rpm in milliseconds
int prevMillis = 0;         // Storing of the previous millisecond mark to keep track of time
bool onState = false;       // Debounce variable


int hallEffectPin = 2; // Pin for the hall effect sensor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                                               // Begin the serial at 9600 Baud Rate
  pinMode(hallEffectPin, INPUT);                                                    // Set the pin the sensor is put in to input
  attachInterrupt(digitalPinToInterrupt(hallEffectPin), detectMagnetOpen, CHANGE);  // Set the interrupt pin to a function and have it activate when the voltage changes
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentMillis = millis();
  if(currentMillis - prevMillis >= interval){
    // Rpm is calculated by taking the count of pulses from sensor and dividing by 4 since there is that many in a rotation and 6then dividing by time passed to get rps
    // and then multiplying by 60 to get rpm
    double rpm = ((count / 4) * 60) / ((currentMillis - prevMillis) / 1000); 
    prevMillis = currentMillis;           // Resets the timer
    count = 0;                            // Resets the count of pulses
    Serial.println(rpm);                  // Print out the rpm
    // l_min =  rpm * however many liters is displaced by one rotation;
  }
}

void detectMagnetOpen(){
  if(onState == false && digitalRead(hallEffectPin) == 1){   // If the hall effect sensor is not on and the pin shows as having 5V
    onState = true;                                          // Sets the onState to true to debounce and prevent misinputs
    count++;                                                 // Sets the count of the pulse up by one
    delay(200);                                              // Gives a slight wait time before it allows another pulse to be read to prevent misinputs
  }
  if(onState == true && digitalRead(hallEffectPin) == 0){    // If the hall effect sensor is on and the pin shows as having 0V
    onState = false;                                         // Sets the onState to false to debounce and prevent misinputs
  }
}
