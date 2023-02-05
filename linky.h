/* Daily.json
{
    "unit": "Wh",
    "data": [
        {
            "date": "2021-01-17",
            "value": 3500
        },
        ...
    ]
}
*/

/* maxpower.json
{
    "unit": "VA",
    "data": [
        {
            "date": "2021-01-17 09:22:00",
            "value": 3500
        },
 
    ]
}
*/

struct LinkyData {
  char unit[10];
  char days[LINKY_DAYS][30];
  unsigned int values[LINKY_DAYS];
};

boolean fillLinkyDataFromJson(JSONVar json, LinkyData* data) {
  if (!json.hasOwnProperty("unit")) {
    Serial.println("fillDataFromJson: unit key not found");
    return false;
  }
  if (!json.hasOwnProperty("data")) {
    Serial.println("fillDataFromJson: data key not found");
    return false;
  }
  
  sprintf(data->unit, "%s", (const char*) json["unit"]);
  int size = json["data"].length();
  
  Serial.printf("linky data length: %i\n", size);
  if (size < LINKY_DAYS) return false;
  
  for (int i = 0, id = size - LINKY_DAYS; i < LINKY_DAYS; i++, id++) {
    sprintf(data->days[i], "%s", (const char*) json["data"][id]["date"]);
    data->values[i] = (unsigned int) int(json["data"][id]["value"]);
  }
  return true;
}

