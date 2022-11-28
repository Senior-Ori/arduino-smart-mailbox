
const unsigned int MAX_INPUT = 50;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void processData(const char* data) {
  String lol = String(data);
  Serial.write(lol.c_str());
  // if (data == "on") {
  //   PORTB = B00100000;
  //   String lol = String("LED Is On, took:[") + String(" x IntMaxNubmer(2,147,483,647)") + String("] attempts.");
  //   Serial.write(lol.c_str());
  // }
  // if (data == "off") {
  //   PORTB = B00000000;
  //   String lol = String("LED Is On, took:[") + String(" x IntMaxNumber(2,147,483,647)") + String("] attempts.");
  //   Serial.write(lol.c_str());
  // }
}

void processIncomingByte(const byte inByte) {
  static char inputLine[MAX_INPUT];
  static unsigned int inputPos = 0;

  switch (inByte) {
    case '\n':
      inputLine[inputPos] = 0;  //terminating null byte

      //terminator reached! process inputLine here...
      processData(inputLine);


      //reset buffer for next time
      inputPos = 0;
      //return inputLine;
      break;

    case '\r': break;  //discard carriae return


    default:
      // keep adding if not full ...allow for terminating null byte
      if (inputPos < (MAX_INPUT - 1)) inputLine[inputPos++] = inByte;
      break;
  }
}

//receiving time of the data takes unnecessary amount of time..
void loop() {
  while (Serial.available() > 0)
    processIncomingByte(Serial.read());
}