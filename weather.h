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

  sprintf(weather->iconH1, "%s", (const char*) json["current"]["weather"][0]["icon"]);
  sprintf(weather->tempH1, "temp: %2i\xb0", (int) round((double) json["current"]["temp"]));
  sprintf(weather->feelsLikeH1, "like: %2i\xb0", (int) round((double) json["current"]["feels_like"]));
  sprintf(weather->humidityH1, "%3i %%", (int) json["current"]["humidity"]);

  sprintf(weather->iconD, "%s", (const char*) json["daily"][0]["weather"][0]["icon"]);
  sprintf(weather->tempMinD, "min: %2i\xb0", (int) round((double) json["daily"][0]["temp"]["min"]));
  sprintf(weather->tempMaxD, "max: %2i\xb0", (int) round((double) json["daily"][0]["temp"]["max"]));
  sprintf(weather->humidityD, "%3i %%", (int) json["daily"][0]["humidity"]);
  sprintf(weather->iconD1, "%s", (const char*) json["daily"][1]["weather"][0]["icon"]);
  sprintf(weather->tempMinD1, "min: %2i\xb0", (int) round((double) json["daily"][1]["temp"]["min"]));
  sprintf(weather->tempMaxD1, "max: %2i\xb0", (int) round((double) json["daily"][1]["temp"]["max"]));
  sprintf(weather->humidityD1, "%3i %%", (int) json["daily"][1]["humidity"]);

  int timezone_offset = (int) json["timezone_offset"];
  int dt = (int) json["current"]["dt"];
  int t = dt + timezone_offset;
  uint currentHour = hour(t);
  sprintf(weather->updated, "MAJ : %02d/%02d %02d:%02d", day(t), month(t), currentHour, minute(t));
  weather->currentHour = currentHour;
}
