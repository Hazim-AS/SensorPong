#include <ArduinoJson.h>
void setup() {
  // put your setup code here, to run once:
  // allocate the memory for the document
  Serial.begin(9600);
const size_t CAPACITY = JSON_OBJECT_SIZE(1);
StaticJsonDocument<CAPACITY> doc;

// deserialize the object
 //char json[] = "{\"hello\":\"world\"}";

char json[] = "{\"nbrBalle\":\"54658\",\"vitesse\":\"255\",\"zone\":\"1\"}";
Serial.println(json);
deserializeJson(doc, json);


// extract the data
JsonObject object = doc.as<JsonObject>();
const char* world = object["nbrBalle"];

 
 Serial.println(world);
}

void loop() {
  // put your main code here, to run repeatedly:

}
