#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <WiFlyHQ.h>

#define SSID "YourWiFiSSID"
#define PASSWORD "YourWiFiPassword"
#define API_KEY "YourRightechAPIKey"
#define DEVICE_ID "YourDeviceID"

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(9600);

  if (!aht.begin()) {
    Serial.println("Could not find AHT sensor, check wiring!");
    while (1);
  }

  WiFly.begin();

  if (!WiFly.join(SSID, PASSWORD)) {
    Serial.println("Failed to join Wi-Fi network.");
    while (1);
  }
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  if (isnan(humidity.relative_humidity) || isnan(temp.temperature)) {
    Serial.println("Failed to read from AHT sensor!");
    return;
  }

  String payload = "{\"humidity\":" + String(humidity.relative_humidity) +
                   ",\"temperature\":" + String(temp.temperature) + "}";

  String request = "POST /v1/device/" + DEVICE_ID + "/telemetry";
  request += " HTTP/1.1\r\n";
  request += "Host: m2.exosite.io\r\n";
  request += "X-Exosite-API-Key: " + String(API_KEY) + "\r\n";
  request += "Content-Type: application/x-www-form-urlencoded\r\n";
  request += "Content-Length: " + String(payload.length()) + "\r\n\r\n";
  request += payload;

  Serial.println("Sending data to Rightech Cloud...");

  WiFly.println(request);

  delay(5000);  // Adjust the delay as needed
}

