boolean connectToWifi() {
  Serial.print("\nconnecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned int retries = 50;
  while (WiFi.status() != WL_CONNECTED && (retries-- > 0)) {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWifi connection failed");
    return false;
  }
  Serial.println("");
  Serial.println("wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.println("");
  return true;
}

String httpGet(const char* url, const char* login, const char* password) {
  String s = "";
  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.print("Connecting to "); Serial.println(url);
    HTTPClient http;
    http.begin(url);
    if (strlen(login) > 0 && strlen(password) > 0) http.setAuthorization(login, password);
    int httpCode = http.GET();
     Serial.print("HTTP code : "); Serial.println(httpCode);
    if (httpCode > 0) {
      s = http.getString();
      Serial.print("Reponse length : "); Serial.println(s.length());
      if (DEBUG) Serial.println(s);
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }  
  return s;
}

boolean getWeatherJSON(Weather* weather) {
  boolean success = false;
  String calendarStr = httpGet(WEATHER_URL, "", "");
  JSONVar json = JSON.parse(calendarStr);
  if (JSON.typeof(json) == "undefined") {
    Serial.println("Parsing weatherJson input failed!");
  } else {
    fillWeatherFromJson(json, weather);
    success = true;
  }
  return success;
}

boolean getCalendarJSON(Events* events) {
  boolean success = false;
  String calendarStr = httpGet(CALENDAR_URL_EVENTS, CALENDAR_LOGIN, CALENDAR_PASSWORD);
  JSONVar json = JSON.parse(calendarStr);
  if (JSON.typeof(json) == "undefined") {
    Serial.println("Parsing eventsJson input failed!");
  } else {
    fillEventsFromJson(json, events);
    success = true;
  }
  return success;
}

boolean getLinkyJSON(LinkyData* daily, LinkyData* power) {
  boolean dailySuccess = false;
  boolean powerSuccess = false;

  String dailyStr = httpGet(LINKY_DAILY_CONSUMPTION_URL, LINK_LOGIN, LINKY_PASSWORD);
  JSONVar json1 = JSON.parse(dailyStr);
  if (JSON.typeof(json1) == "undefined") {
    Serial.println("Parsing dailyJson input failed!");
  } else {    
    dailySuccess = fillLinkyDataFromJson(json1, daily);
  }

  String powerStr = httpGet(LINKY_MAX_POWER_URL, LINK_LOGIN, LINKY_PASSWORD);
  JSONVar json2 = JSON.parse(powerStr);
  if (JSON.typeof(json2) == "undefined") {
    Serial.println("Parsing powerJson input failed!");
  } else {
    powerSuccess = fillLinkyDataFromJson(json2, power);
  }

  return dailySuccess && powerSuccess;
}
