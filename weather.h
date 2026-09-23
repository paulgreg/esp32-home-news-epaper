struct Weather {
  char iconH1[10];
  char tempH1[20];
  char feelsLikeH1[20];
  char humidityH1[6];

  char iconD[10];
  char tempMinD[20];
  char tempMaxD[20];
  char humidityD[6];

  char iconD1[10];
  char tempMinD1[20];
  char tempMaxD1[20];
  char humidityD1[6];

  char updated[20];
  uint currentHour = 0;
};

void fillWeatherFromJson(JSONVar json, Weather* weather) {
  // hourly is disabled in parameters
  // sprintf(weather->iconH1, "%s", (const char*) json["hourly"][1]["weather"][0]["icon"]);
  // sprintf(weather->tempH1, "min: %2i\xb0", (int) round((double) json["hourly"][1]["temp"]));
  // sprintf(weather->feelsLikeH1, "max: %2i\xb0", (int) round((double) json["hourly"][1]["feels_like"]));
  // sprintf(weather->humidityH1, "%3i %%", (int) json["hourly"][1]["humidity"]);

  const char* iconH1 = (const char*) json["current"]["weather"][0]["icon"];
  const char* iconD = (const char*) json["daily"][0]["weather"][0]["icon"];
  const char* iconD1 = (const char*) json["daily"][1]["weather"][0]["icon"];

  snprintf(weather->iconH1, sizeof(weather->iconH1), "%s", iconH1 != nullptr ? iconH1 : "");
  snprintf(weather->tempH1, sizeof(weather->tempH1), "temp: %2i\xb0", (int) round((double) json["current"]["temp"]));
  snprintf(weather->feelsLikeH1, sizeof(weather->feelsLikeH1), "like: %2i\xb0", (int) round((double) json["current"]["feels_like"]));
  snprintf(weather->humidityH1, sizeof(weather->humidityH1), "%3i %%", (int) json["current"]["humidity"]);

  snprintf(weather->iconD, sizeof(weather->iconD), "%s", iconD != nullptr ? iconD : "");
  snprintf(weather->tempMinD, sizeof(weather->tempMinD), "min: %2i\xb0", (int) round((double) json["daily"][0]["temp"]["min"]));
  snprintf(weather->tempMaxD, sizeof(weather->tempMaxD), "max: %2i\xb0", (int) round((double) json["daily"][0]["temp"]["max"]));
  snprintf(weather->humidityD, sizeof(weather->humidityD), "%3i %%", (int) json["daily"][0]["humidity"]);
  snprintf(weather->iconD1, sizeof(weather->iconD1), "%s", iconD1 != nullptr ? iconD1 : "");
  snprintf(weather->tempMinD1, sizeof(weather->tempMinD1), "min: %2i\xb0", (int) round((double) json["daily"][1]["temp"]["min"]));
  snprintf(weather->tempMaxD1, sizeof(weather->tempMaxD1), "max: %2i\xb0", (int) round((double) json["daily"][1]["temp"]["max"]));
  snprintf(weather->humidityD1, sizeof(weather->humidityD1), "%3i %%", (int) json["daily"][1]["humidity"]);

  int timezone_offset = (int) json["timezone_offset"];
  int dt = (int) json["current"]["dt"];
  int t = dt + timezone_offset;
  uint currentHour = hour(t);
  snprintf(weather->updated, sizeof(weather->updated), "MAJ : %02d/%02d %02d:%02d", day(t), month(t), currentHour, minute(t));
  weather->currentHour = currentHour;
}
