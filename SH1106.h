#pragma once
#include "Adafruit_GrayOLED.h"

/// fit into the SH110X_ naming scheme
#define SH110X_BLACK 0   ///< Draw 'off' pixels
#define SH110X_WHITE 1   ///< Draw 'on' pixels
#define SH110X_INVERSE 2 ///< Invert pixels

// Uncomment to disable Adafruit splash logo
// #define SH110X_NO_SPLASH

#define SH110X_MEMORYMODE 0x20          ///< See datasheet
#define SH110X_COLUMNADDR 0x21          ///< See datasheet
#define SH110X_PAGEADDR 0x22            ///< See datasheet
#define SH110X_SETCONTRAST 0x81         ///< See datasheet
#define SH110X_CHARGEPUMP 0x8D          ///< See datasheet
#define SH110X_SEGREMAP 0xA0            ///< See datasheet
#define SH110X_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SH110X_DISPLAYALLON 0xA5        ///< Not currently used
#define SH110X_NORMALDISPLAY 0xA6       ///< See datasheet
#define SH110X_INVERTDISPLAY 0xA7       ///< See datasheet
#define SH110X_SETMULTIPLEX 0xA8        ///< See datasheet
#define SH110X_DCDC 0xAD                ///< See datasheet
#define SH110X_DISPLAYOFF 0xAE          ///< See datasheet
#define SH110X_DISPLAYON 0xAF           ///< See datasheet
#define SH110X_SETPAGEADDR 0xB0         ///< Specify page address to load display RAM data to page address register
#define SH110X_COMSCANINC 0xC0          ///< Not currently used
#define SH110X_COMSCANDEC 0xC8          ///< See datasheet
#define SH110X_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SH110X_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SH110X_SETPRECHARGE 0xD9        ///< See datasheet
#define SH110X_SETCOMPINS 0xDA          ///< See datasheet
#define SH110X_SETVCOMDETECT 0xDB       ///< See datasheet
#define SH110X_SETDISPSTARTLINE 0xDC    ///< Specify Column address to determine the initial display line or COM0.

#define SH110X_SETLOWCOLUMN 0x00  ///< Not currently used
#define SH110X_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SH110X_SETSTARTLINE 0x40  ///< See datasheet

class SH1106 : public Adafruit_GrayOLED
{
public:
  SH1106(i2c_inst_t *i2cBus, uint8_t addr, uint16_t w, uint16_t h);
  ~SH1106();

  void begin(uint8_t i2caddr = 0x3C, bool reset = true);
  void display();

protected:
  /*! some displays are 'inset' in memory, so we have to skip some memory to
   * display */
  uint8_t _page_start_offset = 0;

private:
};
