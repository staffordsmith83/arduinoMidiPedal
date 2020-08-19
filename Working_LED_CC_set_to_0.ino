// Arduino code.
// Takes input from a physical switch input on the Arduino board (pin2)
// and translates it into a MIDI Control Change message that is sent over a MIDI cable to another device.
// Inspired by https://dikant.de/2015/01/18/diy-midi-footswitch-controller/


// initialise the switchState
int switchState = 0;

// Define the message you want to send
int midiChannel = 1;
int midiCommand = 102;
int midiValue1 = 0;
int midiValue2 = 127;
// The provided values will send:
// MIDI CC 102 on channel 1 with value 0 or 127 to turn OFF or ON the
// Global Bypass function on a Strymon Timeline effect device.

// setup method
void setup() {
    pinMode(12,OUTPUT);
    pinMode(2,INPUT);
    // Setup serial port for MIDI communication
    Serial.begin(31250);
}

// the loop method is the main method for Arduino. 
// Will run when power is provided to the microcontroller.
void loop() {
    switchState = digitalRead(2);
    //this reads from pin 2

    if (switchState == LOW) {
    // the switch is not pressed
    digitalWrite(12, HIGH);
    // message that will be sent when switch is released
    midiCc(midiChannel, midiCommand, midiValue1);
    }

    else {
    // the switch is pressed
    digitalWrite(12, LOW);
    // message that will be sent when switch is triggered
    midiCc(midiChannel, midiCommand, midiValue2);
    delay(50);
    }
} 

// this method called by the loop() method
void midiCc(int channel, int command, int value) {
    Serial.write(175 + channel);
    Serial.write(command);
    Serial.write(value);
}
 

