// Morse code for Alphabet, taken from https://forum.arduino.cc/index.php?topic=131603.0
const String morseTable[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",   // A-G
                             "....", "..", ".---", "_._", ".-..", "--", "-.",   // H-N
                             "---", ".--.", "--.-", ".-.", "...", "-", "..-",   // O-U
                             "...-", ".--", "-..-", "-.--", "--.."              // V-Z
                            };

const char alphabetTable[] = {'a','b','c','d','e','f',
                              'g','h','i','j','k','l',
                              'm','n','o','p','q','r',
                              's','t','u','v','w','x',
                              'y','z'
                             };

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
  
  while (val < threshold && offLength < 2000) {
    delay(pulseReadAccuracy);
    offLength += pulseReadAccuracy;
    val = analogRead(A0);
  }
  return offLength;
}

String findChar(String morseString) {
  for (int i =0;i<26;i++) {
    if (String(morseTable[i]) == morseString) {
      return String(alphabetTable[i]);
    }
  }
// If we reach the end of this loop, the morse code was not found.
  Serial.println("ERROR! Morse string: " + morseString + " not recognized!");
  return "";
}



void setup() {

  pinMode(A0, INPUT);
  Serial.begin(9600);

  while (analogRead(A0) < threshold) {} // Wait for a pulse to begin
  Serial.println("Transmission started!");

  String totalWord;
  String morseString;
  while (true) {
    int pulseLength = recordLengthOfPulse();
//    Serial.println("The pulse was " + String(pulseLength) + "ms long");
    int breakLength = recordLengthOfBreak();
//    Serial.println("The delay was " + String(delayLength) + "ms long");
    
    if (pulseLength >= (shortDelayLength-50) && pulseLength <= (shortDelayLength+50)) {  // 50 is a tolerance that has worked well
      morseString += ".";
    } else if (pulseLength >= (delayLength-50) && pulseLength <= (delayLength+50)) {
      morseString += "-";
    } else {
      Serial.println("ERROR! Unrecognized pulse length!");
    }

    if (breakLength >= (shortDelayLength-50) && breakLength <= (shortDelayLength+50)) {  // 50 is a tolerance that has worked well
      // Nothing
    } else if (breakLength >= (delayLength-50) && breakLength <= (delayLength+50)) {
      totalWord += findChar(String(morseString));  // String cast here may be unnecessary
      morseString = "";
    } else if (breakLength >= (2000-50) && breakLength <= (2000+50)) {
      totalWord += findChar(String(morseString));
      Serial.println("Transmission over. The word is:" + totalWord);
      break;
    } else {
      Serial.println("ERROR! Unrecognized break length!");
    }
    
  }
  
}

void loop(){}
