void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.readStringUntil('\r') == "go")
    Serial.println("name");
  delay(10);
}