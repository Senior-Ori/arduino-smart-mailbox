#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <stdio.h>
#include <string.h>


const unsigned int MAX_INPUT = 256;
const byte LEDs[] = { 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000 };
char prevIRs[]= {'[','0',',','0',',','0',',','0',']'};
bool flagWrite= false;
byte ledMapB = 0b00000000;
char jsonStr;

void setup() {
  Serial.begin(57600);
  
  DDRD &= B11111111;

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void serialWrite(const char * var,const char * value){
  strncat(var, value, strlen(var));

  Serial.write(value);
  flagWrite=false;
}



void irRead(){
  const char IRs[] = {'[',digitalRead(4)+'0',',',digitalRead(5)+'0',',',digitalRead(6)+'0',',',digitalRead(7)+'0',']'};
  if (!(strcmp(IRs, prevIRs)==0))
  serialWrite("\"ir\":",IRs);
  strcpy(prevIRs, IRs);
  // OriPrinter("","");
  
//   char str[5];
// for (int i=0;i<4;i++){
//   sprintf(str, "%d", IRs[i]);
  
//   }
  
}
void processData(const char* input) {
  StaticJsonDocument<256> doc;  //set efficient size for jsonDoc
  DeserializationError err = deserializeJson(doc, input);

  // {"command":"triggerLed","leds":[-1,-1,-1,-1]}

  if (err) {
    Serial.print("ERRROR: ");
    Serial.println(err.c_str());
    return;  //break, cos you got error..
  }

  const char* command = doc["command"];
  int ledOnOff[4];
  int count = 0, flag = 1;
  for (int i = 0; i < 4; i++) {
    ledOnOff[i] = doc["leds"][i];
    if (ledOnOff[i] == 1) {
      ledMapB |= LEDs[i + 2];
      PORTB = ledMapB;
      count++;
    } else if (ledOnOff[i] == 0) {
      ledMapB &= ~LEDs[i + 2];
      PORTB = ledMapB;
    } else flag = 0;
  }
  if (flag)
    if (count) serialWrite("msg","Led Is On");
    else serialWrite("msg","Led Is Off");
    flagWrite=true;

  if (String(command) == "triggerLed") {
    ledMapB ^= -1;
    PORTB = ledMapB;
    serialWrite("msg","all LED has been triggered");
    flagWrite=true;
  }
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

void loop() {
  irRead();
  while (Serial.available() > 0)
    processIncomingByte(Serial.read());
  if (flagWrite) serialWrite("\0","\0");
  
}