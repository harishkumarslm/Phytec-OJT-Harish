#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(PC13, OUTPUT);
  pinMode(PC17, OUTPUT);
  pinMode(PC19, OUTPUT);

  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (rfid.uid.uidByte[0] == 0x01 && rfid.uid.uidByte[1] == 0x02 && rfid.uid.uidByte[2] == 0x03) {
      digitalWrite(PC13, HIGH);
      delay(1000);
      digitalWrite(PC13, LOW);
    } else if (rfid.uid.uidByte[0] == 0x04 && rfid.uid.uidByte[1] == 0x05 && rfid.uid.uidByte[2] == 0x06) {
      digitalWrite(PC17, HIGH);
      delay(1000);
      digitalWrite(PC17, LOW);
    } else if (rfid.uid.uidByte[0] == 0x07 && rfid.uid.uidByte[1] == 0x08 && rfid.uid.uidByte[2] == 0x09) {
      digitalWrite(PC19, HIGH);
      delay(1000);
      digitalWrite(PC19, LOW);
    }
  }
}

