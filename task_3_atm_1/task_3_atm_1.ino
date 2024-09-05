#include <Wire.h>  // Include the Wire library for I2C communication

const int sensorAddress = 0x28; // Default I2C address for MS4525DO
const float airDensity = 1.225; // Air density at sea level in kg/m³

void setup() {
  Serial.begin(9600); // Initialize serial communication
  Wire.begin();       // Initialize I2C communication
  
  // Check if the sensor is connected
  Wire.beginTransmission(sensorAddress);
  if (Wire.endTransmission() != 0) {
    Serial.println("Error: Sensor not detected.");
    while (true); // Halt execution if sensor not found
  }
}

void loop() {
  float pressureDifference = readPressureDifference(); // Read pressure difference
  
  if (pressureDifference >= 0) {
    float airSpeed = calculateAirSpeed(pressureDifference); // Calculate air speed
    Serial.print("Pressure Difference (Pa): ");
    Serial.print(pressureDifference);
    Serial.print(" Air Speed (m/s): ");
    Serial.println(airSpeed);
  } else {
    Serial.println("Error: Failed to read pressure difference.");
  }
  
  delay(1000); // Delay for 1 second before the next reading
}

// Function to read pressure difference from the MS4525DO sensor
float readPressureDifference() {
  Wire.beginTransmission(sensorAddress);
  Wire.write(0x00); // Register address to read pressure difference
  Wire.endTransmission();
  
  Wire.requestFrom(sensorAddress, 2); // Request 2 bytes of data
  if (Wire.available() == 2) {
    uint16_t rawData = Wire.read() << 8 | Wire.read(); // Read the raw data
    float pressureDifference = (rawData - 16384) * 0.00122; // Convert to pressure difference (Pa)
    return pressureDifference;
  } else {
    return -1; // Indicate error if not enough data was received
  }
}

// Function to calculate air speed from pressure difference
float calculateAirSpeed(float pressureDifference) {
  return sqrt(2 * pressureDifference / airDensity);
}
