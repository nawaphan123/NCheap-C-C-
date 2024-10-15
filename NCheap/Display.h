#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX1.h"
#include "Adafruit_SSD13061.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
void displaySetup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // initialize I2C addr 0x3c
  display.clearDisplay();                    // clears the screen and buffer
  display.setTextColor(WHITE);
  display.display();
}
void text(String m,int x,int y)
{
  
  display.setCursor(x, y);
  display.print(m);

}
void text(int m,int x,int y)
{
  
  display.setCursor(x, y);
  display.print(m);
 
}
void text(float m,int x,int y)
{
  
  display.setCursor(x, y);
  display.print(m);
  
}
void show()
{
  display.display();
}
void clear()
{
  display.clearDisplay();
  display.display();
}
