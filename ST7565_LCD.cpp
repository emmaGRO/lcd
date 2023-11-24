/**********************************************************************************
* This is a library for ST7565 Monochrome LCD Display.
* These displays use SPI to communicate, 4 or 5 pins are required to  
*   interface
* This is a free library WITH NO WARRANTY, use it at your own risk!
*
* https://simple-circuit.com/
*
***********************************************************************************
* This library depends on Adafruit GFX library at
*   https://github.com/adafruit/Adafruit-GFX-Library
*   being present on your system. Please make sure you have installed the latest
*   version before using this library.
***********************************************************************************/

#include <avr/pgmspace.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifdef __AVR__
  #include <util/delay.h>
#endif

#include <stdlib.h>
#include <Adafruit_GFX.h>
#include "ST7565_LCD.h"

// the memory buffer for the LCD
// the memory buffer for the LCD
uint8_t st7565_buffer[1024] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x3, 0x7, 0xF, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x7F, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x1F, 0x3F, 0x70, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x6, 0x0, 0x0, 0x0, 0x3, 0x3, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xF, 0x7, 0x7, 
0x7, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF, 0x3F, 
0x70, 0x60, 0x60, 0x60, 0x60, 0x30, 0x7F, 0x3F, 0x0, 0x0, 0x1F, 0x3F, 0x70, 0x60, 0x60, 0x60, 
0x60, 0x39, 0xFF, 0xFF, 0x0, 0x6, 0x1F, 0x39, 0x60, 0x60, 0x60, 0x60, 0x30, 0x3F, 0x7F, 0x0, 
0x0, 0x60, 0xFF, 0xFF, 0x60, 0x60, 0x0, 0x7F, 0x7F, 0x70, 0x60, 0x60, 0x40, 0x0, 0x7F, 0x7F, 
0x0, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x60, 0xFF, 0xFF, 
0x60, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x80, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xE7, 0xE7, 0xE3, 
0xF3, 0xF9, 0xFF, 0xFF, 0xFF, 0xF7, 0x7, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 
0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0xF, 0x7, 0x3, 0x0, 0x0, 0x0, 0xC0, 
0xE0, 0x60, 0x20, 0x20, 0x60, 0xE0, 0xE0, 0xE0, 0x0, 0x0, 0x80, 0xC0, 0xE0, 0x60, 0x20, 0x60, 
0x60, 0xE0, 0xE0, 0xE0, 0x0, 0x0, 0x80, 0xC0, 0x60, 0x60, 0x20, 0x60, 0x60, 0xE0, 0xE0, 0x0, 
0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xE0, 
0x60, 0x60, 0x60, 0x60, 0xE0, 0x80, 0x0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0xE0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x3, 0x7, 0x1F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF1, 0xE3, 
0xE3, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFC, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF0, 0xE0, 0x80, 0x0, 0x0, 0x0, 0xC, 
0x1C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x7, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1C, 0xC, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 
0xF8, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 
0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x0, 0x0, 0x1E, 0x7F, 
0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0xFF, 0xFF, 0x0, 0x0, 0xFE, 0xFF, 0x1, 0x0, 0x0, 0x0, 
0xFF, 0xFF, 0x0, 0x0, 0x21, 0xF9, 0xF8, 0xDC, 0xCC, 0xCF, 0x7, 0x0, 0xC0, 0xFF, 0xFF, 0xC0, 
0x80, 0x0, 0xFF, 0xFF, 0xC0, 0xC0, 0x80, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x1F, 0x7F, 0xF9, 
0xC8, 0xC8, 0xC8, 0xC8, 0x79, 0x39, 0x0, 0x0, 0x71, 0xF9, 0xD8, 0xCC, 0xCE, 0x47, 0x3, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0, 
0xC0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 
0xC0, 0x80, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 
0x0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 0xC0, 
0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,};


// the most basic function, set a single pixel
void ST7565_LCD::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return;

  int16_t t;
  switch(rotation){
    case 1:
      t = x;
      x = y;
      y =  LCDHEIGHT - 1 - t;
      break;
    case 2:
      x = LCDWIDTH - 1 - x;
      y = LCDHEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = LCDWIDTH - 1 - y;
      y = t;
      break;
  }

  if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT))
    return;

  switch (color) {
    case ST7565_ON:
      st7565_buffer[x + (y / 8) * WIDTH] |= (1 << (7- y & 7));
      break;
    case ST7565_OFF:
      st7565_buffer[x + (y / 8) * WIDTH] &= ~(1 << (7 - y & 7));
      break;
    case ST7565_INVERSE:
      st7565_buffer[x + (y / 8) * WIDTH] ^= (1 << (7 - y & 7));
      break;
    }
}

