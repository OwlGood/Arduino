#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX
const byte PIN_LED_R = 6;
const byte PIN_LED_G = 5;
const byte PIN_LED_B = 3;

byte rgbCalme[3] = { 97, 255, 0 };
byte rgbAlerte[3] = { 255, 30, 0 };
byte rgbDanger[3] = { 255, 0, 0 };

byte alertState = 0;

String content = "";
char character;

void setup() {
  Serial.begin(57600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  displayColor(rgbCalme);
  Serial.println("Enter AT commands:");
  mySerial.begin(57600);
}

void loop() {

  if (mySerial.available()) {

    while (mySerial.available()) {
      character = mySerial.read();
      content.concat(character);
    }
    updateAlerteState(content);
  }


  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void updateAlerteState(String alerteMessage) {

  if (alerteMessage.indexOf("ptc_alerte_") == -1) {
    return;
  }

    
  alerteMessage.remove(0, alerteMessage.indexOf("ptc_alerte_")+11);
  Serial.println(alerteMessage);

  if (alerteMessage == "V_calme") {
    Serial.println(alerteMessage);
    content = "";
    alertState = 0;
    displayColor(rgbCalme);
  }

  if (alerteMessage == "V_alerte") {
    Serial.println(alerteMessage);
    content = "";
    alertState = 1;
    displayColor(rgbAlerte);
  }

  if (alerteMessage == "V_danger") {
 
    content = "";
    alertState = 2;
    displayColor(rgbDanger);
  }
}

void displayColor(byte rgb[3]) {

  // Assigne l'état des broches
  // Version cathode commune
  analogWrite(PIN_LED_R, rgb[0]);
  analogWrite(PIN_LED_G, rgb[1]);
  analogWrite(PIN_LED_B, rgb[2]);
}