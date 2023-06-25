#include <Arduino.h>
#include <esp_log.h>
#include <PCF8563T.h>

void setup() {
  USBSerial.begin(57600);
  Serial.begin(115200);
  Serial.println("START");

  Wire1.begin(1,2, uint32_t(400000));
  PCF8563.SetWire(&Wire1);
}

void loop() {

  USBSerial.printf("%s\n", PCF8563.GetDatetimeString().c_str());
  delay(1000);
}
