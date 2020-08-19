// pin to use for indicator LED
int ledPin = 12;
// pin that is connected to the footswitch
int buttonPin = 2;
 
int buttonState = 0;
int buttonLastState = 0;
int buttonInitState = 0;
 
int muteStatus = 0;
 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Setup serial port for MIDI communication
  Serial.begin(31250);
  
  // read current button state, a press is detected whenever
  // state changes to anything else than the init state
  buttonInitState = digitalRead(buttonPin);
  // we only want to do something on state changes
  buttonLastState = buttonInitState;
}
 
void loop() {
  buttonState = digitalRead(buttonPin);
  
  // has the state changed?
  // if buttonState NOT EQUAL to buttonLastState
  if (buttonState != buttonLastState) { 
    buttonLastState = buttonState;
    if (buttonState = buttonInitState) {
      // button is in pressed state, trigger action
      if (muteStatus == 0) {
        // mute and light up LED
        digitalWrite(ledPin, HIGH);
        // send CC 85 on channel 2 with value 0 to mute
        // mute group 6 on a Behringer X32
        midiCc(1, 102, 127);
        muteStatus = 1;
      } else {
        // unmute and turn off LED
        digitalWrite(ledPin, LOW);
        midiCc(1, 102, 0);
        muteStatus = 0;
      }
    }
    // workaround to prevent fluttering of button state
    delay(10);
  }
}
 
void midiCc(int channel, int command, int value) {
  Serial.write(175 + channel);
  Serial.write(command);
  Serial.write(value);
}

