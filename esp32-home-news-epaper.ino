
#include <GxEPD2_3C.h>

#define USE_HSPI_FOR_EPD

#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
#define GxEPD2_DRIVER_CLASS GxEPD2_583c_Z83 // GDEW0583Z83 648x480, EK79655 (GD7965)

#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
SPIClass hspi(HSPI);

#include <TimeLib.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

JSONVar weatherJson;
JSONVar eventsJson;

#include "parameters.h"
#include "events.h"
#include "temp.h"
#include "weather.h"
#include "display.h"
#include "network.h"

Events events;

uint currentHour = 0;

const uint64_t SECOND = 1000;
const uint64_t MINUTE = 60 * SECOND;
const uint64_t HOUR = 60 * MINUTE;
const uint64_t MICRO_SEC_TO_MILLI_SEC_FACTOR = 1000;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  while(!Serial) {}
  Serial.println("\nNews station");

  #ifdef RF_RX_PIN
  OregonTHN128_RxBegin(RF_RX_PIN);
  #endif

  // *** special handling for Waveshare ESP32 Driver board *** //
  hspi.begin(13, 12, 14, 15); // remap hspi for EPD (swap pins)
  display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
  // *** end of special handling for Waveshare ESP32 Driver board *** //
  display.init(115200);
  display.setRotation(1);
}

boolean fetchWeatherData() {
  uint64_t retries = MAX_RETRIES;
  boolean jsonParsed = false;
  while(!jsonParsed && (retries-- > 0)) {
    delay(1000);
    jsonParsed = getWeatherJSON();
  }
  if (!jsonParsed) {
    displayError("Error:JSON-W");
  }
  return jsonParsed;
}

boolean fetchCalendarData() {
  unsigned int retries = MAX_RETRIES;
  boolean jsonParsed = false;
  while(!jsonParsed && (retries-- > 0)) {
    delay(1000);
    jsonParsed = getCalendarJSON();
  }
  if (!jsonParsed) {
    displayError("Error:JSON-C");
  }
  return jsonParsed;
}

void displayWeather() {
  Weather weather;
  fillWeatherFromJson(&weather);
  displayWeather(&weather);
  
  char hour[3] = { weather.updated[0], weather.updated[1], '\0'};
  currentHour = atoi(hour);
  Serial.print("currentHour: "); Serial.println(currentHour);
}

void fetchAndDisplayLocalTemp() {
  #ifdef RF_RX_PIN
  // get local temperature from oregon sensor
  retries = 500000000;
  boolean localTemp = false;
  OregonTHN128Data_t oregonData;

  Serial.println("Try to fetch local temp");
  while(!localTemp && (retries-- > 0)) {
    if (OregonTHN128_Available()) {    
      Serial.println("found");
      Serial.println(retries);
      OregonTHN128_Read(&oregonData);
      printReceivedData(&oregonData);
      localTemp = true;
    }
  }
  Serial.println("End fetch local temp loop");

  if (localTemp) {
    LocalTemp localTemp;
    fillLocalTempFromJson(&oregonData, &localTemp);
    displayLocalTemp(&localTemp);
  }
  #endif
}

void displayCalendar() {
  fillDataFromJson(eventsJson, &events);
  displayEvents(&events);
}

void loop() {
  if (!connectToWifi()) {
    displayError("Error: WIFI");
  } else {
    boolean calendarData = fetchCalendarData();
    boolean weatherData  = fetchWeatherData();

    if (weatherData) {
      displayWeather();
    } else {
      displayError("Error: JSON-W");
    }
    if (calendarData) {
      displayCalendar();
    } else {
      displayError("Error: JSON-C");
    }

    fetchAndDisplayLocalTemp();

    // disconnectFromWifi();
  }

  uint64_t sleepTime = currentHour == 0 ? HOUR * 6 : HOUR;

  sleep(sleepTime);
  Serial.println("SLEEP FAILED");
  delay(HOUR);
}

void sleep(uint64_t sleepTime) {
  display.powerOff();
  display.hibernate();
  Serial.print("Will sleep "); 
  Serial.println(sleepTime);
  delay(SECOND);
  Serial.flush();
  display.powerOff();
  esp_sleep_enable_timer_wakeup((uint64_t) sleepTime * MICRO_SEC_TO_MILLI_SEC_FACTOR);
  esp_deep_sleep_start();
  delay(MINUTE);
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : {
      Serial.print("Wakeup caused by touchpad pin "); 
      Serial.println(esp_sleep_get_touchpad_wakeup_status());
      break;
    }
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }
}