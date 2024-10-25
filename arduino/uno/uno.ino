void setup() {
  Serial.begin(1200);
}

void loop() {
  if (Serial.available()) {
    while (Serial.readStringUntil('z') != "admin") {
      if (Serial.availableForWrite()) {
        Serial.println("avtech-f8369be5fff1");
        delay(100);
      }
    }
    while (Serial.readStringUntil('z') != "default") {
      if (Serial.availableForWrite()) {
        Serial.println("Password");
        delay(100);
      }
    }
    if (Serial.availableForWrite()) {
      Serial.println("> ");
      delay(100);
    }
  }
}