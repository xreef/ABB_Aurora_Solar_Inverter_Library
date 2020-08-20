#include <ABBAurora.h>
#include <Thread.h>
#include <Wire.h> 
#include <TimeLib.h>
#include <SoftwareSerial.h>

SoftwareSerial serDebug(10, 11); // RX, TX

void serDebugPrintData(byte *data) {
  for (int i = 0; i < 8; i++) {
    serDebug.print((int)data[i]);
    serDebug.print(F(" "));
  }
  serDebug.println(F(" "));
}

class clsBottone {
private:
  int Pin;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 250;
  byte buttonState = 0;
  byte lastButtonState = 0;
  byte State = 0;

public:
  clsBottone(int _Pin) {
    Pin = _Pin;
    pinMode(Pin, INPUT_PULLUP);
  }

  byte Stato() {
    byte ret = State;
    State = 0;
    return  ret;
  }

  void Aggiorna() {
    unsigned long currentTime = millis();
    byte reading = 0;

    switch (digitalRead(Pin)) {
    case 0:  // SWx
      reading = 1;
      break;
    default:
      reading = 0;
      break;
    }

    if (reading != lastButtonState) {
      lastButtonState = reading;
      lastDebounceTime = currentTime;
    }
    else if ((currentTime - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        State = reading;
      }
    }
  }
};

ABBAurora Inverter2 = ABBAurora(2);
ABBAurora Inverter7 = ABBAurora(7);

volatile double Irms = 0;
byte Menu = 0;

Thread LeggiConsumi = Thread();
Thread LeggiProduzione = Thread();
Thread ScriviDebug = Thread();

clsBottone Bottone = clsBottone(8);

String stampaDataTime(unsigned long scn)
{
  String rtn;

  if (scn > 0) {
    setTime(0, 0, 0, 1, 1, 2000);
    if (timeStatus() == timeSet) {
    adjustTime(scn);

      rtn = String(day());
      rtn += String(F("/"));
      rtn += String(month());
      rtn += String(F("/"));
      rtn += String(year());
      rtn += String(F(" "));
      rtn += String(hour());
      rtn += String(F(":"));
      rtn += String(minute());
      rtn += String(F(":"));
      rtn += String(second());
    }
  }

  return rtn;
}

void LeggiConsumiCallback() {
//  Irms = emon1.calcIrms(1480);
}

void LeggiProduzioneCallback() {
  switch (Menu)
  {
  case 0:
    Inverter2.ReadCumulatedEnergy(0);
    Inverter7.ReadCumulatedEnergy(0);
    break;
  case 1:
    Inverter2.ReadTimeDate();
    Inverter7.ReadTimeDate();
    break;
  case 2:
    Inverter2.ReadLastFourAlarms();
    Inverter7.ReadLastFourAlarms();
    break;
  case 3:
    Inverter2.ReadSystemPN();
    Inverter7.ReadSystemPN();
    break;
  case 4:
    Inverter2.ReadSystemSerialNumber();
    Inverter7.ReadSystemSerialNumber();
    break;
  case 5:
    Inverter2.ReadManufacturingWeekYear();
    Inverter7.ReadManufacturingWeekYear();
    break;
  case 6:
    Inverter2.ReadFirmwareRelease();
    Inverter7.ReadFirmwareRelease();
    break;
  case 7:
    Inverter2.ReadVersion();
    Inverter7.ReadVersion();
    break;
  case 8:
    Inverter2.ReadState();
    Inverter7.ReadState();
    break;
  default:
    break;
  }
}

void clearTerm() {
  serDebug.write(27); serDebug.print("[2J");
  serDebug.write(27); serDebug.print("[;H");
  serDebug.write(27); serDebug.print("[0;40;37m");
}

void clearRow() {
  serDebug.write(27); serDebug.print("[K");
}

