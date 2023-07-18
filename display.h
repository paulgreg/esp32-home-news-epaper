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

#include "Fonts/Cantarell_Bold_euro9pt8b.h"
#include "Fonts/Cantarell_Bold_euro12pt8b.h"
#include "Fonts/Cantarell_Bold_euro16pt8b.h"

#define FONT_SMALL Cantarell_Bold_euro9pt8b
#define FONT_NORMAL Cantarell_Bold_euro12pt8b
#define FONT_BIG Cantarell_Bold_euro16pt8b

#define EURO "\x80"

void drawText(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

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

void displayError(char* text) {
  int h = 20;
  int x = 0;
  int y = display.height() - h;
  int w = display.width() / 2;

  display.setFont(&FONT_SMALL);
  display.setTextColor(GxEPD_RED);
  
  display.setPartialWindow(x, y, w, h);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x + 10, y + 10);
    display.print(text);
  } while (display.nextPage());
}

void drawLine(uint y) {
  display.fillRect(0, y - 1, display.width(), 1, GxEPD_BLACK);
}

/*
 * Weather
 */
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
  drawTextCenterAlign(center + x, 190 + y, humidity, GxEPD_BLACK, &FONT_NORMAL);
}

#define WEATHER_X  0
#define WEATHER_Y 0
#define WEATHER_HEIGHT 202

void displayWeather(Weather* weather) {
  if (weather->currentHour != 13) { // Partial refresh most of the time
    display.setPartialWindow(WEATHER_X, 0, display.width(), WEATHER_HEIGHT);
  }
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do {
    displayDayMinMax(WEATHER_X + 20, WEATHER_Y, "now", weather->iconH1, weather->feelsLikeH1, weather->tempH1, weather->humidityH1);
    displayDayMinMax(WEATHER_X + 180, WEATHER_Y, "today", weather->iconD, weather->tempMinD, weather->tempMaxD, weather->humidityD);
    displayDayMinMax(WEATHER_X + 330, WEATHER_Y, "tomorrow", weather->iconD1, weather->tempMinD1, weather->tempMaxD1, weather->humidityD1);
    drawLine(WEATHER_Y + WEATHER_HEIGHT - 2);
  } while (display.nextPage());
}

void displayUpdatedTime(Weather* weather) {
  display.setPartialWindow(0, display.height() - 20, display.width(), display.height());
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do {
    drawTextRightAlign(display.width() - 10, display.height() - 10, weather->updated, GxEPD_BLACK, &FONT_SMALL);
  } while (display.nextPage());  
}

void displayLocalTemp(LocalTemp* localTemp) {
  int x = WEATHER_X;
  int y = WEATHER_Y + 110;
  int w = 155;
  int h = 56;
  
  display.setPartialWindow(x, y, w, h);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    drawTextCenterAlign(x + 84, y + 38, localTemp->temp, GxEPD_BLACK, &FONT_BIG);
  } while (display.nextPage());
}


/*
 * Calendar
 */
void drawDateAndCalendar(int x, int y, char* fulldate, char* cal, boolean isToday) {
  char calendarAndDate[25];
  char shortdate[14];
  extractDate(fulldate, shortdate);
  sprintf(calendarAndDate, "%s - %s", shortdate, cal);
  drawTextCenterAlign(x, y, calendarAndDate, isToday ? GxEPD_BLACK : GxEPD_RED, &FONT_NORMAL);
}

void drawSummary(int x, int y, char* text, boolean isToday) {
  char summary[64];
  strncpy(summary, text, 63);
  drawTextCenterAlign(x, y, summary, isToday ? GxEPD_BLACK : GxEPD_RED, &FONT_BIG);
}

#define CALENDAR_X  10
#define CALENDAR_Y WEATHER_Y + WEATHER_HEIGHT + 2
#define CALENDAR_HEIGHT 238

