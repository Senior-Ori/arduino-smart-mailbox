#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

const unsigned int MAX_INPUT = 50;

void setup() {
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  const char* input =  "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  StaticJsonDocument<256> doc;
  DeserializationError err=deserializeJson(doc,input);

  if (err) {
  Serial.print("ERRROR: ");
  Serial.println(err.c_str());
  return; //break, cos you got error..
  }

  const char* sensor = doc["sensor"];
  long time = doc["time"];
  float lat = doc["data"][0];
  float lon = doc["data"][1];
  
  Serial.println(sensor);  
  Serial.println(time);  
  Serial.println(lat);  
  Serial.println(lon);
  
}

void processData(const char* data) {
  if (String(data) == "on") {
    PORTB = B00100000;
    Serial.write("LED Is On");
  }
  if (String(data) == "off") {
    PORTB = B00000000;
    Serial.write("LED Is Off");
  }
  if (String(data) == "triggerLed") {
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