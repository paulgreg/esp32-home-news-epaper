struct BandwidthData {
  char unit[10];
  char days[CHART_DAYS][30];
  unsigned int values[CHART_DAYS];
};


boolean fillBandwidthDataFromJson(JSONVar json, BandwidthData* data) {
  if (!json.hasOwnProperty("reading_type")) {
    Serial.println("fillBandwidthDataFromJson: reading_type key not found");
    return false;
  }
  if (!json.hasOwnProperty("interval_reading")) {
    Serial.println("fillBandwidthDataFromJson: interval_reading key not found");
    return false;
  }

  sprintf(data->unit, "%s", (const char*) json["reading_type"]["unit"]);
  int size = json["interval_reading"].length();

  Serial.printf("bandwidth data length: %i\n", size);
  if (size < CHART_DAYS) return false;

  for (int i = 0, id = size - CHART_DAYS; i < CHART_DAYS; i++, id++) {
    sprintf(data->days[i], "%s", (const char*) json["interval_reading"][id]["date"]);
    data->values[i] = atoi((const char*) json["interval_reading"][id]["value"]);
    Serial.printf("bandwidth[%i] - %s -> %i\n", id, data->days[i], data->values[i]);
  }
  Serial.printf("Parsing end\n");
  return true;
}