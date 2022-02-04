/***** INFO **************************************************
 *
 *
 *
 *
 ************************************************************/

#define POTM A0
#define LED 6
#define MAX 255

void setup() {
  Serial.begin(19200);
  pinMode(LED, OUTPUT);
}


void loop() {
  int res = analogRead(POTM);
  print_res(res);
  analogWrite(LED, res/4);
  delay(100);
}


void print_res(int value) {
  Serial.println((String)"ADC-value: " + value + "\tPWM-value: " + (value/4) + "\tLED at: " + ((float)(value/4)/MAX)*100 + "%");
}