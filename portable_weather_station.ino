/**************************************************************************************************
 *
 *      Small portable weather station based on the ESP32-C3 Supermini - 22 July 2025
 *      repo:  
 *
 **************************************************************************************************
 The sketch...
 **************************************************************************************************/


#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 32 // OLED display height in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define TOUCH_PIN 2

Adafruit_AHTX0 aht; // The temperature AHT10 sensor object
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile uint32_t time_last_pressed;
uint32_t time_millis;
uint32_t lastRefresh = 0;
const uint32_t refreshInterval = 2000;  // only redraw every 2 seconds


void updateDisplay(float temperature, float humidity){
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setFont(NULL);
  oled.setCursor(0, 10);
  oled.print(temperature);
  oled.print(" C ");
  oled.print(humidity);
  oled.println(" %");
  oled.display();
}

void IRAM_ATTR isr() {
  time_last_pressed = millis();
}

void setup() {
  Wire.begin(8, 9); // SDA, SCL for ESP32-C3
  Serial.begin(115200);

  // Setup the temp sensor
  Serial.println("Trying AHT10 Sensor");
  if (!aht.begin()) {
    Serial.println("Failed to find sensor!");
    while(1){
      delay(1000);
    }
  }
  Serial.println("Found sensor!");

  // Setup the OLED screen
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Failed to find screen");
    while(1){
      delay(1000);
    }
  }

  //Setup the touch button
  pinMode(TOUCH_PIN, INPUT);
  attachInterrupt(TOUCH_PIN, isr, RISING); // Interupt for the touch button
}

void loop() {
  time_millis = millis();
  if (time_millis - time_last_pressed < 8000){
    // Read temperature and humidity from the sensor
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp); // Populate the event objects
    // Print temperature and humidity to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");

    if (time_millis - lastRefresh > refreshInterval){
      updateDisplay(temp.temperature, humidity.relative_humidity);
      lastRefresh = millis();
    }  
  }
  else{
    oled.clearDisplay();
    oled.display();
  }
  
  // Delay between readings
  delay(300); 
}