
const unsigned int MAX_INPUT = 50;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void processData (const char * data){

}

void processIncomingByte(const byte inByte){
  static char inputLine [MAX_INPUT];
  static unsigned int inputPos = 0;
}

//receiving time of the data takes unnecessary amount of time..
void loop() {
  if (Serial.available() > 0) {
    //this line take 1 sec, i shall do it manualy
    String dataInput = Serial.readStringUntil('\r');

    if (dataInput == "on") {
      PORTB = B00100000;
      String lol = String("LED Is On, took:[")+String(" x IntMaxNubmer(2,147,483,647)")+String("] attempts.");
      Serial.write(lol.c_str());
    }
    if (dataInput == "off") {
      PORTB = B00000000;
      String lol = String("LED Is On, took:[")+String(" x IntMaxNumber(2,147,483,647)")+String("] attempts.");
      Serial.write(lol.c_str());
    }
  }
}