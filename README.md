# ESP32 home news epaper

Display weather, power comsumption and agenda on an e-ink screen, powered by an esp32.

That project combines previous projects into a single e-ink screen.

## Hardware

  * ESP32: https://www.waveshare.com/product/e-paper-esp32-driver-board.htm
  * Screen : GDEW0583Z83 5.83" b/w/r 648x480, EK79655 (GD7965)
  * https://www.waveshare.com/5.83inch-e-paper-b.htm


mapping of Waveshare ESP32 Driver Board
BUSY -> 25, RST -> 26, DC -> 27, CS-> 15, CLK -> 13, DIN -> 14

NOTE: this board uses "unusual" SPI pins and requires re-mapping of HW SPI to these pins in SPIClass
The Wavehare ESP32 Driver Board uses uncommon SPI pins for the FPC connector. It uses HSPI pins, but SCK and MOSI are swapped.
To use HW SPI with the ESP32 Driver Board, HW SPI pins need be re-mapped in any case. Can be done using either HSPI or VSPI.
Other SPI clients can either be connected to the same SPI bus as the e-paper, or to the other HW SPI bus, or through SW SPI.
The logical configuration would be to use the e-paper connection on HSPI with re-mapped pins, and use VSPI for other SPI clients.
VSPI with standard VSPI pins is used by the global SPI instance of the Arduino IDE ESP32 package.

## Software

  * https://github.com/ZinggJM/GxEPD2
