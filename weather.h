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
};

void fillWeatherFromJson(Weather* weather) {
  sprintf(weather->iconH1, "%s", (const char*) weatherJson["hourly"][1]["weather"][0]["icon"]);
  sprintf(weather->tempH1, "min: %2i\xb0", (int) round((double) weatherJson["hourly"][1]["temp"]));
  sprintf(weather->feelsLikeH1, "max: %2i\xb0", (int) round((double) weatherJson["hourly"][1]["feels_like"]));
  sprintf(weather->humidityH1, "%3i %%", (int) weatherJson["hourly"][1]["humidity"]);

  sprintf(weather->iconD, "%s", (const char*) weatherJson["daily"][0]["weather"][0]["icon"]);
  sprintf(weather->tempMinD, "min: %2i\xb0", (int) round((double) weatherJson["daily"][0]["temp"]["min"]));
  sprintf(weather->tempMaxD, "max: %2i\xb0", (int) round((double) weatherJson["daily"][0]["temp"]["max"]));
  sprintf(weather->humidityD, "%3i %%", (int) weatherJson["daily"][0]["humidity"]);

  sprintf(weather->iconD1, "%s", (const char*) weatherJson["daily"][1]["weather"][0]["icon"]);
  sprintf(weather->tempMinD1, "min: %2i\xb0", (int) round((double) weatherJson["daily"][1]["temp"]["min"]));
  sprintf(weather->tempMaxD1, "max: %2i\xb0", (int) round((double) weatherJson["daily"][1]["temp"]["max"]));
  sprintf(weather->humidityD1, "%3i %%", (int) weatherJson["daily"][1]["humidity"]);

  int timezone_offset = (int) weatherJson["timezone_offset"];
  int dt = (int) weatherJson["current"]["dt"];
  int t = dt + timezone_offset;
  sprintf(weather->updated, "MAJ : %02d/%02d %02d:%02d", day(t), month(t), hour(t), minute(t));
}
