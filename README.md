# ESP32 home news epaper

A display showing weather (current, today and tomorrow), agenda & power comsumption (for french Linky service) on an e-ink screen, powered by an esp32.

That project combines previous projects into a single e-ink screen :

  * [IoT eink Weather Station](https://hackaday.io/project/171910-iot-eink-weather-station)
  * [esp32next-calendar-events](https://github.com/paulgreg/esp32-next-calendar-events)
  * [Linky Daily Consumption](https://hackaday.io/project/177065-linky-daily-consumption)


Weather is fetched from [Open Weather Map](https://openweathermap.org/). You’ll need to create an account to get an API key.

The « agenda » and power consumption needs JSON produced and served on a server :
- [next-calendar-events-server](https://github.com/paulgreg/next-calendar-events-server) to fetch and format agenda events,
- [bokub/linky](https://github.com/bokub/linky), launched daily to produces daily consumption and max power files. You will also need a price.json file containing `{ "price": "0.23" }` 

You’ll need to copy `parameters.h.dist` to `parameters.h` and change it to your needs.

## Hardware

  * [WaveShare ESP32 Driver Board](https://www.waveshare.com/product/e-paper-esp32-driver-board.htm)
  * [5.83" b/w/r e-ink screen](https://www.waveshare.com/5.83inch-e-paper-b.htm) GDEW0583Z83 648x480, EK79655 (GD7965)

### Mapping of Waveshare ESP32 Driver Board

  - BUSY -> 25
  - RST -> 26
  - DC -> 27
  - CS-> 15
  - CLK -> 13 
  - DIN -> 14

## Software

That project is made possible by amazing [ZinggJM/GxEPD2](https://github.com/ZinggJM/GxEPD2) and wonderful [bokub/linky](https://github.com/bokub/linky) Open Source projects. Thanks
