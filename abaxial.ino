#include <SPI.h>
#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

// ST7565 LCD connection with Arduino board using software SPI
#define LCD_DIN    12
#define LCD_SCLK   11
#define LCD_A0     10
#define LCD_RESET  9
#define LCD_CS     8
ST7565_LCD display = ST7565_LCD(LCD_DIN, LCD_SCLK, LCD_A0, LCD_RESET, LCD_CS);

void setup()   {                
  Serial.begin(9600);

  // initialize the ST7565 LCD display with contrast = 13 (0 <= coontrast <= 63)
  display.begin(0);

  display.display();

  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  abaxial();      // Draw characters of the default font
  delay(2000);
  display.clearDisplay();

  concentration();
  delay(1000);

}

// main loop (nothing here!)
void loop() {

}

void abaxial(void) {
  display.clearDisplay();
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(ST7565_ON);
  display.setCursor(22, 22);     // Start at top-left corner
  display.println(F("ABAXIAL"));

  display.display();
  delay(2000);
}

void concentration(void) {
      float number = 10.7;
  while(1){
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(ST7565_ON);
    display.setCursor(2, 2);     
    display.println(F("Concentration (mol/L)"));
    display.display();
    display.setTextSize(3);             
    display.setCursor(20, 30);    
    display.println(number);  
    display.display();
    number += 0.07;  
    delay(500);
    
  }
}
