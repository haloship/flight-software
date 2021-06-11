#include <Arduino.h>
#include <SPI.h>
#include <RH_RF69.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#include "config.hpp"
#include "bmx055.hpp"
#include "lps25.hpp"
#include "ublox.hpp"


// Singleton instance of the radio driver
RH_RF69 rf69_transceiver(RFM69_CS, RFM69_INT);
SFE_UBLOX_GNSS myGNSS;
int16_t packetnum = 0; // packet counter, we increment per xmission

void Blink(byte PIN, byte DELAY_MS, byte loops)
{
  for (byte i = 0; i < loops; i++)
  {
    digitalWrite(PIN, HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN, LOW);
    delay(DELAY_MS);
  }
}

bool check_sensors()
{
  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69_transceiver.init())
  {
    Serial.println("RFM69 radio init failed");
    return false;
  }
  Serial.println("RFM69 radio init OK!");

  if (!myGNSS.begin())
  {
    Serial.println("u-blox GNSS module init failed");
    return false;
  }
  //This will pipe all NMEA sentences to the serial port so we can see them
  // myGNSS.setNMEAOutputPort(Serial);
  Serial.println("u-blox GNSS module init OK!");

  if (!lps.begin_SPI(LPS_CS))
  {
    Serial.println("Failed to find LPS25 chip");
    return false;
  }
  Serial.println("LPS25 Found!");
  //  lps.setDataRate(LPS25_RATE_12_5_HZ);
  Serial.print("Data rate set to: ");
  switch (lps.getDataRate())
  {
  case LPS25_RATE_ONE_SHOT:
    Serial.println("One Shot");
    break;
  case LPS25_RATE_1_HZ:
    Serial.println("1 Hz");
    break;
  case LPS25_RATE_7_HZ:
    Serial.println("7 Hz");
    break;
  case LPS25_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LPS25_RATE_25_HZ:
    Serial.println("25 Hz");
    break;
  }

  return true;
}

void rf69_communicate()
{
  if (rf69_transceiver.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69_transceiver.recv(buf, &len))
    {
      if (!len)
        return;
      buf[len] = 0;
      Serial.print("Received [");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char *)buf);
      Serial.print("RSSI: ");
      Serial.println(rf69_transceiver.lastRssi(), DEC);

      if (strstr((char *)buf, "Hello World"))
      {
        // Send a reply!
        uint8_t data[] = "And hello back to you";
        rf69_transceiver.send(data, sizeof(data));
        rf69_transceiver.waitPacketSent();
        Serial.println("Sent a reply");
        Blink(LED, 40, 3); //blink LED 3 times, 40ms between blinks
      }
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}



void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 RX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  check_sensors();

  // BMX055_Init();

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69_transceiver.setFrequency(RF69_FREQ))
  {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69_transceiver.setTxPower(20, true); // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                   0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69_transceiver.setEncryptionKey(key);

  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");
  Serial.print((int)RF69_FREQ);
  Serial.println(" MHz");

  myGNSS.setAutoPVTcallback(&printPVTdata); 
}

void loop()
{
  rf69_communicate();
  lps25_retrieve_data();
  myGNSS.checkUblox();
  myGNSS.checkCallbacks();
  Serial.println("");
  // bmx055_retrieve_data();
  delay(1000);
}
