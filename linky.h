struct LinkyData {
  char unit[10];
  char days[CHART_DAYS][30];
  unsigned int values[CHART_DAYS];
};

struct LinkyMetaData {
  double price;
};

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

boolean fillLinkyDataFromJson(JSONVar json, LinkyData* data, BandwidthData* bandwidthRef = nullptr) {
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
   
   if (bandwidthRef != nullptr) {
     // Use bandwidth dates as reference
     Serial.println("Using bandwidth reference for date alignment");
     
     for (int i = 0; i < CHART_DAYS; i++) {
       sprintf(data->days[i], "%s", bandwidthRef->days[i]);
       
       // Find matching date in Linky data
       data->values[i] = 0; // Default to 0 if not found
       
       for (int j = 0; j < size; j++) {
         const char* linkyDate = (const char*) json["interval_reading"][j]["date"];
         if (strcmp(linkyDate, bandwidthRef->days[i]) == 0) {
           data->values[i] = atoi((const char*) json["interval_reading"][j]["value"]);
           break;
         }
       }
       
       Serial.printf("linky[%i] - %s -> %i\n", i, data->days[i], data->values[i]);
     }
   } else {
     // Original behavior - take last CHART_DAYS entries
     if (size < CHART_DAYS) return false;

     for (int i = 0, id = size - CHART_DAYS; i < CHART_DAYS; i++, id++) {
       sprintf(data->days[i], "%s", (const char*) json["interval_reading"][id]["date"]);
       data->values[i] = atoi((const char*) json["interval_reading"][id]["value"]);
       Serial.printf("linky[%i] - %s -> %i\n", id, data->days[i], data->values[i]);
     }
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
