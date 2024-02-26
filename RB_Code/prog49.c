#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <WiFi.h>

#define SSID "YourWiFiSSID"
#define PASSWORD "YourWiFiPassword"
#define TOKEN "YourThingsBoardToken"

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);

  if (!aht.begin()) {
    Serial.println("Could not find AHT sensor, check wiring!");
    while (1);
  }

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
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

  String request = "POST /api/v1/" + TOKEN + "/telemetry";
  request += " HTTP/1.1\r\n";
  request += "Host: demo.thingsboard.io\r\n";
  request += "Content-Type: application/json\r\n";
  request += "Content-Length: " + String(payload.length()) + "\r\n\r\n";
  request += payload;

  Serial.println("Sending data to ThingsBoard Phytec Cloud...");

  WiFiClient client;
  if (client.connect("demo.thingsboard.io", 80)) {
    client.print(request);
    client.stop();
  }

  delay(5000);  // Adjust the delay as needed
}

