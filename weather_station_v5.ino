#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2          // DHT11 sensor pin
#define LDRPIN A0         // LDR sensor pin
#define VIBRATIONPIN 7    // Vibration sensor pin
#define LEDPIN 9

DHT dht(DHTPIN, DHT11);

float temperatureData[20];    // Array to store temperature readings
float humidityData[20];       // Array to store humidity readings
int lightLevelData[20];       // Array to store light level readings
int vibrationData[20];        // Array to store vibration readings
int dataCount = 0;            // Counter for the number of data points

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(VIBRATIONPIN, INPUT);  // Set Vibration sensor pin as input
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read light level from LDR sensor
  int lightLevel = analogRead(LDRPIN);

  // Read vibration sensor state
  int vibrationState = digitalRead(VIBRATIONPIN);

  if (vibrationState == 0) {
    digitalWrite(LEDPIN, HIGH);
    Serial.println("Earthquake - Be aware!");
    delay(5000);
  } else {
    digitalWrite(LEDPIN, LOW);
    delay(1000);
  }

  // Store sensor data in arrays
  temperatureData[dataCount] = temperature;
  humidityData[dataCount] = humidity;
  lightLevelData[dataCount] = lightLevel;
  vibrationData[dataCount] = vibrationState;

  // Increment data count and break the loop when reaching the desired number of data points
  dataCount++;
  if (dataCount >= 20) {
    while (1) {
      // Continue running an empty loop to maintain delay before restarting
    }
  }

  // Print sensor readings on Serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(", Humidity: ");
  Serial.print(humidity);
  Serial.print(", Light Level: ");
  Serial.print(lightLevel);
  Serial.print(", Vibration: ");
  Serial.println(vibrationState);

  // Send sensor data to the serial plotter
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(lightLevel);
  Serial.print(",");
  Serial.println(vibrationState);

  // Check light level and print corresponding message
  if (lightLevel == 0) {
    Serial.println("Sunny day");
  } else if (lightLevel >= 0 && lightLevel <= 6) {
    Serial.println("Cloudy day");
  } else if (lightLevel > 9) {
    Serial.println("Night");
  }

  delay(1000);
}