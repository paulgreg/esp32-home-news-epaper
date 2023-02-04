#include "icons/01d-sun.h"
#include "icons/02d-sun.h"
#include "icons/02d-cloud.h"
#include "icons/03d-cloud.h"
#include "icons/04d-cloud.h"
#include "icons/04d-cloud-back.h"
#include "icons/09d-cloud.h"
#include "icons/09d-rain.h"
#include "icons/10d-cloud.h"
#include "icons/10d-sun.h"
#include "icons/11d-cloud.h"
#include "icons/11d-lightning.h"
#include "icons/13d-snow.h"
#include "icons/50d-fog.h"

#include "Fonts/Cantarell_Regular_euro8pt8b.h"
#include "Fonts/Cantarell_Bold_euro9pt8b.h"
#include "Fonts/FreeMonoBold_euro14pt8b.h"
#include "Fonts/Cantarell_Bold_euro16pt8b.h"

#define FONT_TINY Cantarell_Regular_euro8pt8b
#define FONT_SMALL Cantarell_Bold_euro9pt8b
#define FONT_NORMAL FreeMonoBold_euro14pt8b
#define FONT_BIG Cantarell_Bold_euro16pt8b

#define WEATHER_X  0
#define WEATHER_Y 10

void drawTextRightAlign(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - tbw, y);
  display.println(text);
}

void drawTextCenterAlign(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - (tbw / 2), y);
  display.println(text);
}

void drawIcon(int x, int y, char* icon) {
  if (strcmp(icon, "01d") == 0) {
    // 01d - Sun
    display.drawBitmap(x, y, icon_01d_sun_bits, icon_01d_sun_width, icon_01d_sun_height, GxEPD_RED);
  } else if (strcmp(icon, "01n") == 0) {
    // 01d - Sun - night
    display.drawBitmap(x, y, icon_01d_sun_bits, icon_01d_sun_width, icon_01d_sun_height, GxEPD_BLACK);
  } else if (strcmp(icon, "02d") == 0) {
    // 02d - Cloud, sun
    display.drawBitmap(x, y, icon_02d_sun_bits, icon_02d_sun_width, icon_02d_sun_height, GxEPD_RED);
    display.drawBitmap(x, y, icon_02d_cloud_bits, icon_02d_cloud_width, icon_02d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "02n") == 0) {
    // 02d - Cloud, sun - night
    display.drawBitmap(x, y, icon_02d_sun_bits, icon_02d_sun_width, icon_02d_sun_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_02d_cloud_bits, icon_02d_cloud_width, icon_02d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "03d") == 0 || strcmp(icon, "03n") == 0) {
    // 03d - Cloud
    display.drawBitmap(x, y, icon_03d_cloud_bits, icon_03d_cloud_width, icon_03d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "04d") == 0) {
    // 04d - Cloud, second cloud
    display.drawBitmap(x, y, icon_04d_cloud_bits, icon_04d_cloud_width, icon_04d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_04d_cloud_back_bits, icon_04d_cloud_back_width, icon_04d_cloud_back_height, GxEPD_RED);
  } else if (strcmp(icon, "04n") == 0) {
    // 04d - Cloud, second cloud - night
    display.drawBitmap(x, y, icon_04d_cloud_bits, icon_04d_cloud_width, icon_04d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_04d_cloud_back_bits, icon_04d_cloud_back_width, icon_04d_cloud_back_height, GxEPD_BLACK);
  } else if (strcmp(icon, "09d") == 0) {
    // 09d - Clouds, rain
    display.drawBitmap(x, y, icon_09d_cloud_bits, icon_09d_cloud_width, icon_09d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_09d_rain_bits, icon_09d_rain_width, icon_09d_rain_height, GxEPD_BLACK);
  } else if (strcmp(icon, "09n") == 0) {
    // 09d - Clouds, rain - night
    display.drawBitmap(x, y, icon_09d_cloud_bits, icon_09d_cloud_width, icon_09d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_09d_rain_bits, icon_09d_rain_width, icon_09d_rain_height, GxEPD_BLACK);
  } else if (strcmp(icon, "10d") == 0) {
    // 10d - Clouds, sun, rain
    display.drawBitmap(x, y, icon_10d_cloud_bits, icon_10d_cloud_width, icon_10d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_10d_sun_bits, icon_10d_sun_width, icon_10d_sun_height, GxEPD_BLACK);
  } else if (strcmp(icon, "10n") == 0) {
    // 10d - Clouds, sun, rain - night
    display.drawBitmap(x, y, icon_10d_cloud_bits, icon_10d_cloud_width, icon_10d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_10d_sun_bits, icon_10d_sun_width, icon_10d_sun_height, GxEPD_BLACK);
  } else if (strcmp(icon, "11d") == 0) {
    // 11d - Clouds, lightning
    display.drawBitmap(x, y, icon_11d_cloud_bits, icon_11d_cloud_width, icon_11d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_11d_ligthning_bits, icon_11d_ligthning_width, icon_11d_ligthning_height, GxEPD_RED);
  } else if (strcmp(icon, "11n") == 0) {
    // 11d - Clouds, lightning - night
    display.drawBitmap(x, y, icon_11d_cloud_bits, icon_11d_cloud_width, icon_11d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_11d_ligthning_bits, icon_11d_ligthning_width, icon_11d_ligthning_height, GxEPD_BLACK);
  } else if (strcmp(icon, "13d") == 0 || strcmp(icon, "13n") == 0) {
    // 13d - Snow
    display.drawBitmap(x, y, icon_13d_snow_bits, icon_13d_snow_width, icon_13d_snow_height, GxEPD_BLACK);
  } else if (strcmp(icon, "50d") == 0 ||strcmp(icon, "50n") == 0) {
    // 50d - Fog
    display.drawBitmap(x, y, icon_50d_fog_bits, icon_50d_fog_width, icon_50d_fog_height, GxEPD_BLACK);
  }
}