void displayEvents(Events* events) {
  display.setPartialWindow(0, CALENDAR_Y, display.width(), CALENDAR_HEIGHT);
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  uint middleX = display.width() / 2;
  do {
    int x = CALENDAR_X;
    int y = CALENDAR_Y + 22;
    for (int i = 0; i < events->size; i++) {
      drawDateAndCalendar(middleX, y, events->date[i], events->calendar[i], events->isToday[i]);
      y += 28;
      drawSummary(middleX, y, events->summary[i], events->isToday[i]);
      y += 30;
    }
    drawLine(CALENDAR_Y + CALENDAR_HEIGHT - 2);
  } while (display.nextPage());
}


/*
 * Linky
 */
#define LINKY_X  10
#define LINKY_Y CALENDAR_Y + CALENDAR_HEIGHT + 4
#define LINKY_HEIGHT 172

#define LINKY_STEP 46
#define LINKY_OFFSET_X 65
#define LINKY_MAX_Y 140

void displayPrices(int offsetY, LinkyData* daily, double kmWPerHourPrice) {
  int y = offsetY + 16;
  drawText(18, offsetY + 18, EURO, GxEPD_BLACK, &FONT_NORMAL);
  char price[10];
  for (int i = 0; i < LINKY_DAYS; i++) {
    double p = daily->values[i] * kmWPerHourPrice / 1000;
    sprintf(price, "%.1lf", p);
    Serial.printf("price: %s\n", price);
    int x = LINKY_OFFSET_X + i * LINKY_STEP;
    drawText(x, y, price, p >= LINKY_PRICE_THRESHOLD ? GxEPD_BLACK : GxEPD_RED, &FONT_SMALL);
  }
}

void displayDays(uint offsetY, LinkyData* daily) {
  char date[3];
  for (int i = 0; i < LINKY_DAYS; i++) {
    if (strlen(daily->days[i]) >= 9) { // str is like yyyy-mm-dd
      drawText(LINKY_OFFSET_X + i * LINKY_STEP, offsetY + 160, &daily->days[i][8], GxEPD_BLACK, &FONT_SMALL);
    }
  }
}

int mapToY (int y) {
 int yy = y * 7;
 int maxY = LINKY_MAX_Y;
 int r = yy < maxY ? maxY - yy : maxY;
 // Serial.printf("mapToY: %i ⁻> %i\n", y, r);
 return r;
}

void displayScale(uint offsetY) {
  char s[4];
  Serial.println("Scale");
  for (int i = 0; i <= 15; i+=3) {
    int y = offsetY + mapToY(i);
    sprintf(s, "%2dk", i);
    drawText(16, 5 + y, s, GxEPD_BLACK, &FONT_SMALL);
    display.fillRect(50, y, 420, 2, GxEPD_RED);
  }
}

void displayConsumption(uint offsetY, LinkyData* daily) {
  for (int i = 0; i < LINKY_DAYS; i++) {
    int value = daily->values[i] / 1000;
    int x = LINKY_OFFSET_X + 10 + i * LINKY_STEP;
    int y = offsetY + mapToY(value);
    display.fillRect(x, y, 12, (offsetY + LINKY_MAX_Y) - y, GxEPD_BLACK);
  }
}

void displayMaxPower(uint offsetY, LinkyData* power) {
  for (int i = 0; i < LINKY_DAYS; i++) {
    int value = power->values[i] / 1000;
    int x = LINKY_OFFSET_X + i * LINKY_STEP;
    int y = offsetY + mapToY(value);
    display.fillRect(x, y, 6, (offsetY + LINKY_MAX_Y) - y, GxEPD_RED);
  }
}

void displayLinkyData(LinkyData* daily, LinkyData* power, LinkyMetaData* metadata) {
  display.setPartialWindow(0, LINKY_Y, display.width(), LINKY_HEIGHT);
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do {
    displayScale(LINKY_Y);
    displayDays(LINKY_Y, daily);
    displayPrices(LINKY_Y, daily, metadata->price);
    displayConsumption(LINKY_Y, daily);
    displayMaxPower(LINKY_Y, power);
    drawLine(LINKY_Y + LINKY_HEIGHT - 2);
  } while (display.nextPage());
}
