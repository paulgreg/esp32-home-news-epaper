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

boolean disconnectFromWifi() {
  WiFi.disconnect();
}

boolean getWeatherJSON() {
  boolean success = false;
  
  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.print("Connecting to "); Serial.println(WEATHER_URL);
    
    HTTPClient http;
    http.begin(WEATHER_URL);
    int httpCode = http.GET();
    Serial.print("HTTP code : "); Serial.println(httpCode);
    if (httpCode > 0) {
      weatherJson = JSON.parse(http.getString());
      
      if (JSON.typeof(weatherJson) == "undefined") {
        Serial.println("Parsing weatherJson input failed!");
      } else {
        success = true;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  return success;
}


boolean getCalendarJSON() {
  boolean success = false;

  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.print("Connecting to "); Serial.println(CALENDAR_URL_EVENTS);
    
    HTTPClient http;
    http.begin(CALENDAR_URL_EVENTS);
    http.setAuthorization(CALENDAR_LOGIN, CALENDAR_PASSWORD);
    int httpCode = http.GET();
    Serial.print("HTTP code : "); Serial.println(httpCode);
    if (httpCode > 0) {
      eventsJson = JSON.parse(http.getString());

      if (JSON.typeof(eventsJson) == "undefined") {
        Serial.println("Parsing eventsJson input failed!");
      } else {
        success = true;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  return success;
}
