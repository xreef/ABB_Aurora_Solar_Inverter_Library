ABB Aurora protocol
-------------------

Here the base information of RS485 ABB Aurora communication Protocol.

![ABB PowerOne Aurora communication protocol Library arduino esp8266 esp32 Main](https://www.mischianti.org/wp-content/uploads/2020/08/ABB-PowerOne-Aurora-communication-protocol-Library-arduino-esp8266-esp32-Main.jpg)

ABB PowerOne Aurora communication protocol Library arduino esp8266 esp32 Main

The communication between Host and processor works via a Serial Interface RS485 or RS232.
 Configuration parameters in both cases are:

-   19200 baud (default value)
-   1 stop bit
-   no parity

The communication protocol uses fixed length transmission messages (8Bytes + 2Bytes for Checksum) structured as follows:

||
|0|1|2|3|4|5|6|7|8|9|
|Address|Command|B2|B3|B4|B5|B6|B7|CRC\_L|CRC\_H|

The structure of the answer has also fixed length (6 Bytes + 2 Bytes for Checksum) :

||
|0|1|2|3|4|5|6|7|
|Transmission State|Global State|B2|B3|B4|B5|CRC\_L|CRC\_H|

**Transmission State** is coded as follows:

0 = Everything is OK.
51 = Command is not implemented
52 = Variable does not exist
53 = Variable value is out of range
54 = EEprom not accessible
55 = Not Toggled Service Mode
56 = Can not send the command to internal micro
57 = Command not Executed
58 = The variable is not available, retry

[![](https://www.mischianti.org/wp-content/uploads/2020/05/pcbWay-banner-mobile-300x200-1.gif)](https://www.pcbway.com/?from=mischianti05)

**Global State** shows the state of the addressed device, the details are specified in the description of the commands.

Arduino UNO and MAX485
----------------------

You can use an Arduino UNO and a MAX485 IC, if you prefer can buy a module.

You can find IC on [AliExpress](https://s.click.aliexpress.com/e/_d6o7wph)

You can find module on [AliExpress](https://s.click.aliexpress.com/e/_dYTw9rD)

You can ArduinoUNO on [AliExpress](http://s.click.aliexpress.com/e/bilC7QEk)

Here the simple connection schema, the resistor must be 120Ω, i use 104Ω.

![](https://www.mischianti.org/wp-content/uploads/2019/05/ArduinoConnectionSchema_bb-1024x720.jpg)

MAX485 Arduino connection schema

I create a library derived from a project that you can find in the web created by [drhack](http://www.drhack.it/arduino/32-lettura-inverte-power-one-aurora.html), It’s a fantastic works (thanks to drhack) but I find It quite difficult to use, with specific hardware and not so reusable.

So I try to standardize the library and made It simple (the people that use my library know that “simplify first” It’s my motto.

esp8266 and MAX3485
-------------------

If you want use an esp8266 (I create a centraline with Wemos D1 mini) you must buy a MAX3485 tha work at the correct voltage.

You can find IC on [AliExpress](https://s.click.aliexpress.com/e/_d8ENRNN) [eBay](https://rover.ebay.com/rover/1/711-53200-19255-0/1?icep_id=114&ipn=icep&toolid=20004&campid=5338536765&mpre=https%3A%2F%2Fwww.ebay.com%2Fitm%2F5-PCS-MAX3485CPA-DIP-8-MAX3485-3-3V-Powered-Transceiver%2F302191492920%3Fhash%3Ditem465c043f38%3Ag%3A5DYAAOSwk1JWfXIY)

You can find module on [AliExpress](https://s.click.aliexpress.com/e/_d8vTejl) [eBay](https://rover.ebay.com/rover/1/711-53200-19255-0/1?icep_id=114&ipn=icep&toolid=20004&campid=5338536765&mpre=https%3A%2F%2Fwww.ebay.com%2Fitm%2FMAX3485-TTL-To-RS485-Module-MCU-Development-Converter-Module-Board-Accessories%2F382910038180%3Fhash%3Ditem59273780a4%3Ag%3A8aIAAOSwY7lcufQE%26frcectupt%3Dtrue)

You can find WeMos D1 mini on [AliExpress](http://s.click.aliexpress.com/e/ct2C48ti)

Here the simple connection schema, the resistor must be 120Ω, i use 104Ω.

![](https://www.mischianti.org/wp-content/uploads/2019/05/espConnectionSchemaClean_bb-1024x726.jpg)

MAX3485 and esp8266 connection schema

As you can see It’s quite simple to connect.

Library
-------

You can find my library here.

**To download.**

-   Click the DOWNLOADS button in the top right corner, rename the uncompressed folder Arduino\_ABB\_PowerOne\_Aurora\_communication\_protocol.
-   Check that the Arduino\_ABB\_PowerOne\_Aurora\_communication\_protocol folder contains Aurora.cpp and Aurora.h.
-   Place the Arduino\_ABB\_PowerOne\_Aurora\_communication\_protocol library folder your /libraries/ folder.
-   You may need to create the libraries subfolder if its your first library.
-   Restart the IDE.

List of commands It’s quite big, so I’m going to explain all.

### Constructor

As usual I try to create It more generic as possible, so If you want use `HardwareSerial `or `SoftwareSerial `you are free to choiche.

As you can see in the packet description

||
|0|1|2|3|4|5|6|7|8|9|
|**Address**|Command|B2|B3|B4|B5|B6|B7|CRC\_L|CRC\_H|

you must specify an address, that address normally is 2, but you must check It in your inverter menu.

You can create a **chain of inverters** that communicate via RS485. An address can be chosen from 2 to 63. The address on the inverter is set through the display and the pushbutton panel.

To change address go to `SETTINGS --> Insert password (default 0000) --> Address`.

This menu allows you to set the serial port addresses of the individual inverters connected to the RS485 line.
 The addresses that can be assigned are 2 to 63. The UP and DOWN buttons scroll through the numerical scale. ‘AUTO’ selection cannot be used at present.

#### HardwareSerial

<table>
<col width="50%" />
<col width="50%" />
<tbody>
<tr class="odd">
<td align="left">1
2</td>
<td align="left"><code class="cpp comments">// Aurora(byte inverterAddress, HardwareSerial* serial, byte serialCommunicationControlPin)</code>
<code class="cpp plain">Aurora inverter = Aurora(2, &amp;amp;Serial, 5);</code></td>
</tr>
</tbody>
</table>

-   `inverterAddress`: as described is the inverter address set on device.
-   `serial`: is the `HardwareSerial`.
-   `serialCommunicationControlPin`: is the pin that activate transmission of serial communication.

#### SoftwareSerial

<table>
<col width="50%" />
<col width="50%" />
<tbody>
<tr class="odd">
<td align="left">1
2</td>
<td align="left"><code class="cpp comments">// Aurora(byte inverterAddress, byte rxPin, byte txPin, byte serialCommunicationControlPin)</code>
<code class="cpp plain">Aurora inverter = Aurora(2, 10, 11, 5);</code></td>
</tr>
</tbody>
</table>

-   `inverterAddress`: as described is the inverter address set on device.
-   `rxPin: `is the SoftwareSerial RX pin.
-   `txPin: `is the SoftwareSerial TX pin.
-   `serialCommunicationControlPin`: is the pin that activate transmission of serial communication.

For software serial you can pass external SoftwareSerial instance.

||
|1|`// Aurora(byte inverterAddress, SoftwareSerial* serial, byte serialCommunicationControlPin) `|

#### Usage

First you must startup the communication with `begin` command:

||
|1|`inverter.begin();`|

Than there are a lot of command that you can use to make query to your Inverter:


Example code
------------

Here an example of reading via Arduino.

```cpp
/*
 Test Arduino MAX485 Aurora ABB connection
 by Mischianti Renzo <https://www.mischianti.org>
 
 https://www.mischianti.org/
*/
 
#include "Arduino.h"
#include <Aurora.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>
 
//SoftwareSerial mySerial(10, 11); // RX, TX
//Aurora inverter = Aurora(2, &amp;Serial1, 5);
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
    Serial.print(F("freeMemory(1)="));Serial.println(freeMemory());
 
    Aurora::DataCumulatedEnergy cumulatedEnergy = inverter.readCumulatedEnergy((byte)1);
    Serial.println(F("------------------------------------------"));
    Serial.println(F("INVERTER 2"));
    Serial.print(F("          Data ROW = ")); SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = ")); Serial.println(cumulatedEnergy.state.readState);
    Serial.print(F("Transmission State = ")); Serial.println(cumulatedEnergy.state.getTransmissionState());
    Serial.print(F("      Global State = ")); Serial.println(cumulatedEnergy.state.getGlobalState());
    Serial.print(F("           Energia = ")); Serial.print(cumulatedEnergy.energy); Serial.println(" Wh");
//    free(&amp;cumulatedEnergy);
    Serial.println(F("------------------------------------------"));
 
 
    Aurora::DataLastFourAlarms lastFour = inverter.readLastFourAlarms();
 
    Serial.println(F("INVERTER 2"));
    Serial.print(F("          Data ROW = "));  SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = "));  Serial.println(lastFour.state.readState);
    Serial.print(F("Transmission State = "));  Serial.println(lastFour.state.getTransmissionState());
    Serial.print(F("      Global State = "));  Serial.println(lastFour.state.getGlobalState());
    Serial.print(F("          Alarms 1 = "));  Serial.println(lastFour.getAlarm1State());
    Serial.print(F("          Alarms 2 = "));  Serial.println(lastFour.getAlarm2State());
    Serial.print(F("          Alarms 3 = "));  Serial.println(lastFour.getAlarm3State());
    Serial.print(F("          Alarms 4 = "));  Serial.println(lastFour.getAlarm4State());
//  free(&amp;lastFour);
 
    Serial.println(F("------------------------------------------"));
 
    Aurora::DataVersion version = inverter.readVersion();
    Serial.println("INVERTER 2");
    Serial.print(F("          Data ROW = ")); SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = ")); Serial.println(version.state.readState);
    Serial.print(F("Transmission State = ")); Serial.println(version.state.getTransmissionState());
    Serial.print(F("      Global State = ")); Serial.println(version.state.getGlobalState());
    Serial.print(F("           Version = ")); Serial.print(version.getModelName().name); Serial.print(F(" ")); Serial.print(version.getIndoorOutdoorAndType()); Serial.print(F(" ")); Serial.print(version.getGridStandard()); Serial.print(F(" ")); Serial.print(version.getTrafoOrNonTrafo()); Serial.print(F(" ")); Serial.println(version.getWindOrPV());
    Serial.println(F("------------------------------------------"));
//  free(&amp;version);
 
    Aurora::DataConfigStatus configStatus = inverter.readConfig();
 
    Serial.print(F("          Data ROW = ")); SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = ")); Serial.println(configStatus.state.readState);
    Serial.print(F("Transmission State = ")); Serial.println(configStatus.state.getTransmissionState());
    Serial.print(F("      Global State = ")); Serial.println(configStatus.state.getGlobalState());
    Serial.print(F("      config       = ")); Serial.println(configStatus.getConfigStatus());
    Serial.println(F("------------------------------------------"));
//  free(&amp;version);
    Serial.print(F("freeMemory(2)="));Serial.println(freeMemory());
 
    Aurora::DataTimeCounter timeCounter = inverter.readTimeCounter(CT_TOTAL_RUN);
 
    Serial.print(F("          Data ROW = ")); SerialPrintData(inverter.receiveData);
    Serial.print(F("        Read State = ")); Serial.println(timeCounter.state.readState);
    Serial.print(F("Transmission State = ")); Serial.println(timeCounter.state.getTransmissionState());
    Serial.print(F("      Global State = ")); Serial.println(timeCounter.state.getGlobalState());
    Serial.print(F("      time in sec  = ")); Serial.println(timeCounter.upTimeInSec);
    Serial.print(F("      time in verb  = ")); Serial.print(timeCounter.getSecondsInDateElements()[0]); Serial.print(F("Y ")); Serial.print(timeCounter.getSecondsInDateElements()[1]); Serial.print(F("D "));Serial.print(timeCounter.getSecondsInDateElements()[2]);Serial.print(F("H "));Serial.print(timeCounter.getSecondsInDateElements()[3]);+Serial.print(F("M "));Serial.print(timeCounter.getSecondsInDateElements()[4]);Serial.println(F("S "));
    Serial.println(F("------------------------------------------"));
//  free(&amp;version);
    Serial.print(F("freeMemory(2)="));Serial.println(freeMemory());
 
    delay(4000);
 
}
```

As you can see the usage is quite simple.

Here the video of the result call.

https://youtu.be/KK6nUxzuNPs

Thanks
------
