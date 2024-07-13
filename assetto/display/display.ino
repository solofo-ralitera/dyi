// PWM 12V
// help: https://forum.arduino.cc/index.php?topic=92776.0 => avec circuit simple pour pwm 12v
// https://forum.allaboutcircuits.com/threads/tach-frequency-calculation.98285/ => avec correspondance rpm/hz
// https://www.youtube.com/watch?v=n7bltLKnRrs / https://github.com/daniel-centore/arduino-tone-library => ne fonctionne pas sur 1.8.7 leonardo
// Build-in function: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

#define TachoPin 5

void setup()
{
  Serial.begin(19200);
  pinMode(TachoPin, OUTPUT);
}
   

void loop(){

 if (Serial.available() > 0) {
    char buffer[] = {' ',' ',' ',' ',' ',' ',' ', ' '}; // Receive up to 7 bytes
    Serial.readBytesUntil('\n', buffer, 8);

    // Get message as string and remove the first char
    String message((char*)buffer);
    message = message.substring(1);
    
    // Tacho Rpm message
    if(buffer[0] == 'r') {
      // Pour 4 cylindres => Hz = RPM / 30
      tone(TachoPin, message.toInt() / 30, 1500);
    }

    /*
    message = Serial.readString();
    messageKey = message.substring(0, 1);
    
    // Tacho Rpm message
    if (messageKey == "r") {
      // Pour 4 cylindres => Hz = RPM / 30
      tone(TachoPin, message.substring(1).toInt() / 30, 1500);
    }
    */
 }
}
