/*
 Test Arduino MAX485 Aurora ABB connection
 by Mischianti Renzo <http://www.mischianti.org>

 https://www.mischianti.org/2020/08/20/abb-aurora-pv-inverter-library-for-arduino-esp8266-and-esp32/
*/

#include "Arduino.h"
#include <Aurora.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>

//SoftwareSerial mySerial(10, 11); // RX, TX
//Aurora inverter = Aurora(2, &Serial1, 5);
Aurora inverter = Aurora(2, 10, 11, 5);

void SerialPrintData(byte *data) {
  for (int i = 0; i < 8; i++) {
    Serial.print((int)data[i]);
    Serial.print(F(" "));
  }
  Serial.println(F(" "));
}

void setup()
{
	Serial.begin(19200);
	inverter.begin();
}

// The loop function is called in an endless loop
void loop()
{
	Aurora::DataCumulatedEnergy cumulatedEnergy = inverter.readCumulatedEnergy(CUMULATED_MONTHLY_ENERGY);
    Serial.println(F("------------------------------------------"));
    Serial.println(F("INVERTER 2"));
    Serial.print(F("          Data ROW = ")); SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = ")); Serial.println(cumulatedEnergy.state.readState);
    Serial.print(F("Transmission State = ")); Serial.println(cumulatedEnergy.state.getTransmissionState());
    Serial.print(F("      Global State = ")); Serial.println(cumulatedEnergy.state.getGlobalState());
    Serial.print(F("           Energia = ")); Serial.print(cumulatedEnergy.energy); Serial.println(" Wh");
    Serial.println(F("------------------------------------------"));

	Serial.print(F("freeMemory()="));Serial.println(freeMemory());

	Aurora::DataLastFourAlarms lastFour = inverter.readLastFourAlarms();
	Serial.print(F("freeMemory()="));Serial.println(freeMemory());

    Serial.println(F("INVERTER 2"));
    Serial.print(F("          Data ROW = "));  SerialPrintData(inverter.receiveData);
	Serial.print(F("        Read State = "));  Serial.println(lastFour.state.readState);
    Serial.print(F("Transmission State = "));  Serial.println(lastFour.state.getTransmissionState());
    Serial.print(F("      Global State = "));  Serial.println(lastFour.state.getGlobalState());
    Serial.print(F("          Alarms 1 = "));  Serial.println(lastFour.getAlarm1State());
    Serial.print(F("          Alarms 2 = "));  Serial.println(lastFour.getAlarm2State());
    Serial.print(F("          Alarms 3 = "));  Serial.println(lastFour.getAlarm3State());
    Serial.print(F("          Alarms 4 = "));  Serial.println(lastFour.getAlarm4State());
    Serial.println(F("------------------------------------------"));

    Aurora::DataVersion version = inverter.readVersion();
    Serial.println("INVERTER 2");
    Serial.print("          Data ROW = "); SerialPrintData(inverter.receiveData);
    Serial.print("        Read State = "); Serial.println(version.state.readState);
    Serial.print("Transmission State = "); Serial.println(version.state.getTransmissionState());
    Serial.print("      Global State = "); Serial.println(version.state.getGlobalState());
    Serial.print("           Version = "); Serial.print(version.getIndoorOutdoorAndType()); Serial.print(F(" ")); Serial.print(version.getGridStandard()); Serial.print(F(" ")); Serial.print(version.getTrafoOrNonTrafo()); Serial.print(F(" ")); Serial.println(version.getWindOrPV());
    Serial.println("------------------------------------------");

    delay(4000);

}