// software SPI
ST7565_LCD::ST7565_LCD(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  sid = SID;
  sclk = SCLK;
  a0 = A0;
  rst = RST;
  cs = CS;
}
// software SPI without CS
ST7565_LCD::ST7565_LCD(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  sid = SID;
  sclk = SCLK;
  a0 = A0;
  rst = RST;
  cs = -1;
}
// hardware SPI
ST7565_LCD::ST7565_LCD(int8_t A0, int8_t RST, int8_t CS) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  // -1 for din and sclk specify using hardware SPI
  sid = -1;
  sclk = -1;
  a0 = A0;
  rst = RST;
  cs = CS;
}

void ST7565_LCD::begin(uint8_t contrast) {
  if (isHardwareSPI()) {
    // Setup hardware SPI.
    SPI.begin();
    SPI.setClockDivider(ST7565_SPI_CLOCK_DIV);
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
  }
  else {
    // Setup software SPI.
    pinMode(sid, OUTPUT);
    pinMode(sclk, OUTPUT);

    // Set software SPI ports and masks.
    clkport     = portOutputRegister(digitalPinToPort(sclk));
    clkpinmask  = digitalPinToBitMask(sclk);
    mosiport    = portOutputRegister(digitalPinToPort(sid));
    mosipinmask = digitalPinToBitMask(sid);
  }

  pinMode(a0, OUTPUT);
  pinMode(rst, OUTPUT);
  if (cs > 0) {
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
  }

  // reset the ST7565 display controller
  digitalWrite(rst, LOW);
  delay(500);
  digitalWrite(rst, HIGH);

  // LCD bias select
  command(CMD_SET_BIAS_7);
  // ADC select
  command(CMD_SET_ADC_NORMAL);
  // SHL select
  command(CMD_SET_COM_NORMAL);
  // Initial display line
  command(CMD_SET_DISP_START_LINE);

  // turn on voltage converter (VC=1, VR=0, VF=0)
  command(CMD_SET_POWER_CONTROL | 0x4);
  // wait for 50% rising
  delay(50);

  // turn on voltage regulator (VC=1, VR=1, VF=0)
  command(CMD_SET_POWER_CONTROL | 0x6);
  // wait >=50ms
  delay(50);

  // turn on voltage follower (VC=1, VR=1, VF=1)
  command(CMD_SET_POWER_CONTROL | 0x7);
  // wait
  delay(10);

  // set lcd operating voltage (regulator resistor, ref voltage resistor)
  command(CMD_SET_RESISTOR_RATIO | 0x6);
  command(CMD_DISPLAY_ON);
  command(CMD_SET_ALLPTS_NORMAL);
  setContrast(contrast);
  setRotation(0);
}

inline void ST7565_LCD::spiwrite(uint8_t c) {
  if (isHardwareSPI()) {
    // Hardware SPI write.
    SPI.transfer(c);
  }
  else {
    // Software SPI write with bit banging.
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      *clkport &= ~clkpinmask;
      if(c & bit) *mosiport |=  mosipinmask;
      else        *mosiport &= ~mosipinmask;
      delayMicroseconds(1);
      *clkport |=  clkpinmask;
      delayMicroseconds(1);
    }
  }
}

bool ST7565_LCD::isHardwareSPI() {
  return (sid == -1 && sclk == -1);
}

void ST7565_LCD::command(uint8_t c) {
  digitalWrite(a0, LOW);
  if (cs > 0)
    digitalWrite(cs, LOW);
  spiwrite(c);
  if (cs > 0)
    digitalWrite(cs, HIGH);
}

void ST7565_LCD::data(uint8_t c) {
  digitalWrite(a0, HIGH);
  if (cs > 0)
    digitalWrite(cs, LOW);
  spiwrite(c);
  if (cs > 0)
    digitalWrite(cs, HIGH);
}

