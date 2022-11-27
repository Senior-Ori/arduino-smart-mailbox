
//int analogPin = 3;
//int data = 0;
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String dataInput = Serial.readStringUntil('\r');
   
    if (dataInput == "on") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("LED Is On");
    }
    if (dataInput=="off") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("LED Is Off");
    }
  }
}