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

#define V_MARGIN 4

void drawText(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

void drawTextRightAlign(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - tbw, y);
  display.println(text);
}

void drawTextCenterAlign(int x, int y, char* text, int color, const GFXfont* font) {
  display.setFont(font);
  display.setTextColor(color);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - (tbw / 2), y);
  display.println(text);
}

void displayError(int y, char* text) {
  int x = 0;

  display.setFont(&FONT_SMALL);
  display.setTextColor(GxEPD_RED);

  display.setCursor(x + 10, y + 10);
  display.print(text);
}

void drawLine(uint y, uint size, int color) {
  display.fillRect(0, y - 1, display.width(), size, color);
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
  } else if (strcmp(icon, "50d") == 0 || strcmp(icon, "50n") == 0) {
    // 50d - Fog
    display.drawBitmap(x, y, icon_50d_fog_bits, icon_50d_fog_width, icon_50d_fog_height, GxEPD_BLACK);
  }
}

void displayDayMinMax(int x, int y, char* title, char* icon, char* temp1, char* temp2) {
  int center = 60;
  drawTextCenterAlign(center + x, 28 + y, title, GxEPD_BLACK, &FONT_BIG);
  drawIcon(20 + x, 30 + y, icon);
  drawTextRightAlign(130 + x, 130 + y, temp1, GxEPD_BLACK, &FONT_BIG);
  drawTextRightAlign(130 + x, 160 + y, temp2, GxEPD_BLACK, &FONT_BIG);
}

#define WEATHER_X 0
#define WEATHER_Y 0
#define WEATHER_HEIGHT 182

void displayDayLocalTemp(int x, int y, char* title, char* icon, char* temp) {
  int center = 60;
  drawTextCenterAlign(center + x, 28 + y, title, GxEPD_BLACK, &FONT_BIG);
  drawIcon(20 + x, 30 + y, icon);
  drawTextCenterAlign(center + x, y + 140, temp, GxEPD_BLACK, &FONT_BIG);
}

void displayWeather(Weather* weather, LocalTemp* localTemp = nullptr) {
  if (localTemp != nullptr && localTemp->temp[0] != '\0') {
    displayDayLocalTemp(WEATHER_X + 20, WEATHER_Y, "now", weather->iconH1, localTemp->temp);
  } else {
    displayDayMinMax(WEATHER_X + 20, WEATHER_Y, "now", weather->iconH1, weather->feelsLikeH1, weather->tempH1);
  }
  displayDayMinMax(WEATHER_X + 180, WEATHER_Y, "today", weather->iconD, weather->tempMinD, weather->tempMaxD);
  displayDayMinMax(WEATHER_X + 330, WEATHER_Y, "tomorrow", weather->iconD1, weather->tempMinD1, weather->tempMaxD1);
  drawLine(WEATHER_Y + WEATHER_HEIGHT - V_MARGIN, 2, GxEPD_BLACK);
}

void displayWeatherError(char* text) {
  displayError(WEATHER_Y + 20, text);
}

