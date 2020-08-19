// Arduino code.
// Takes input from a physical switch input on the Arduino board (pin2)
// and translates it into a MIDI Control Change message that is sent over a MIDI cable to another device.
// THIS VERSION: incorporates a check for a change in state of the switch. Looks for state changes
// so that the message is only sent if the pedal is pressed or released.
// Inspired by https://dikant.de/2015/01/18/diy-midi-footswitch-controller/


// Set Constants:
// pin to use for indicator LED
int ledPin = 12;
// pin that is connected to the footswitch
int switchPin = 2;

// initialise states:
int switchState = 0;
int switchLastState = 0;
int switchInitState = 0;
int messageStatus = 0;

// setup method
void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(switchPin, INPUT_PULLUP);

    // Setup serial port for MIDI communication
    Serial.begin(31250);

    // Is the switch pressed when we first power up the board? Read the pin
    switchInitState = digitalRead(switchPin);
    // Set the switchLastState to be this initial state
    switchLastState = switchInitState;
}

// the loop method is the main method for Arduino. 
// Will run when power is provided to the microcontroller.
void loop() {
    // read the switch state again to see if it has changed
    switchState = digitalRead(switchPin);

    // has the state changed?
    // if switchState NOT EQUAL to switchLastState, then run the code
    if (switchState != switchLastState) {
        switchLastState = switchState;
        if (switchState = switchInitState) {
        // if switch is in pressed state, send the pressed message
            if (messageStatus == 0) {
                // send on message and light up LED
                digitalWrite(ledPin, HIGH);
                // Send MIDI CC 102 on channel 1 with value 127
                midiCc(1, 102, 127);
                messageStatus = 1;
            } else {
                // send off message and turn off LED
                digitalWrite(ledPin, LOW);
                // Send MIDI CC 102 on channel 1 with value 127
                midiCc(1, 102, 0);
                messageStatus = 0;
            }
        }
    // delay for 50 milliseconds before checking for state change again
    // to deal with electrical switch 'bounce'
    delay(10);

  } // then go back to the top of the loop and check for state change again
}

// this method called when we want to send a message
void midiCc(int channel, int command, int value) {
    Serial.write(175 + channel);
    Serial.write(command);
    Serial.write(value);
}

