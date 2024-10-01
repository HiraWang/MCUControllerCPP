void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.readStringUntil('\r') == "go")
    Serial.println("name");
  else
    Serial.println("avtech-f8369be5fff1");
  delay(100);
}