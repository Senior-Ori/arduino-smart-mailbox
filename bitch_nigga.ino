#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

const unsigned int MAX_INPUT = 256;

void setup() {
  Serial.begin(57600);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void processData(const char* input) {
  // StaticJsonDocument<256> doc;//set efficient size for jsonDoc
  // DeserializationError err=deserializeJson(doc,input);

  //const char* input =  "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  

  //const char* sensor = doc["sensor"];
  //long time = doc["time"];
  //float lat = doc["data"][0];
  //float lon = doc["data"][1];

  if (err) {
  Serial.print("ERRROR: ");
  Serial.println(err.c_str());
  return; //break, cos you got error..
  }



  if (String(input) == "on") {
    PORTB = B00100000;
    Serial.write("LED Is On");
  }
  if (String(input) == "off") {
    PORTB = B00000000;
    Serial.write("LED Is Off");
  }
  if (String(input) == "triggerLed") {
    if(PORTB == B00000000) PORTB = B00100000;
    else PORTB = B00000000;
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