
int switchState = 0;
void setup() {
  pinMode(12,OUTPUT);
  pinMode(2,INPUT); 
  // Setup serial port for MIDI communication
  Serial.begin(31250); 
}
void loop() {
switchState = digitalRead(2);
//this reads from pin 2

if (switchState == LOW) {
// the button is not pressed

  digitalWrite(12, HIGH);
  // send CC 102 on channel 1 with value 0 to turn OFF Global Bypass on Strymon Timeline
      midiCc(1, 102, 0);    
  }
else {

  // the button is pressed
  
  digitalWrite(12, LOW);
  // send CC 102 on channel 1 with value 0 to turn OFF Global Bypass on Strymon Timeline
      midiCc(1, 102, 127);
  delay(50);
  }
} 

void midiCc(int channel, int command, int value) {
  Serial.write(175 + channel);
  Serial.write(command);
  Serial.write(value);
  }
 

