const int threshold = 850;                  // Values above the threshold means the laser is on
const int pulseReadAccuracy = 5;            // How accurate the pulses are read to
const int delayLength =  500;               // Length of pulse for "-", length of delay between separate characters
const int shortDelayLength = delayLength/2; // Length of pulse for ".", length of delay between separate morse code symbols ("." or "-")


int recordLengthOfPulse() { // This waits until the laser turns off, then returns how long it was on
  int pulseLength = 0;
  int val = analogRead(A0);
  
  while (val > threshold) {
    delay(pulseReadAccuracy);
    pulseLength += pulseReadAccuracy;
    val = analogRead(A0);
  }
  return pulseLength;
}

int recordLengthOfBreak() { // This waits until the laser turns on, and returns how long it was off
  int offLength = 0;
  int val = analogRead(A0);
  
  while (val < threshold) {
    delay(pulseReadAccuracy);
    offLength += pulseReadAccuracy;
    val = analogRead(A0);
  }
  return offLength;
}



void setup() {
  
  pinMode(A0, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  while (analogRead(A0) < threshold) {} // Wait for a pulse to begin
  Serial.println("Pulse Started");
  
  int pulseLength = recordLengthOfPulse();
  Serial.println("The pulse was " + String(pulseLength) + "ms long");

  // Record length of delay here 
  
}