void displayDayMinMax(int x, int y, char* title, char* icon, char* temp1, char* temp2, char* humidity) {
  int center = 60;
  drawTextCenterAlign(center + x,  28 + y, title, GxEPD_BLACK, &FONT_BIG);
  drawIcon(               20 + x,  30 + y, icon);
  drawTextRightAlign(    130 + x, 130 + y, temp1, GxEPD_BLACK, &FONT_BIG);
  drawTextRightAlign(    130 + x, 160 + y, temp2, GxEPD_BLACK, &FONT_BIG);
  drawTextRightAlign(    120 + x, 190 + y, humidity, GxEPD_BLACK, &FONT_NORMAL);
}

void displayWeather(Weather* weather) {
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do
  {
    displayDayMinMax(WEATHER_X + 20, WEATHER_Y, "now", weather->iconH1, weather->feelsLikeH1, weather->tempH1, weather->humidityH1);
    displayDayMinMax(WEATHER_X + 180, WEATHER_Y, "today", weather->iconD, weather->tempMinD, weather->tempMaxD, weather->humidityD);
    displayDayMinMax(WEATHER_X + 330, WEATHER_Y, "tomorrow", weather->iconD1, weather->tempMinD1, weather->tempMaxD1, weather->humidityD1);
    drawTextRightAlign(display.width() - 10, display.height() - 10, weather->updated, GxEPD_BLACK, &FONT_SMALL);
  } while (display.nextPage());
}

void displayLocalTemp(LocalTemp* localTemp) {
  int x = 5;
  int y = 100;
  int w = 90;
  int h = 38;
  
  display.setPartialWindow(x, y, w, h);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    drawTextCenterAlign(x + 40, y + 24, localTemp->temp, GxEPD_BLACK, &FONT_NORMAL);
  } while (display.nextPage());
}

void displayError(char* text) {
  int x = 0;
  int y = display.height() - 20;
  int w = display.width() / 2;
  int h = 20;
  display.setFont(&FONT_SMALL);
  display.setTextColor(GxEPD_RED);
  
  display.setPartialWindow(x, y, w, h);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x + 5, y + 12);
    display.print(text);
  } while (display.nextPage());
}
