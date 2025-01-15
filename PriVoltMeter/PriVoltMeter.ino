#include <LedDisplay.h>

#define dataPin D6              // connects to the display's data in
#define registerSelect D7       // the display's register select pin
#define clockPin D8             // the display's clock pin
#define enable D9               // the display's chip enable pin
#define reset D10               // the display's reset pin

#define displayLength 4        // number of characters in the display


LedDisplay hcms29xx = LedDisplay(dataPin, registerSelect, clockPin,
                                  enable, reset, displayLength);

const float referenceVoltage = 3.22;
const int adcResolution = 4096;

void setup() {

  hcms29xx.begin();
  hcms29xx.setBrightness(15);
  analogReadResolution(12);

  Serial.begin(9600);
}
// Exponential moving average filter 
float smoothedValue = 0.0;
float alpha = 0.07;  // Smoothing factor (0 < alpha <= 1)

void loop() {
  int sensorValue = analogRead(A0);
  smoothedValue = alpha * sensorValue + (1 - alpha) * smoothedValue; 
  float voltage = (smoothedValue / (float)adcResolution) * referenceVoltage;


  // Serial.print("Voltage: ");
  // Serial.print(voltage, 3); // Print voltage with 2 decimal places
  // Serial.println(" V");
  hcms29xx.home();
  hcms29xx.print(voltage, DEC);

  delay(200);  // delay in between reads for stability
}