// scroll display buffer to the right by 's' pixels
void ST7565_LCD::scrollRight(uint8_t s) {
  s &= 0x7F;
  while (s--) {
    for(uint8_t p = 0; p < 8; p++) {
      uint8_t msbyte = st7565_buffer[ ((p + 1) * LCDWIDTH) - 1 ];
      for(uint8_t col = (LCDWIDTH - 1); col > 0; col--) {
        st7565_buffer[ (p * LCDWIDTH) + col ] = st7565_buffer[ (p * LCDWIDTH) + col - 1 ];
      }
      st7565_buffer[ (p * LCDWIDTH) ] = msbyte;
    }
  }
}
// scroll display buffer to the left by 's' pixels
void ST7565_LCD::scrollLeft(uint8_t s) {
  s &= 0x7F;
  while (s--) {
    for(uint8_t p = 0; p < 8; p++) {
      uint8_t lsbyte = st7565_buffer[ p * LCDWIDTH ];
      for(uint8_t col = 0; col < (LCDWIDTH - 1); col++) {
        st7565_buffer[ (p * LCDWIDTH) + col ] = st7565_buffer[ (p * LCDWIDTH) + (col + 1) ];
      }
      st7565_buffer[ ((p + 1) * LCDWIDTH) - 1 ] = lsbyte;
    }
  }
}
// scroll display buffer down by 's' pixels
void ST7565_LCD::scrollDown(uint8_t s) {
  s &= 0x3F;
  while (s--) {
    for(uint8_t col = 0; col < LCDWIDTH; col++) {
      uint8_t msbit = st7565_buffer[ (7 * LCDWIDTH) + col ] & 0x01;  // save lcd buffer ms bit (very last bit in the display)
      for(uint8_t p = 7; p > 0; p--) {
        st7565_buffer[ (p * LCDWIDTH) + col ] = (st7565_buffer[ (p * LCDWIDTH) + col ] >> 1);  // shift right by 1
        uint8_t p_msb = st7565_buffer[ ((p-1) * LCDWIDTH) + col ] & 0x01;  // save page byte ms bit
        st7565_buffer[ (p * LCDWIDTH) + col ] |= (p_msb << 7);  // update page byte ls bit
      }
      // first page byte update
      st7565_buffer[col] = (st7565_buffer[col] >> 1);
      st7565_buffer[col] |= (msbit << 7);
    }
  }
}
// scroll display buffer up by 's' pixels
void ST7565_LCD::scrollUp(uint8_t s) {
  s &= 0x3F;
  while (s--) {
    for(uint8_t col = 0; col < LCDWIDTH; col++) {
      uint8_t lsbit = st7565_buffer[col] & 0x80;  // save lcd buffer ls bit (very first bit in the display)
      for(uint8_t p = 0; p < 7; p++) {
        st7565_buffer[ (p * LCDWIDTH) + col ] = (st7565_buffer[ (p * LCDWIDTH) + col ] << 1);  // shift left by 1
        uint8_t p_lsb = st7565_buffer[ ((p+1) * LCDWIDTH) + col ] & 0x80;  // save page byte ls bit
        st7565_buffer[ (p * LCDWIDTH) + col ] |= (p_lsb >> 7);  // update page byte ls bit
      }
      // first page byte update
      st7565_buffer[ (7 * LCDWIDTH) + col ] = (st7565_buffer[ (7 * LCDWIDTH) + col ] << 1);
      st7565_buffer[ (7 * LCDWIDTH) + col ] |= (lsbit >> 7);
    }
  }
}

// set LCD contrast with: 0 <= val <= 63
void ST7565_LCD::setContrast(uint8_t val) {
    command(CMD_SET_VOLUME_FIRST);
    command(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

// write display buffer in LCD hardware
void ST7565_LCD::display(void) {

  for(uint16_t p = 0; p < 8; p++) {

    //command(CMD_SET_PAGE | pagemap[p]);
    command( CMD_SET_PAGE | (7 - p) );

    // start at the beginning of the row
    command(CMD_SET_COLUMN_UPPER | 0);
    command(CMD_SET_COLUMN_LOWER | 0);
  
    for(uint8_t col = 0; col < LCDWIDTH; col++) {
      data(st7565_buffer[ (p * LCDWIDTH) + col ]);
    }
  }
}

// clear everything
void ST7565_LCD::clearDisplay(void) {
  memset(st7565_buffer, 0, LCDWIDTH*LCDHEIGHT/8);
  cursor_y = cursor_x = 0;
}

// end of code.