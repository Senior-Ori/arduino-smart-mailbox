
const unsigned int MAX_INPUT = 50;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  //Serial.write("on\r\n");
}

void processData(const char* data) {
  // Serial.print("line:[");
  // for (int i =0;i<MAX_INPUT;i++) {Serial.print(data[i],HEX);Serial.print(",");}
  // Serial.print("]\n");
  //Serial.print(String(data));
  if (String(data) == "on") {
    PORTB = B00100000;
    String lol = String("LED Is On, took:[") + String(" x IntMaxNubmer(2,147,483,647)") + String("] attempts.") + String(data);
    Serial.write(lol.c_str());
  }
  if (String(data) == "off") {
    PORTB = B00000000;
    String lol = String("LED Is On, took:[") + String(" x IntMaxNumber(2,147,483,647)") + String("] attempts.");
    Serial.write(lol.c_str());
  }
  if (data[0] == 'o') {
    PORTB = B00100000;
    Serial.write(String("o2").c_str());
  }
  if (data[0] == 'b') {
    PORTB = B00100000;
    Serial.write(String("b").c_str());
  }
  if (data[0] == "'") {
    PORTB = B00100000;
    Serial.write(String("'").c_str());
  }
  if (data[0] == "'") {
    PORTB = B00100000;
    Serial.write(String("'").c_str());
  }
}

void processIncomingByte(const byte inByte) {
  //   Serial.print("char:");
  // Serial.println(inByte);
  static char inputLine[MAX_INPUT];
  static unsigned int inputPos = 0;

  switch (inByte) {
    case 'o':
      Serial.print("o");
      break;
    case '\'':
      Serial.write(String("'").c_str());
      break;
    case 'b':
      Serial.write(String("b").c_str());
      break;
    case '0':
      Serial.write(String("0").c_str());
      break;
    case '\0':
      Serial.write(String("NULL").c_str());
      break;
    case '\001':
      Serial.write(String("Start of Header").c_str());
      break;
    case '\002':
      Serial.write(String("Start of Text").c_str());
      break;
    case '\003':
      Serial.write(String("End of Text").c_str());
      break;
    case '\004':
      Serial.write(String("End of Transaction").c_str());
      break;
    case '\005':
      Serial.write(String("Enquiry").c_str());
      break;
    case '\006':
      Serial.write(String("Acknowledgement").c_str());
      break;
    case '\007':
      Serial.write(String("Bell").c_str());
      break;case '\b':
      Serial.write(String("Backspace").c_str());
      break;case '\t':
      Serial.write(String("Horizontal Tab").c_str());
      break;case '0х60':
      Serial.write(String("'").c_str());
      break;
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
  while (Serial.available() > 0) {
    processIncomingByte(Serial.read());
  }
}