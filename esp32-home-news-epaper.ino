
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define USE_HSPI_FOR_EPD

#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
#define GxEPD2_DRIVER_CLASS GxEPD2_583c_Z83 // GDEW0583Z83 648x480, EK79655 (GD7965)

#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
SPIClass hspi(HSPI);

void setup() {
  Serial.begin(115200);
  Serial.println("\nsetup");
  // *** special handling for Waveshare ESP32 Driver board *** //
  hspi.begin(13, 12, 14, 15); // remap hspi for EPD (swap pins)
  display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
  // *** end of special handling for Waveshare ESP32 Driver board *** //
  display.init(115200);
  display.setRotation(1);


  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(100, 100);
    display.print("HelloWorld");
  } while (display.nextPage());
  
  Serial.println("setup done");

  display.powerOff();
  display.hibernate();
}

void loop() {
}
