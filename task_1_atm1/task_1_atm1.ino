const int sensorPin = A0; // Analog pin connected to the sensor
const int windowSize = 5; // Number of samples for the moving average filter
const int maxTime = 600;// Max no of timestamps for compiling final data

int altitude[windowSize]; // Array to store the altitude
int readIndex= 0; // Current index in the altitude array which corresponds to readIndex
int total = 0; // Sum of the current window of samples
int average = 0; // Moving average result

int timeStamp=0;// Index of final data
int finaldata[maxTime];//Compiled Moving average result in an array


void setup() {
  Serial.begin(9600); 
  // Initialize all altitude to 0
  for (int i = 0; i < windowSize; i++) {
    altitude[i] = 0;
  }
}

void loop() {
  // Subtract the oldest reading from the total
  total = total - altitude[readIndex];
  
  // Read new data from the sensor
  altitude[readIndex] = analogRead(sensorPin);
  
  // Add the new reading to the total
  total = total + altitude[readIndex];
  
  // Calculate the average
  average = total / windowSize;

  finaldata[timeStamp]=average;
  
  // Print the moving average to the serial monitor
  Serial.print("Moving Average: ");
  Serial.println(average);
  
  // Move to the next index in the array
  readIndex+= 1;
  timeStamp+= 1;
  
  
  if (readIndex>= windowSize) {
    readIndex= 0;
  }

  // Delay for a short period before the next reading
  delay(100);
}
