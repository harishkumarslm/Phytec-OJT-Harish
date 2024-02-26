#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    displayTagName(rfid.uid);
    delay(1000);
  }
}

void displayTagName(MFRC522::Uid uid) {
  if (uid.uidByte[0] == 0x01 && uid.uidByte[1] == 0x02 && uid.uidByte[2] == 0x03) {
    Serial.println("Tag 1: John Doe");
  } else if (uid.uidByte[0] == 0x04 && uid.uidByte[1] == 0x05 && uid.uidByte[2] == 0x06) {
    Serial.println("Tag 2: Jane Smith");
  } else if (uid.uidByte[0] == 0x07 && uid.uidByte[1] == 0x08 && uid.uidByte[2] == 0x09) {
    Serial.println("Tag 3: Bob Johnson");
  } else {
    Serial.println("Unknown Tag");
  }
}

