
// Voltmeter using 180k:10k voltage divider for 0-95v
// remove delay
// add another one for Shunt other side and measure current

// screen

#include <Wire.h>                     // This library allows you to communicate with I2C / TWI devices 
#include <Adafruit_GFX.h>             // Adafruit graphics library
#include <Adafruit_SSD1306.h>         // Adafruit Monochrome OLEDs library based on SSD1306 drivers
#define OLED_RESET 4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET); // ? not sure what this is

// temp

#define thermPin1 A2                     // What pin to connect the sensor to
#define thermPin2 A3                     // What pin to connect the sensor to
#define thermSamples1 50                  // how many samples to take for averaging the thermistor sensor reading - more takes loger
#define thermSamples2 50                  // how many samples to take for averaging the thermistor sensor reading - more takes loger
uint16_t samples1[thermSamples1];          // create a place to store ???
uint16_t samples2[thermSamples2];          // create a place to store ???

void setup(void) {

  Serial.begin(9600);                   // initialize serial communication at 9600 bits per second:

// display

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();                          // display the display!
  display.clearDisplay();                     // clear the buffer.
  display.setTextSize(1);                     // 
  display.setCursor(0, 0);                    // this is supposed to position the text on screen, but doesn't work for me
  display.setTextColor(WHITE);
 
 }

void loop(void) {

// thermistor 1

  uint8_t i;                            // set a 8-bit integer as 'i'
  float thermValue1;                     // create a place to store thermistor value
                                        // take N samples in a row, with a slight delay
  for (i=0; i< thermSamples1; i++) {
   samples1[i] = analogRead(thermPin1);   // read the thermistor value
   delay(10);
  }

                                        // average all the samples out
  thermValue1 = 0;
  for (i=0; i< thermSamples1; i++) {
     thermValue1 += samples1[i];
  }
  thermValue1 /= thermSamples1;


// thermistor 2

  float thermValue2;                     // create a place to store thermistor value
                                        // take N samples in a row, with a slight delay
  for (i=0; i< thermSamples2; i++) {
   samples2[i] = analogRead(thermPin2);   // read the thermistor value
   delay(10);
  }

                                        // average all the samples out
  thermValue2 = 0;
  for (i=0; i< thermSamples2; i++) {
     thermValue2 += samples2[i];
  }
  thermValue2 /= thermSamples2;
  
// averaging thingy for the temperature reading
//  float steinhart;
//  steinhart = thermValue1 / thermNominal;        // (R/Ro)
//  steinhart = log(steinhart);                   // ln(R/Ro)
//  steinhart /= bco;                             // 1/B * ln(R/Ro)
//  steinhart += 1.0 / (tempNominal + 273.15);    // + (1/To)
//  steinhart = 1.0 / steinhart;                  // Invert
//  steinhart -= 273.15;                          // convert to C


 // OLED Printout 1
  display.setCursor(0, 0);

  display.print("Voltage 1: ");
// maps the Analog input reading to the ratio of the voltage divider and outputs volts to one decimal place 
  display.println(thermValue1 * (5.0 / 1023.0) / 0.05555555556 * .974,1);

 // OLED Printout 2
  display.print("Voltage 2: ");
// maps the Analog input reading to the ratio of the voltage divider and outputs volts to one decimal place 
  display.println(thermValue2 * (5.0 / 1023.0) / 0.05555555556 * .974,1);
  
   // OLED Printout 1
  display.print("Watts: ");
// maps the Analog input reading to the ratio of the voltage divider and outputs volts to one decimal place 
  display.println(thermValue1 - thermValue2 * (5.0 / 1023.0) / 0.05555555556 * .974,1); // need to put the actual maths for 
  
  display.display();                                //you have to tell the display to...display
  delay(20);
  display.clearDisplay();


  delay(1000);
}