void ScriviDebugCallback() {
  serDebug.write(27); serDebug.print("[;H");
  serDebug.println("------------------------------------------");
  serDebug.print("MENU = "); clearRow(); serDebug.println(Menu);
  serDebug.println("------------------------------------------");

  switch (Menu)
  {
  case 0:
    serDebug.println("CONSUMI");
    serDebug.print("IRMS = "); clearRow(); serDebug.println(Irms, 10);
    serDebug.print("   W = "); clearRow(); serDebug.println(Irms * 230, 1);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.CumulatedEnergy.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.CumulatedEnergy.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.CumulatedEnergy.GlobalState));
    serDebug.print("           Energia = "); clearRow(); serDebug.print(Inverter2.CumulatedEnergy.Energia); serDebug.println(" Wh");
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.CumulatedEnergy.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.CumulatedEnergy.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.CumulatedEnergy.GlobalState));
    serDebug.print("           Energia = "); clearRow(); serDebug.print(Inverter7.CumulatedEnergy.Energia); serDebug.println(" Wh");
    serDebug.println("------------------------------------------");
    break;
  case 1:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.TimeDate.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.TimeDate.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.TimeDate.GlobalState));
    serDebug.print("           Secondi = "); clearRow(); serDebug.println(Inverter2.TimeDate.Secondi);
    serDebug.print("         Data/Time = "); clearRow(); serDebug.println(stampaDataTime(Inverter2.TimeDate.Secondi));
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.TimeDate.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.TimeDate.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.TimeDate.GlobalState));
    serDebug.print("           Secondi = "); clearRow(); serDebug.println(Inverter7.TimeDate.Secondi);
    serDebug.print("         Data/Time = "); clearRow(); serDebug.println(stampaDataTime(Inverter7.TimeDate.Secondi));
    serDebug.println("------------------------------------------");
    break;
  case 2:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.LastFourAlarms.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.LastFourAlarms.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.LastFourAlarms.GlobalState));
    serDebug.print("          Alarms 1 = "); clearRow(); serDebug.println(Inverter2.AlarmState(Inverter2.LastFourAlarms.Alarms1));
    serDebug.print("          Alarms 2 = "); clearRow(); serDebug.println(Inverter2.AlarmState(Inverter2.LastFourAlarms.Alarms2));
    serDebug.print("          Alarms 3 = "); clearRow(); serDebug.println(Inverter2.AlarmState(Inverter2.LastFourAlarms.Alarms3));
    serDebug.print("          Alarms 4 = "); clearRow(); serDebug.println(Inverter2.AlarmState(Inverter2.LastFourAlarms.Alarms4));
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.LastFourAlarms.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.LastFourAlarms.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.LastFourAlarms.GlobalState));
    serDebug.print("          Alarms 1 = "); clearRow(); serDebug.println(Inverter7.AlarmState(Inverter7.LastFourAlarms.Alarms1));
    serDebug.print("          Alarms 2 = "); clearRow(); serDebug.println(Inverter7.AlarmState(Inverter7.LastFourAlarms.Alarms2));
    serDebug.print("          Alarms 3 = "); clearRow(); serDebug.println(Inverter7.AlarmState(Inverter7.LastFourAlarms.Alarms3));
    serDebug.print("          Alarms 4 = "); clearRow(); serDebug.println(Inverter7.AlarmState(Inverter7.LastFourAlarms.Alarms4));
    serDebug.println("------------------------------------------");
    break;
  case 3:
    serDebug.println("INVERTER 2");
    serDebug.print("  Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("Read State = "); clearRow(); serDebug.println(Inverter2.SystemPN.ReadState);
    serDebug.print("       P/N = "); clearRow(); serDebug.println(Inverter2.SystemPN.PN);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("  Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("Read State = "); clearRow(); serDebug.println(Inverter7.SystemPN.ReadState);
    serDebug.print("       P/N = "); clearRow(); serDebug.println(Inverter7.SystemPN.PN);
    serDebug.println("------------------------------------------");
    break;
  case 4:
    serDebug.println("INVERTER 2");
    serDebug.print("     Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("   Read State = "); clearRow(); serDebug.println(Inverter2.SystemSerialNumber.ReadState);
    serDebug.print("Serial Number = "); clearRow(); serDebug.println(Inverter2.SystemSerialNumber.SerialNumber);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("     Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("   Read State = "); clearRow(); serDebug.println(Inverter7.SystemSerialNumber.ReadState);
    serDebug.print("Serial Number = "); clearRow(); serDebug.println(Inverter7.SystemSerialNumber.SerialNumber);
    serDebug.println("------------------------------------------");
    break;
  case 5:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.ManufacturingWeekYear.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.ManufacturingWeekYear.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.ManufacturingWeekYear.GlobalState));
    serDebug.print("              Week = "); clearRow(); serDebug.println(Inverter2.ManufacturingWeekYear.Week);
    serDebug.print("              Year = "); clearRow(); serDebug.println(Inverter2.ManufacturingWeekYear.Year);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.ManufacturingWeekYear.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.ManufacturingWeekYear.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.ManufacturingWeekYear.GlobalState));
    serDebug.print("              Week = "); clearRow(); serDebug.println(Inverter7.ManufacturingWeekYear.Week);
    serDebug.print("              Year = "); clearRow(); serDebug.println(Inverter7.ManufacturingWeekYear.Year);
    serDebug.println("------------------------------------------");
    break;
  case 6:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.FirmwareRelease.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.FirmwareRelease.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.FirmwareRelease.GlobalState));
    serDebug.print("  Firmware Release = "); clearRow(); serDebug.println(Inverter2.FirmwareRelease.Release);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.FirmwareRelease.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.FirmwareRelease.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.FirmwareRelease.GlobalState));
    serDebug.print("  Firmware Release = "); clearRow(); serDebug.println(Inverter7.FirmwareRelease.Release);
    serDebug.println("------------------------------------------");
    break;
  case 7:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.Version.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.Version.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.Version.GlobalState));
    serDebug.print("           Version = "); clearRow(); serDebug.print(Inverter2.Version.Par1); serDebug.print(F(" ")); serDebug.print(Inverter2.Version.Par2); serDebug.print(F(" ")); serDebug.print(Inverter2.Version.Par3); serDebug.print(F(" ")); serDebug.println(Inverter2.Version.Par4);
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.Version.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.Version.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.Version.GlobalState));
    serDebug.print("           Version = "); clearRow(); serDebug.print(Inverter7.Version.Par1); serDebug.print(F(" ")); serDebug.print(Inverter7.Version.Par2); serDebug.print(F(" ")); serDebug.print(Inverter7.Version.Par3); serDebug.print(F(" ")); serDebug.println(Inverter7.Version.Par4);
    serDebug.println("------------------------------------------");
    break;
  case 8:
    serDebug.println("INVERTER 2");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter2.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter2.State.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter2.TransmissionState(Inverter2.State.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter2.GlobalState(Inverter2.State.GlobalState));
    serDebug.print("          Inverter = "); clearRow(); serDebug.println(Inverter2.InverterState(Inverter2.State.InverterState));
    serDebug.print("         Channel 1 = "); clearRow(); serDebug.println(Inverter2.DcDcState(Inverter2.State.Channel1State));
    serDebug.print("         Channel 2 = "); clearRow(); serDebug.println(Inverter2.DcDcState(Inverter2.State.Channel2State));
    serDebug.print("             Alarm = "); clearRow(); serDebug.println(Inverter2.AlarmState(Inverter2.State.AlarmState));
    serDebug.println("------------------------------------------");
    serDebug.println("INVERTER 7");
    serDebug.print("          Data ROW = "); clearRow(); serDebugPrintData(Inverter7.ReceiveData);
    serDebug.print("        Read State = "); clearRow(); serDebug.println(Inverter7.State.ReadState);
    serDebug.print("Transmission State = "); clearRow(); serDebug.println(Inverter7.TransmissionState(Inverter7.State.TransmissionState));
    serDebug.print("      Global State = "); clearRow(); serDebug.println(Inverter7.GlobalState(Inverter7.State.GlobalState));
    serDebug.print("          Inverter = "); clearRow(); serDebug.println(Inverter7.InverterState(Inverter7.State.InverterState));
    serDebug.print("         Channel 1 = "); clearRow(); serDebug.println(Inverter7.DcDcState(Inverter7.State.Channel1State));
    serDebug.print("         Channel 2 = "); clearRow(); serDebug.println(Inverter7.DcDcState(Inverter7.State.Channel2State));
    serDebug.print("             Alarm = "); clearRow(); serDebug.println(Inverter7.AlarmState(Inverter7.State.AlarmState));
    serDebug.println("------------------------------------------");
    break;
  default:
    break;
  }
}

void setup()
{
  serDebug.begin(19200);
  clearTerm();
  serDebug.println("------------------------------------------");
  serDebug.println("               AVVIO");
  serDebug.println("------------------------------------------");

//  emon1.current(0, 16.0); // DA REGOLARE

  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver   

  Serial.setTimeout(500);
  Serial.begin(19200);

  LeggiConsumi.onRun(LeggiConsumiCallback);
  LeggiConsumi.setInterval(500);

  LeggiProduzione.onRun(LeggiProduzioneCallback);
  LeggiProduzione.setInterval(500);

  ScriviDebug.onRun(ScriviDebugCallback);
  ScriviDebug.setInterval(500);

}

void loop()
{

  Bottone.Aggiorna();

  switch (Bottone.Stato())
  {
  case 1:
    Menu++;
    clearTerm();
    break;
  /*case 2:
    Menu--;
    clearTerm();
    break;
  case 3:
    Menu = 0;
    clearTerm();
    break;
    */
  }

  if (LeggiConsumi.shouldRun()) {
    LeggiConsumi.run();
  }
  if (LeggiProduzione.shouldRun()) {
    LeggiProduzione.run();
  }
  if (ScriviDebug.shouldRun()) {
    ScriviDebug.run();
  }
}
