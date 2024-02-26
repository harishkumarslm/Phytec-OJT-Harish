#include <Wire.h>

#define AHT25_ADDR 0x38

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(AHT25_ADDR);
  Wire.write(0x00);
  Wire.endTransmission();

  delay(500);

  Wire.requestFrom(AHT25_ADDR, 6);

  if (Wire.available() == 6) {
    uint8_t data[6];
    for (int i = 0; i < 6; i++) {
      data[i] = Wire.read();
    }

    int humidity = ((data[1] << 12) | (data[2] << 4) | (data[3] >> 4)) * 100 / 0x100000;
    int temperature = (((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5]) * 200 / 0x100000 - 50;

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

  delay(2000);
}

