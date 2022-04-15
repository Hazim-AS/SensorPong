#include <ArduinoJson.h>

char json[] = "{\“nbrBalle\”:10,\"vitesse\”:255,\”zone\”:\”1\”}";


void setup() {
  Serial.begin(9600);
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& key1 = jsonBuffer.parseObject(json);
  int abc = key1["nbrBalle"];
  Serial.print(abc);

}

void loop() {




}
