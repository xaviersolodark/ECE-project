#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AHTX0.h"
#include "ScioSense_ENS160.h"

// Initialize sensor objects
Adafruit_AHTX0 aht;
ScioSense_ENS160 ens160;

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Initialize AHT21
    if (!aht.begin()) {
        Serial.println("Failed to find AHT21! Check connections.");
        while (1);
    }
    Serial.println("AHT21 initialized.");

    // Initialize ENS160
    if (ens160.begin()) {
        Serial.println("ENS160 initialized.");
    } else {
        Serial.println("Failed to find ENS160! Check connections.");
        while (1);
    }
    
    ens160.setMode(ENS160_OP_MODE_STANDARD);
}

void loop() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    
    // Read ENS160 data
    ens160.measure();
    
    // Print AHT21 data
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");

    // Print ENS160 data
    Serial.print("Air Quality Index (AQI): ");
    Serial.println(ens160.getAQI());
    Serial.print("TVOC (Total Volatile Organic Compounds): ");
    Serial.println(ens160.getTVOC());
    Serial.print("eCO2 (Equivalent CO2): ");
    Serial.println(ens160.geteCO2());

    Serial.println("---------------------------");
    delay(2000); // Delay for readability
}
