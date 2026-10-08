struct LinkyData {
  char unit[10];
  char days[CHART_DAYS][30];
  unsigned int values[CHART_DAYS];
};

struct LinkyMetaData {
  double price;
};

/* Daily.json (v3 format)
{
  "idPrm": "07373806030184",
  "etapeMetier": "BRUT",
  "periode": {
    "dateDebut": "2026-09-22",
    "dateFin": "2026-10-07"
  },
  "typeValeur": "GLOBALE",
  "modeCalcul": "DIFF.INDEX",
  "pas": "P1D",
  "grandeur": [
    {
      "grandeurMetier": "CONS",
      "grandeurPhysique": "EA",
      "unite": "Wh",
      "points": [
        {
          "v": "5824",
          "d": "2026-09-22"
        },
        ...
*/

// Helper function to extract date part from timestamp (handles both "YYYY-MM-DD" and "YYYY-MM-DD HH:MM:SS")
void extractDatePart(char* dest, const char* source, size_t destSize) {
  if (destSize == 0) return;
  if (source == nullptr) {
    dest[0] = '\0';
    return;
  }

  // Copy up to 10 characters (YYYY-MM-DD) or until space/end
  size_t i = 0;
  while (i < destSize - 1 && source[i] != '\0' && source[i] != ' ' && i < 10) {
    dest[i] = source[i];
    i++;
  }
  dest[i] = '\0'; // Null-terminate
}

boolean fillLinkyDataFromJson(JSONVar json, LinkyData* data, BandwidthData* bandwidthRef = nullptr) {
  if (!json.hasOwnProperty("grandeur")) {
    Serial.println("fillLinkyDataFromJson: grandeur key not found");
    return false;
  }
  
  JSONVar grandeur = json["grandeur"][0]; // First (and only) element in array
  if (!grandeur.hasOwnProperty("unite") || !grandeur.hasOwnProperty("points")) {
    Serial.println("fillLinkyDataFromJson: unite or points key not found in grandeur");
    return false;
  }

  const char* unit = (const char*) grandeur["unite"];
  snprintf(data->unit, sizeof(data->unit), "%s", unit != nullptr ? unit : "");
  int size = grandeur["points"].length();

  Serial.printf("linky data length: %i\n", size);
  
  if (bandwidthRef != nullptr) {
    // Use bandwidth dates as reference
    Serial.println("Using bandwidth reference for date alignment");
    
    for (int i = 0; i < CHART_DAYS; i++) {
      snprintf(data->days[i], sizeof(data->days[i]), "%s", bandwidthRef->days[i]);
      
      // Find matching date in Linky data
      data->values[i] = 0; // Default to 0 if not found
      
      for (int j = 0; j < size; j++) {
        const char* linkyDate = (const char*) grandeur["points"][j]["d"];
        
        // Extract date part from Linky timestamp for comparison
        char linkyDatePart[11]; // YYYY-MM-DD + null terminator
        extractDatePart(linkyDatePart, linkyDate, sizeof(linkyDatePart));
        
        if (strcmp(linkyDatePart, bandwidthRef->days[i]) == 0) {
          data->values[i] = atoi((const char*) grandeur["points"][j]["v"]);
          break;
        }
      }
      
      Serial.printf("linky[%i] - %s -> %i\n", i, data->days[i], data->values[i]);
    }
  } else {
    // Original behavior - take last CHART_DAYS entries
    if (size < CHART_DAYS) return false;

    for (int i = 0, id = size - CHART_DAYS; i < CHART_DAYS; i++, id++) {
      const char* date = (const char*) grandeur["points"][id]["d"];
      snprintf(data->days[i], sizeof(data->days[i]), "%s", date != nullptr ? date : "");
      data->values[i] = atoi((const char*) grandeur["points"][id]["v"]);
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

  const char* priceStr = (const char*) json["price"];
  if (priceStr == nullptr) {
    Serial.println("fillLinkyMetaDataFromJson: invalid price value");
    return false;
  }

  double price;
  if (sscanf(priceStr, "%lf", &price) != 1) {
    Serial.println("fillLinkyMetaDataFromJson: failed to parse price");
    return false;
  }
  data->price = price;
  Serial.println("Price");
  Serial.println(data->price);

  return true;
}
