/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read new NUID from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
   Reader on the Arduino SPI interface.

   When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
   then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
   you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
   will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
   when removing the PICC from reading distance too early.

   @license Released into the public domain.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define Sv_PIN 5
#define RSv_PIN 6

MFRC522 rfid1(SS_PIN, RST_PIN);
MFRC522 rfid2(Sv_PIN, RSv_PIN);


MFRC522::MIFARE_Key key;

byte nuidPICC[4];

int rightStatus = 1;
int leftStatus = 1;
int gripLeft;
int gripRight;
#define Left A0
#define Right A1

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  SPI.begin(); // Init SPI bus
  rfid1.PCD_Init(); // Init MFRC522
  rfid2.PCD_Init();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

}

void loop() {

  if ( ! rfid1.PICC_IsNewCardPresent())
    return;

  if ( ! rfid1.PICC_ReadCardSerial())
    return;

  if ( ! rfid2.PICC_IsNewCardPresent())
    return;

  if ( ! rfid2.PICC_ReadCardSerial())
    return;
  MFRC522::PICC_Type piccType = rfid1.PICC_GetType(rfid1.uid.sak);
  //  MFRC522::PICC_Type piccType = rfid2.PICC_GetType(rfid2.uid.sak);

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
  }

  if (rfid1.uid.uidByte[0] != nuidPICC[0] ||
      rfid1.uid.uidByte[1] != nuidPICC[1] ||
      rfid1.uid.uidByte[2] != nuidPICC[2] ||
      rfid1.uid.uidByte[3] != nuidPICC[3] ) {

    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid1.uid.uidByte[i];
      nuidPICC[i] = rfid2.uid.uidByte[i];
    }
    if (rfid2.uid.uidByte[0] != nuidPICC[0] ||
        rfid2.uid.uidByte[1] != nuidPICC[1] ||
        rfid2.uid.uidByte[2] != nuidPICC[2] ||
        rfid2.uid.uidByte[3] != nuidPICC[3] ) {

      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = rfid1.uid.uidByte[i];
        nuidPICC[i] = rfid2.uid.uidByte[i];
      }
      //sensors
      rightStatus = digitalRead(7);
      leftStatus = digitalRead(8);
      gripLeft = analogRead(Left);
      gripRight = analogRead(Right);
      Serial.print(rightStatus);
      Serial.print(",");
      Serial.print(leftStatus);
      Serial.print(",");
      Serial.print(gripLeft);
      Serial.print(",");
      Serial.print(gripRight);
      Serial.print(",");
      printDec(rfid1.uid.uidByte, rfid1.uid.size);
      Serial.print(",");
      printDec(rfid2.uid.uidByte, rfid2.uid.size);
      Serial.println("");
      delay(100);
      //sensorsend

    }

  }

  rfid1.PICC_HaltA();

  rfid1.PCD_StopCrypto1();

  rfid2.PICC_HaltA();

  rfid2.PCD_StopCrypto1();
}



void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "0" : "");
    Serial.print(buffer[i], DEC);
  }
}
