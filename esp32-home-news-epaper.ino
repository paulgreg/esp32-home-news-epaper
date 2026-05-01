#include <GxEPD2_3C.h>

#define USE_HSPI_FOR_EPD

#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z08 

#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

GxEPD2_3C<GxEPD2_750c_GDEY075Z08, GxEPD2_750c_GDEY075Z08::HEIGHT / 2> display(GxEPD2_750c_GDEY075Z08(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25)); // GDEY075Z08 800x480, UC8179, (FPC-C001 21.08.30)

SPIClass hspi(HSPI);

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#include "parameters.h"
#include <TimeLib.h>
#include "stringUtil.h"
#include "events.h"
#include "temp.h"
#include "weather.h"
#include "words.h"
#include "bandwidth.h"
#include "linky.h"
#include "display.h"
#include "network.h"

const uint64_t SECOND = 1000;
const uint64_t MINUTE = 60 * SECOND;
const uint64_t HOUR = 60 * MINUTE;
const uint64_t MICRO_SEC_TO_MILLI_SEC_FACTOR = 1000;

enum state { RENDER_1 = 1, RENDER_2 = 2, RENDER_END = 3 };

Weather weather;
Events events;
LinkyData daily;
LinkyData power;
LinkyMetaData metadata;
BandwidthData bandwidthData;
Words words;
LocalTemp localTemp;


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

  // display.init(115200);
  display.init(115200, true, 2, false); 
  display.setRotation(1);
}

boolean fetchWeatherData() {
  uint retries = MAX_RETRIES;
  boolean success = false;
  while(!success && (retries-- > 0)) {
    delay(RETRIES_DELAY);
    success = getWeatherJSON(&weather);
  }
  return success;
}

boolean fetchCalendarData() {
  uint retries = MAX_RETRIES;
  boolean success = false;
  while(!success && (retries-- > 0)) {
    delay(RETRIES_DELAY);
    success = getCalendarJSON(&events);
  }
  return success;
}

boolean fetchBandwidthData() {
  uint retries = MAX_RETRIES;
  boolean success = false;
  while(!success && (retries-- > 0)) {
    delay(RETRIES_DELAY);
    success = getBandwidthJSON(&bandwidthData);
  }
  return success;
}

boolean fetchLinkyData() {
  uint retries = MAX_RETRIES;
  boolean success = false;
  while(!success && (retries-- > 0)) {
    delay(RETRIES_DELAY);
    success = getLinkyJSON(&daily, &power, &metadata, &bandwidthData);
  }
  return success;
}

boolean fetchWordsData() {
  uint retries = MAX_RETRIES;
  boolean success = false;
  while(!success && (retries-- > 0)) {
    delay(RETRIES_DELAY);
    success = getWordsJSON(&words);
  }
  return success;
}

boolean fetchLocalTemp() {
  boolean foundLocalTemp = false;

  #ifdef RF_RX_PIN
  // get local temperature from oregon sensor
  const uint32_t maxRetries = 180 * 100; // 180 seconds with 10ms delay
  const uint32_t retryDelayMs = 10;
  OregonTHN128Data_t oregonData;

  Serial.println("Try to fetch local temp");
  for (uint32_t retries = maxRetries; retries > 0 && !foundLocalTemp; retries--) {
    if (OregonTHN128_Available()) {
      if (retries % 100 == 0) {
        Serial.print("remaining tries: "); Serial.println(retries);
      }
      OregonTHN128_Read(&oregonData);
      printReceivedData(&oregonData);
      foundLocalTemp = true;
    }
    delay(retryDelayMs);
  }
  Serial.println("End fetch local temp loop");

  if (foundLocalTemp) {
    fillLocalTempFromJson(&oregonData, &localTemp);
  }
  #endif

  return foundLocalTemp;
}


void loop() {
  enum state st = RENDER_1;
  display.setFullWindow();
  display.firstPage();

  if (!connectToWifi()) {
    do {
      display.fillScreen(GxEPD_WHITE);
      displayError(20, "Error: WIFI");
    } while (display.nextPage());

  } else {
    boolean weatherSuccess = fetchWeatherData();
    boolean eventsSuccess = fetchCalendarData();
    boolean bandwidthSuccess = fetchBandwidthData();
    boolean linkySuccess = fetchLinkyData();
    boolean wordsSuccess = fetchWordsData();

    do {
      Serial.printf("State: %i\n", st);

      do {
        display.fillScreen(GxEPD_WHITE);

        if (weatherSuccess) {
          displayWeather(&weather, &localTemp);
          displayUpdatedTime(&weather);
        } else {
          displayWeatherError("Error: weather");
        }

        if (eventsSuccess) {
          displayEvents(&events);
        } else {
          displayCalendarError("Error: calendar");
        }

        if (linkySuccess) {
          displayLinkyData(&daily, &power, &metadata);
        } else {
          displayGraphError("Error: linky");
        }

        if (bandwidthSuccess) {
          displayBandwidthData(&bandwidthData);
        } else {
          displayGraphError("Error: bandwidth");
        }

        if (wordsSuccess) {
          displayWords(&words);
        } else {
          displayWordsError("Error: word of the day");
        }

      } while (display.nextPage());

      if (st == RENDER_2) {
        st = RENDER_END;
      } else {
        if (fetchLocalTemp()) {
          st = RENDER_2;
        } else {
          st = RENDER_END;
        }
      }
    } while (st != RENDER_END);


  }
  uint64_t sleepTime = weather.currentHour == 23 ? HOUR * 7 : HOUR;
  
  sleep(sleepTime);
  Serial.println("SLEEP FAILED");
  delay(HOUR);
}

void sleep(uint64_t sleepTime) {
  display.hibernate();

  Serial.print("Will sleep "); 
  Serial.println(sleepTime);
  delay(SECOND);
  Serial.flush();

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