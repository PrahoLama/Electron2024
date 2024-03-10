#include "HX711.h"
#include <Arduino.h>
HX711 scale;

void setup() {
  Serial.begin(9600);
 Serial.println("Initializare scala");
  scale.begin(15, 14);

  Serial.print("Initial: \t\t");
  Serial.println(scale.read_average(10));  

  //Pentru calibrare 1kg = 2020 la set.scale(x,f)
  scale.set_scale(2020.f);                      

  Serial.println("Dupa Initializare:");

  Serial.print("Raw: \t\t\t");
  Serial.println(scale.read());                 // citire initiala

  Serial.print("Raw ave(20): \t\t");
  Serial.println(scale.read_average(20));       // afiseaza media a 20 de citiri

  Serial.print("Raw ave(5) - tare: \t");
  Serial.println(scale.get_value(5));   // media a 5 citiri fara masa neincarcata, set with tare()

  Serial.print("Calibrated ave(5): \t");
  Serial.println(scale.get_units(5), 1);       

  Serial.println("\nCitiri Greutate:");
}

void loop() {
  int t, i, n, T;
  double val, sum, sumsq, mean;
  float stddev;
  
  n = 20;
  t = millis();
  i = sum = sumsq = 0;
  while (i<n) {
    val = ((scale.read() - scale.get_offset()) / scale.get_scale());
    sum += val;
    sumsq += val * val;
    i++;
  }
  t = millis() - t;
  mean = sum / n;
  stddev = sqrt(sumsq / n - mean * mean);
  Serial.print(" Std "); Serial.print(i); Serial.print(" readings:\t");
  Serial.print(sum / n, 3); Serial.print("\t"); Serial.print(stddev, 3);
  Serial.print("\Timp:\t"); Serial.print(float(t)/1000, 3); Serial.println("Secs\n");

 
}

