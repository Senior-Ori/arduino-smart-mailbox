
//int analogPin = 3;
//int data = 0;
int i= 0;
int g=0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

//receiving time of the data takes unnecessary amount of time..
void loop() {
  if (Serial.available() > 0) {
    String dataInput = Serial.readStringUntil('\r');

    if (dataInput == "on") {
      PORTB = B00100000;
      String lol = String("LED Is On, took:[")+ String(i)+String(",")+String(g)+String(" x IntMaxNubmer(2,147,483,647)")+String("] attempts.");
      Serial.write(lol.c_str());
    }
    if (dataInput == "off") {
      PORTB = B00000000;
      String lol = String("LED Is On, took:[")+ String(i)+String(",")+String(g)+String(" x IntMaxNumber(2,147,483,647)")+String("] attempts.");
      Serial.write(lol.c_str());
    }
  }else if (i<0) {
  i=0;
  g++;
  }
  else {
    i++;
  }
}