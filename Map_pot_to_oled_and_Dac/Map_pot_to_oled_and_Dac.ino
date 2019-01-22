 
// PROGRESS
// Oled installed single number
// super laggy!!

// #include <SPI.h>                   // This library allows you to communicate with SPI devices 
#include <Wire.h>                     // This library allows you to communicate with I2C / TWI devices 

// DAC

#include <Adafruit_MCP4725.h>         // this is the library for the DAC
Adafruit_MCP4725 dac;                 // constructor

int throttleIn = A0;                  // sets the pin for Throttle Input, testing with variable resistor
int throttleState = 820;              // create a variable for ThrottleState to be sent to the DAC, 820 is 1.0v (DAC is 0-4095)

// SCREEN

#include <Adafruit_GFX.h>             // Adafruit graphics library
#include <Adafruit_SSD1306.h>         // Adafruit Monochrome OLEDs library based on SSD1306 drivers
#define OLED_RESET 4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET); // ? not sure what this is


void setup() 
{
  Serial.begin(9600);                   // initialize serial communication at 9600 bits per second:

  // DAC

  dac.begin(0x62);                      // start the dac at it's address 

  // DISPLAY

// tried removing some bits below as they were repeated later in the loop, and seems ok

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();                          // display the display!
  display.clearDisplay();                     // clear the buffer.
  display.setTextSize(2);                     // 
  display.setCursor(0, 0);                    // this is supposed to position the text on screen, but doesn't work for me
  display.setTextColor(WHITE);
}


void loop() {                            // code runs in a loop

  // DAC

  int throttleIn = analogRead(0);                   // read the throttle input
  throttleIn = map(throttleIn, 0, 1023, 820, 4095); // remap the throttle to the range that the DAC is expecting
  dac.setVoltage(throttleIn, false);                // write the throttle output to the DAC, set the store to EEPROM to false
  
  // DISPLAY

  display.setCursor(0, 0);
  display.print("throttleIn");
  display.println(throttleIn*0.001221001221);
  display.display();                                //you have to tell the display to...display
//  delay(20);
  display.clearDisplay();

}
