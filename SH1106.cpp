#include "SH1106.h"

// CONSTRUCTORS, DESTRUCTOR ------------------------------------------------

SH1106::SH1106(i2c_inst_t *i2cBus, uint8_t addr, uint16_t w, uint16_t h)
    : Adafruit_GrayOLED(i2cBus, addr, w, h) {}

/*!
    @brief  Destructor for SSD1306 object.
*/
SH1106::~SH1106(void) {}

void SH1106::begin(uint8_t addr, bool reset)
{

  Adafruit_GrayOLED::_init();

  _page_start_offset =
      2; // the SH1106 display we have found requires a small offset into memory

  // Init sequence, make sure its under 32 bytes, or split into multiples!
  // clang-format off
  static const uint8_t init[] = {
      SH110X_DISPLAYOFF,               // 0xAE
      SH110X_SETDISPLAYCLOCKDIV, 0x80, // 0xD5, 0x80,
      SH110X_SETMULTIPLEX, 0x3F,       // 0xA8, 0x3F,
      SH110X_SETDISPLAYOFFSET, 0x00,   // 0xD3, 0x00,
      SH110X_SETSTARTLINE,             // 0x40
      SH110X_DCDC, 0x8B,               // DC/DC on
      SH110X_SEGREMAP + 1,             // 0xA1
      SH110X_COMSCANDEC,               // 0xC8
      SH110X_SETCOMPINS, 0x12,         // 0xDA, 0x12,
      SH110X_SETCONTRAST, 0xFF,        // 0x81, 0xFF
      SH110X_SETPRECHARGE, 0x1F,       // 0xD9, 0x1F,
      SH110X_SETVCOMDETECT, 0x40,      // 0xDB, 0x40,
      0x33,                            // Set VPP to 9V
      SH110X_NORMALDISPLAY,
      SH110X_MEMORYMODE, 0x10,         // 0x20, 0x00
      SH110X_DISPLAYALLON_RESUME,
  };

        send_cmd_list(init, count_of(init));

        sleep_ms(100);
        send_cmd(SH110X_DISPLAYON);
}

// REFRESH DISPLAY ---------------------------------------------------------

/*!
    @brief  Push data currently in RAM to SH110X display.
    @note   Drawing operations are not visible until this function is
            called. Call after each graphics command, or after a whole set
            of graphics commands, as best needed by one's own application.
*/
void SH1106::display()
{
  uint8_t *ptr = buffer;
  uint8_t dc_byte = 0x40;
  uint8_t pages = ((HEIGHT + 7) / 8);
  uint8_t bytes_per_page = WIDTH;
  uint8_t first_page = window_y1 / 8;
  uint8_t page_start = MIN(bytes_per_page, (uint8_t)window_x1);
  uint8_t page_end = (uint8_t)MAX((int)0, (int)window_x2);

  for (uint8_t p = first_page; p < pages; p++) {
    uint8_t bytes_remaining = bytes_per_page;
    ptr = buffer + (uint16_t)p * (uint16_t)bytes_per_page;
    // fast forward to dirty rectangle beginning
    ptr += page_start;
    bytes_remaining -= page_start;
    // cut off end of dirty rectangle
    bytes_remaining -= (WIDTH - 1) - page_end;

      uint16_t maxbuff = i2cDevice->getMaxBufferSize() - 1;

      uint8_t cmd[] = {
          0x00, (uint8_t)(SH110X_SETPAGEADDR + p),
          (uint8_t)(0x10 + ((page_start + _page_start_offset) >> 4)),
          (uint8_t)((page_start + _page_start_offset) & 0xF)};

      send_cmd_list(cmd, 4);

      while (bytes_remaining) {
        uint8_t to_write = MIN(bytes_remaining, (uint8_t)maxbuff);
        send_buf(ptr, to_write);
        ptr += to_write;
        bytes_remaining -= to_write;
      }    
  }
  // reset dirty window
  window_x1 = 1024;
  window_y1 = 1024;
  window_x2 = -1;
  window_y2 = -1;
}

void SH1106::print(const char *str)
{

  for (uint i = 0; str[i] != '\0'; ++i)
  {
    write(str[i]);
  }
  
}
