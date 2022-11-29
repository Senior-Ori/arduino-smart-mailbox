#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

const unsigned int MAX_INPUT = 256;

void setup() {
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void processData(const char* input) {
  StaticJsonDocument<256> doc;//set efficient size for jsonDoc
  DeserializationError err=deserializeJson(doc,input);

  //test --> {"command":"-1","leds":[1,0,0,0]}

  if (err) {
  Serial.print("ERRROR: ");
  Serial.println(err.c_str());
  return; //break, cos you got error..
  }

  const char* command = doc["command"];
  int ledOnOff[4];
  for (int i=0;i<4;i++) ledOnOff[i]=doc["leds"][i];

  



  if (ledOnOff[0]) {
    PORTB = B00100000; Serial.write("Led Is On");}
    else{PORTB = B00000000; Serial.write("Led Is Off");}

  if (command == "triggerLed") {
    PORTB ^= -1;
    Serial.write("LED has been triggered");
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

//receiving time of the data takes unnecessary amount of time..
void loop() {
  while (Serial.available() > 0)
    processIncomingByte(Serial.read());
    
}


// char* input;
// size_t inputLength; (optional)