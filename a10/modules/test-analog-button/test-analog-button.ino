void setup() {
  Serial.begin(9600);

  pinMode(A6, INPUT_PULLUP);
}

void loop() {
  Serial.println(analogRead(A6));

}
