/***** INFO **************************************************
 * nlantau, 2021-05-18
 * 
 * Read ADC (10-bit) and output to PWM (8-bit)
 *
 ************************************************************/

#define POTM A0
#define LED 6
#define BUTTON 3
#define MAX 255

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
}


void loop() {
  //int res = analogRead(POTM);
  int res = 127;

  while (digitalRead(BUTTON) == HIGH) {
    analogWrite(LED, 0);
  }


  print_res(res);
  analogWrite(LED, res);

  delay(1000);
}


void print_res(int value) {
  Serial.println((String)"ADC-value: " + value + "\tPWM-value: " + (value >> 2) + "\tLED at: " + ((float)(value >> 2)/MAX) * 100 + "%");
}