// Morse code for Alphabet, taken from https://forum.arduino.cc/index.php?topic=131603.0
const String morseTable[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",   // A-G
                             "....", "..", ".---", "_._", ".-..", "--", "-.",    // H-N
                             "---", ".--.", "--.-", ".-.", "...", "-", "..-",    // O-U
                             "...-", ".--", "-..-", "-.--", "--.."               // V-Z
                            };

const char alphabetTable[] = {'a','b','c','d','e','f',
                        'g','h','i','j','k','l',
                        'm','n','o','p','q','r',
                        's','t','u','v','w','x',
                        'y','z'};
                        
// delayLength can be adjusted to transmit data faster or slower; however, 
// a longer delayLength will correspond to greater accuracy in reading data.
const int delayLength = 500;
const int shortDelay = delayLength/2;                    

// morseToPulse takes in a Morse code character morseStr, and then changes the
// output voltage based on the dots and dashes making up morseStr.
void morseToPulse(String morseStr) {
  int strLen = morseStr.length();

  for (int i =0;i<strLen;i++){
  // As per the standards of Morse code, a dot corresponds to a short pulse
  // and a dash, a long pulse.
    digitalWrite(7,HIGH);
    if (morseStr[i]== '.') {
      delay(shortDelay);
    }
    else if (morseStr[i]=='-') {
      delay(delayLength);
    }
    digitalWrite(7,LOW);
  // If we are still in the middle of morseStr, we need to give a short delay
  // to indicate that the current pulse is over and get ready to expect the next.
    if(i < strLen-1) delay(shortDelay);
  }
// Once we have output the character, we must give a long delay to tell the receiver
// to expect a new character.
  digitalWrite(7,LOW);
  delay(delayLength);
}

// findMorse finds the Morse code string from morseTable that corresponds to the
// input character.
String findMorse(char charInterest) {
  for (int i =0;i<26;i++) {
    if (alphabetTable[i] == charInterest) {
      return morseTable[i];
    }
  }
// If we reach the end of this loop, the character was not found.
  Serial.println("Input character not found.");
}

void setup() {
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  
  const String inputStr = "insertstringhere";
  const int strSize = inputStr.length();
  String morseOut[strSize];
  
  for (int i = 0; i < strSize; i++) {
    morseOut[i] = findMorse(inputStr[i]);
  }
  for (int i = 0;i<strSize;i++) {
    Serial.println(morseOut[i]);
    morseToPulse(morseOut[i]);
  }
}

void loop() {
}
