#include <WiFlyHQ.h>

#define SSID "YourWiFiSSID"
#define PASSWORD "YourWiFiPassword"
#define API_KEY "YourRightechAPIKey"
#define DEVICE_ID "YourDeviceID"

void setup() {
  Serial.begin(9600);

  WiFly.begin();

  if (!WiFly.join(SSID, PASSWORD)) {
    Serial.println("Failed to join Wi-Fi network.");
    while (1);
  }
}

void loop() {
  if (WiFly.available()) {
    String response = WiFly.readStringUntil('\n');
    Serial.println("Received from Rightech Cloud: " + response);

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

