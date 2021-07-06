/*
 * This simple Arduino sketch reads from an Adafruit MS8607 and a RadiationWatch counter
 * to give a periodic reading of pressure, temperature, and radiation level
 */

#include <Adafruit_Sensor.h>
#include <Adafruit_MS8607.h>
#include <RadiationWatch.h>

#define MS_DELTA 1000

RadiationWatch radiationWatch;
Adafruit_MS8607 ms8607;

unsigned long last_log = 0;

void setup()
{
  Serial.begin(9600);
  radiationWatch.setup();
  if (!ms8607.begin()) 
  {
    Serial.println("Failed to find MS8607 chip");
    while (1) { delay(10); }
  }
}

void loop()
{
  radiationWatch.loop();
  
  // If it's been more than MS_DELTA since the last long, then log
  if(millis() - last_log > MS_DELTA)
  {
    sensors_event_t temp, pressure, humidity;
    ms8607.getEvent(&pressure, &temp, &humidity);
    
    Serial.print(pressure.pressure);
    Serial.print(",");
    Serial.print(temp.temperature);
    Serial.print(",");
    Serial.print(radiationWatch.uSvh());
  
    Serial.println();

    last_log = millis();
  }
}
