
// TEMP SENSOR on A1
// remove delays and replace with milli??
// add to main code and output to screen
// Added display printout

// screen

#include <Wire.h>                     // This library allows you to communicate with I2C / TWI devices 
#include <Adafruit_GFX.h>             // Adafruit graphics library
#include <Adafruit_SSD1306.h>         // Adafruit Monochrome OLEDs library based on SSD1306 drivers
#define OLED_RESET 4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET); // ? not sure what this is

// temp

#define thermResistor 10000             // the value of the 'other' resistor
#define thermNominal 10000              // resistance at 25 degrees C
#define tempNominal 25                  // temp. for nominal resistance (almost always 25 C)
#define bco 3950                        // The beta coefficient of the thermistor (usually 3000-4000)
#define thermPin A1                     // What pin to connect the sensor to
#define thermSamples 5                  // how many samples to take for averaging the thermistor sensor reading - more takes loger

uint16_t samples[thermSamples];         // create a place to store ???

void setup(void) {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();                          // display the display!
  display.clearDisplay();                     // clear the buffer.
  display.setTextSize(2);                     // 
  display.setCursor(0, 0);                    // this is supposed to position the text on screen, but doesn't work for me
  display.setTextColor(WHITE);
 
  Serial.begin(9600);                   // initialize serial communication at 9600 bits per second:
  analogReference(EXTERNAL);            // connect AREF to 3.3V and use that as VCC, less noisy!
}

void loop(void) {

  uint8_t i;                            // set a 8-bit integer as 'i'
  float thermValue;                     // create a place to store thermistor value
                                        // take N samples in a row, with a slight delay
  for (i=0; i< thermSamples; i++) {
   samples[i] = analogRead(thermPin);   // read the thermistor value
   delay(10);
  }

                                        // average all the samples out
  thermValue = 0;
  for (i=0; i< thermSamples; i++) {
     thermValue += samples[i];
  }
  thermValue /= thermSamples;
  
  Serial.print("Avg analog reading "); 
  Serial.println(thermValue);                   // print out the value you read:

                                                // convert the value to resistance
  thermValue = 1023 / thermValue - 1;           // (1023/ADC - 1) 
  thermValue = thermResistor / thermValue;      // 10K / (1023/ADC - 1)
  
  Serial.print("Thermistor resistance "); 
  Serial.println(thermValue);

// averaging thingy for the temperature reading
  float steinhart;
  steinhart = thermValue / thermNominal;        // (R/Ro)
  steinhart = log(steinhart);                   // ln(R/Ro)
  steinhart /= bco;                             // 1/B * ln(R/Ro)
  steinhart += 1.0 / (tempNominal + 273.15);    // + (1/To)
  steinhart = 1.0 / steinhart;                  // Invert
  steinhart -= 273.15;                          // convert to C


 // OLED Printout
   display.setCursor(0, 0);
  display.print("Tempe C   ");
  display.println(steinhart);
  display.display();                                //you have to tell the display to...display
//  delay(20);
  display.clearDisplay();


  delay(1000);
}