void displayUpdatedTime(Weather* weather) {
  drawTextRightAlign(display.width() - 4, display.height() - 4, weather->updated, GxEPD_BLACK, &FONT_SMALL);
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

#define CALENDAR_X 10
#define CALENDAR_Y WEATHER_Y + WEATHER_HEIGHT + V_MARGIN
#define CALENDAR_HEIGHT 270

void displayEvents(Events* events) {
  uint middleX = display.width() / 2;
  int x = CALENDAR_X;
  int y = CALENDAR_Y + 22;
  for (int i = 0; i < events->size; i++) {
    drawDateAndCalendar(middleX, y, events->date[i], events->calendar[i], events->isToday[i]);
    y += 28;
    drawSummary(middleX, y, events->summary[i], events->isToday[i]);
    y += 30;
  }
  drawLine(CALENDAR_Y + CALENDAR_HEIGHT - V_MARGIN, 2, GxEPD_BLACK);
}

void displayCalendarError(char* text) {
  displayError(CALENDAR_Y + 20, text);
}


/*
 * Word of the day
 */
#define WORDS_Y CALENDAR_Y + CALENDAR_HEIGHT + V_MARGIN + 4
#define WORDS_HEIGHT 136

void displayWords(Words* words) {
  int xLang = 34;
  int xWord = 40;
  int yGap = 22;

  int xSecondColumn = display.width() / 2 - 10;

  for (int i = 0; i < NB_LANG; i+=2) {
    int y = WORDS_Y + (1 + i) * yGap;

    drawTextRightAlign(xLang, y, words->languages[i], GxEPD_BLACK, &FONT_NORMAL);
    drawText(xWord, y, words->translations[i], GxEPD_BLACK, &FONT_BIG);

    drawTextRightAlign(xSecondColumn + xLang, y, words->languages[i+1], GxEPD_BLACK, &FONT_NORMAL);
    drawText(xSecondColumn + xWord, y, words->translations[i+1], GxEPD_BLACK, &FONT_BIG);

    drawLine(y + 5, 1, GxEPD_RED);
  }
  drawLine(WORDS_Y + WORDS_HEIGHT - V_MARGIN, 2, GxEPD_BLACK);
}

void displayWordsError(char* text) {
  displayError(WORDS_Y + 20, text);
}

/*
 * Linky & Bandwidth
 */
#define LINKY_X 4
#define GRAPH_Y WORDS_Y + WORDS_HEIGHT + V_MARGIN
#define LINKY_HEIGHT 172

#define GRAPH_STEP 45
#define GRAPH_OFFSET_X 53
#define GRAPH_MAX_Y 140

void displayPrices(int offsetY, LinkyData* daily, double kmWPerHourPrice) {
  int y = offsetY + 16;
  drawText(LINKY_X, offsetY + 18, EURO, GxEPD_BLACK, &FONT_NORMAL);
  char price[10];
  for (int i = 0; i < CHART_DAYS; i++) {
    int x = GRAPH_OFFSET_X + i * GRAPH_STEP;

    if (daily->values[i] == 0) {
      drawText(x, y, "n/a", GxEPD_RED, &FONT_SMALL);
    } else {
      double p = daily->values[i] * kmWPerHourPrice / 1000;
      sprintf(price, "%.1lf", p);
      Serial.printf("price: %s\n", price);
      drawText(x, y, price, p >= LINKY_PRICE_THRESHOLD ? GxEPD_BLACK : GxEPD_RED, &FONT_SMALL);
    }
  }
}

void displayDays(uint offsetY, BandwidthData* daily) {
  char date[3];
  for (int i = 0; i < CHART_DAYS; i++) {
    if (strlen(daily->days[i]) >= 9) {  // str is like yyyy-mm-dd
      drawText(GRAPH_OFFSET_X + i * GRAPH_STEP, offsetY + 160, &daily->days[i][8], GxEPD_BLACK, &FONT_SMALL);
    }
  }
}

int mapToYElectricity(int y) {
  int yy = y * 7;
  int maxY = GRAPH_MAX_Y;
  int r = yy < maxY ? maxY - yy : maxY;
  // Serial.printf("mapToY: %i ⁻> %i\n", y, r);
  return r;
}

int mapToYBandwidth(int mbValue) {
  // Convert Mb to Gb, then map to display coordinates
  // Bandwidth scale: 0-50 Gb should map to same vertical space as 0-15 kW
  // Since 50 Gb should map to same height as 15 kW:
  float gbValue = mbValue / 1000.0;  // Convert Mb to Gb
  float normalized = gbValue / 50.0 * 15.0;  // Scale 0-50 Gb to 0-15 range
  int yy = normalized * 7;
  int maxY = GRAPH_MAX_Y;
  int r = yy < maxY ? maxY - yy : maxY;
  // Serial.printf("mapToYBandwidth: %d Mb (%.1f Gb) -> %d\n", mbValue, gbValue, r);
  return r;
}

void displayScale(uint offsetY) {
  char s[4];
  Serial.println("Scale");
  for (int i = 0; i <= 15; i += 3) {
    int y = offsetY + mapToYElectricity(i);
    sprintf(s, "%2dk", i);
    drawText(LINKY_X, 5 + y, s, GxEPD_BLACK, &FONT_SMALL);
    display.fillRect(38, y, 410, 2, GxEPD_RED);
  }
}

void displayBandwidthScale(uint offsetY) {
  char s[5];
  Serial.println("Bandwidth Scale");
  // Draw scale on right side with 10 Gb increments (0, 10, 20, 30, 40, 50)
  for (int i = 0; i <= 50; i += 10) {
    int y = offsetY + mapToYBandwidth(i * 1000); // Convert Gb back to Mb for mapping
    sprintf(s, "%2d", i);
    drawTextRightAlign(display.width() - 4, 5 + y, s, GxEPD_BLACK, &FONT_SMALL);
  }
}

void displayConsumption(uint offsetY, LinkyData* daily) {
  for (int i = 0; i < CHART_DAYS; i++) {
    if (daily->values[i] == 0) break;
    int value = daily->values[i] / 1000;
    int x = GRAPH_OFFSET_X + 14 + i * GRAPH_STEP;
    int y = offsetY + mapToYElectricity(value);
    display.fillRect(x, y, 12, (offsetY + GRAPH_MAX_Y) - y, GxEPD_BLACK);
  }
}

void displayMaxPower(uint offsetY, LinkyData* power) {
  for (int i = 0; i < CHART_DAYS; i++) {
    if (power->values[i] == 0) break;
    int value = power->values[i] / 1000;
    int x = GRAPH_OFFSET_X + 4 + i * GRAPH_STEP;
    int y = offsetY + mapToYElectricity(value);
    display.fillRect(x, y, 6, (offsetY + GRAPH_MAX_Y) - y, GxEPD_RED);
  }
}

void displayLinkyData(LinkyData* daily, LinkyData* power, LinkyMetaData* metadata) {
  displayScale(GRAPH_Y);
  displayPrices(GRAPH_Y, daily, metadata->price);
  displayConsumption(GRAPH_Y, daily);
  displayMaxPower(GRAPH_Y, power);
  drawLine(GRAPH_Y + LINKY_HEIGHT - V_MARGIN, 2, GxEPD_BLACK);
}

void drawDiamond(int centerX, int centerY, int size, int color) {
  // Top triangle
  display.fillTriangle(centerX, centerY - size, centerX + size, centerY, centerX - size, centerY, color);
  // Bottom triangle
  display.fillTriangle(centerX, centerY + size, centerX + size, centerY, centerX - size, centerY, color);
}

void displayBandwidth(uint offsetY, BandwidthData* daily) {
  for (int i = 0; i < CHART_DAYS; i++) {
    int value = daily->values[i];
    int x = GRAPH_OFFSET_X + i * GRAPH_STEP;
    int y = offsetY + mapToYBandwidth(value);
    drawDiamond(x - 6, y, 6, GxEPD_BLACK);
  }
}

void displayBandwidthData(BandwidthData* daily) {
  displayDays(GRAPH_Y, daily);
  displayBandwidthScale(GRAPH_Y);
  drawTextRightAlign(display.width() - 2, GRAPH_Y + 18, "Go", GxEPD_BLACK, &FONT_NORMAL);
  displayBandwidth(GRAPH_Y, daily);
}

void displayGraphError(char* text) {
  displayError(GRAPH_Y + 20, text);
}
