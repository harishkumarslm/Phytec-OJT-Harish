#include <WiFi.h>

#define SSID "YourWiFiSSID"
#define PASSWORD "YourWiFiPassword"
#define TOKEN "YourThingsBoardToken"

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  // Check for control commands from ThingsBoard Phytec Cloud
  if (WiFi.available()) {
    String response = WiFi.readStringUntil('\n');
    Serial.println("Received from ThingsBoard Phytec Cloud: " + response);

    // Process the response and control PC13, PC17, and PC19 accordingly
    if (response.indexOf("PC13_ON") != -1) {
      digitalWrite(PC13, HIGH);
    } else if (response.indexOf("PC13_OFF") != -1) {
      digitalWrite(PC13, LOW);
    }
    
    // Repeat for PC17 and PC19

    delay(1000);  // Adjust the delay as needed
  }
}

