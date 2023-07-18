struct LinkyData {
  char unit[10];
  char days[LINKY_DAYS][30];
  unsigned int values[LINKY_DAYS];
};

struct LinkyMetaData {
  double price;
};


boolean fillLinkyDataFromJson(JSONVar json, LinkyData* data) {
  if (!json.hasOwnProperty("reading_type")) {
    Serial.println("fillLinkyDataFromJson: reading_type key not found");
    return false;
  }
  if (!json.hasOwnProperty("interval_reading")) {
    Serial.println("fillLinkyDataFromJson: interval_reading key not found");
    return false;
  }

  sprintf(data->unit, "%s", (const char*) json["reading_type"]["unit"]);
  int size = json["interval_reading"].length();

  Serial.printf("linky data length: %i\n", size);
  if (size < LINKY_DAYS) return false;

  for (int i = 0, id = size - LINKY_DAYS; i < LINKY_DAYS; i++, id++) {
    sprintf(data->days[i], "%s", (const char*) json["interval_reading"][id]["date"]);
    data->values[i] = atoi((const char*) json["interval_reading"][id]["value"]);
    Serial.printf("linky[%i] - %s -> %i\n", id, data->days[i], data->values[i]);
  }
  Serial.printf("Parsing end\n");
  return true;
}

boolean fillLinkyMetaDataFromJson(JSONVar json, LinkyMetaData* data) {
  if (!json.hasOwnProperty("price")) {
    Serial.println("fillLinkyMetaDataFromJson: price key not found");
    return false;
  }

  double price;
  sscanf(json["price"], "%lf", &price);
  data->price = price;
  Serial.println("Price");
  Serial.println(data->price);

  return true;
}

/* Daily.json
{
  "start": "2023-04-26",
  "end": "2023-05-11",
  "quality": "BRUT",
  "reading_type": {
    "unit": "Wh",
    "measurement_kind": "energy",
    "aggregate": "sum",
    "measuring_period": "P1D"
  },
  "interval_reading": [
    {
      "value": "5918",
      "date": "2023-04-26"
    },...
*/
