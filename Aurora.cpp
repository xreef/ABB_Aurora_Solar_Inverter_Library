#include "Aurora.h"

#ifdef ADD_SOFTWARE_SERIAL
Aurora::Aurora(byte inverterAddress, byte rxPin, byte txPin, byte serialCommunicationControlPin) {
    this->inverterAddress = inverterAddress;
    this->serialCommunicationControlPin = serialCommunicationControlPin;
    this->rxPin = rxPin;
    this->txPin = txPin;

    SoftwareSerial* mySerial = new SoftwareSerial((uint8_t)this->rxPin, (uint8_t)this->txPin); // "RX TX" // @suppress("Abstract class cannot be instantiated")
    this->ss = mySerial;

    sendStatus = false;
    receiveStatus = false;

    clearReceiveData();
}
#endif

Aurora::Aurora(byte inverterAddress, HardwareSerial* serial, byte serialCommunicationControlPin) {
    this->inverterAddress = inverterAddress;
    this->serialCommunicationControlPin = serialCommunicationControlPin;
    this->hs = serial;

    this->isSoftwareSerial = false;

    sendStatus = false;
    receiveStatus = false;

    clearReceiveData();
}

#ifdef ADD_SOFTWARE_SERIAL
Aurora::Aurora(byte inverterAddress, SoftwareSerial* serial, byte serialCommunicationControlPin) {
    this->inverterAddress = inverterAddress;
    this->serialCommunicationControlPin = serialCommunicationControlPin;
    this->ss = serial;

    sendStatus = false;
    receiveStatus = false;

    clearReceiveData();
}
#endif

void Aurora::begin(){

    pinMode(this->serialCommunicationControlPin, OUTPUT);
    digitalWrite(this->serialCommunicationControlPin, RS485_RX_PIN_VALUE);  // Init Transceiver

    DEBUG_PRINTLN("Begin ex");
    if (this->hs){
        DEBUG_PRINTLN("Begin Hardware Serial");

    	this->serialDef.begin(*this->hs, 19200);
	}
#ifdef ADD_SOFTWARE_SERIAL
    else if (this->ss){
        DEBUG_PRINTLN("Begin Software Serial");

		this->serialDef.begin(*this->ss, 19200);
	}	else{
        DEBUG_PRINTLN("Begin Software Serial Pin");
        SoftwareSerial* mySerial = new SoftwareSerial((int)this->rxPin, (int)this->txPin); // "RX TX" // @suppress("Abstract class cannot be instantiated")
        this->ss = mySerial;

//		SoftwareSerial mySerial(this->rxPin, this->txPin);
        DEBUG_PRINT("RX Pin: ");
        DEBUG_PRINT((int)this->rxPin);
        DEBUG_PRINT("TX Pin: ");
        DEBUG_PRINTLN((int)this->txPin);

		this->serialDef.begin(*this->ss, 19200);
	}
#endif
}

void Aurora::setInverterAddress(byte inverterAddress) {
    this->inverterAddress = inverterAddress;
}

byte Aurora::getInverterAddress() {
    return this->inverterAddress;
}

void Aurora::clearData(byte *data, byte len) {
    for (int i = 0; i < len; i++) {
        data[i] = 0;
    }
}

int Aurora::crc16(byte *data, int offset, int count)
{
    byte BccLo = 0xFF;
    byte BccHi = 0xFF;

    for (int i = offset; i < (offset + count); i++)
    {
        byte New = data[offset + i] ^ BccLo;
        byte Tmp = New << 4;
        New = Tmp ^ New;
        Tmp = New >> 5;
        BccLo = BccHi;
        BccHi = New ^ Tmp;
        Tmp = New << 3;
        BccLo = BccLo ^ Tmp;
        Tmp = New >> 4;
        BccLo = BccLo ^ Tmp;

    }

    return (int)word(~BccHi, ~BccLo);
}

bool Aurora::send(byte address, byte param0, byte param1, byte param2, byte param3, byte param4, byte param5, byte param6)
{

    sendStatus = false;
    receiveStatus = false;

    byte sendData[10];
    sendData[0] = address;
    sendData[1] = param0;
    sendData[2] = param1;
    sendData[3] = param2;
    sendData[4] = param3;
    sendData[5] = param4;
    sendData[6] = param5;
    sendData[7] = param6;

    int crc = crc16(sendData, 0, 8);
    sendData[8] = lowByte(crc);
    sendData[9] = highByte(crc);

    clearReceiveData();

    for (int i = 0; i < MAX_ATTEMP; i++)
    {
        digitalWrite(this->serialCommunicationControlPin, RS485_TX_PIN_VALUE);
        delay(50);

        DEBUG_PRINTLN("Start write");
        if (this->serialDef.stream->write(sendData, sizeof(sendData)) != 0) {

#ifdef ADD_SOFTWARE_SERIAL
        	if (this->isSoftwareSerial){
        		this->ss->listen();
        	}
#endif

        	DEBUG_PRINTLN("Start flush");
        	this->serialDef.stream->flush();
            sendStatus = true;

        	DEBUG_PRINTLN("Set RX PIN");

            digitalWrite(this->serialCommunicationControlPin, RS485_RX_PIN_VALUE);

            if (this->serialDef.stream->readBytes(receiveData, sizeof(receiveData)) != 0) {
            	DEBUG_PRINTLN("Start read");

                if ((int)word(receiveData[7], receiveData[6]) == crc16(receiveData, 0, 6)) {
                    receiveStatus = true;
                    break;
                }
            }
        }
    }
    return receiveStatus;
}


void Aurora::clearReceiveData() {
    clearData(receiveData, 8);
}

Aurora::DataState Aurora::readState() {
	DataState allState;

    allState.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_STATE, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (allState.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
        receiveData[2] = 255;
        receiveData[3] = 255;
        receiveData[4] = 255;
        receiveData[5] = 255;
    }

    allState.state.transmissionState = receiveData[0];
    allState.state.globalState = receiveData[1];
    allState.inverterState = receiveData[2];
    allState.channel1State = receiveData[3];
    allState.channel2State = receiveData[4];
    allState.alarmState = receiveData[5];

    return allState;
}

Aurora::DataVersion Aurora::readVersion() {
	DataVersion version;
    version.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_VERSION, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (version.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    version.state.transmissionState = receiveData[0];
    version.state.globalState = receiveData[1];

    version.par1 = (char)receiveData[aPar1];
    version.par2 = (char)receiveData[aPar2];
    version.par3 = (char)receiveData[aPar3];
    version.par4 = (char)receiveData[aPar4];

    return version;
}

Aurora::DataDSP Aurora::readDSP(byte type, byte global) {
	DataDSP DSP;
    if ((((int)type >= 1 && (int)type <= 9) || ((int)type >= 21 && (int)type <= 63)) && (/*(int)global >= 0 && */(int)global <= 1)) {
        DSP.state.readState = send(this->inverterAddress, (byte)COMMAND_DSP, type, global, (byte)0, (byte)0, (byte)0, (byte)0);

        if (DSP.state.readState == false) {
            receiveData[0] = 255;
            receiveData[1] = 255;
        }

    }
    else {
        DSP.state.readState = false;
        clearReceiveData();
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    DSP.state.transmissionState = receiveData[0];
    DSP.state.globalState = receiveData[1];

    foo.asBytes[0] = receiveData[5];
    foo.asBytes[1] = receiveData[4];
    foo.asBytes[2] = receiveData[3];
    foo.asBytes[3] = receiveData[2];

    DSP.value = foo.asFloat;

    return DSP;
}

Aurora::DataTimeDate Aurora::readTimeDate() {
	DataTimeDate timeDate;
    timeDate.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_TIMEDATE, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (timeDate.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    timeDate.state.transmissionState = receiveData[0];
    timeDate.state.globalState = receiveData[1];
    timeDate.seconds = ((unsigned long)receiveData[2] << 24) + ((unsigned long)receiveData[3] << 16) + ((unsigned long)receiveData[4] << 8) + (unsigned long)receiveData[5];
    timeDate.epochTime = timeDate.seconds+EPOCH_TO_START_TIME;
    return timeDate;
}

bool Aurora::writeTimeDate(unsigned long epochTime) {
	unsigned long timeInSecond = epochTime - EPOCH_TO_START_TIME;

    if (timeInSecond>0) {
    	byte sendingDateTime[4];
    	sendingDateTime[0] = (timeInSecond >> 24) & 0xff;
    	sendingDateTime[1] = (timeInSecond >> 16) & 0xff;
    	sendingDateTime[2] = (timeInSecond >> 8) & 0xff;
    	sendingDateTime[3] = timeInSecond & 0xff;

        return send(this->inverterAddress, (byte)COMMAND_SET_TIME_DATE, sendingDateTime[0], sendingDateTime[1], sendingDateTime[2], sendingDateTime[3], (byte)0, (byte)0);
    }
    else {
        clearReceiveData();
        return false;
    }
}


Aurora::DataLastFourAlarms Aurora::readLastFourAlarms() {
	DataLastFourAlarms lastFourAlarms;
    lastFourAlarms.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_LAST_4_ALARMS, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (lastFourAlarms.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
        receiveData[2] = 255;
        receiveData[3] = 255;
        receiveData[4] = 255;
        receiveData[5] = 255;
    }

    lastFourAlarms.state.transmissionState = receiveData[0];
    lastFourAlarms.state.globalState = receiveData[1];
    lastFourAlarms.alarm1 = receiveData[2];
    lastFourAlarms.alarm2 = receiveData[3];
    lastFourAlarms.alarm3 = receiveData[4];
    lastFourAlarms.alarm4 = receiveData[5];

    return lastFourAlarms;
}

Aurora::DataJunctionBoxState Aurora::readJunctionBoxState(byte nj) {
	DataJunctionBoxState dataJunctionBoxState;
    dataJunctionBoxState.state.readState = send(this->inverterAddress, (byte)200, nj, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
    if (dataJunctionBoxState.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
        receiveData[2] = 255;
        receiveData[3] = 255;
        receiveData[4] = 255;
        receiveData[5] = 255;
    }

    dataJunctionBoxState.state.transmissionState = receiveData[0];
    dataJunctionBoxState.state.globalState = -1;

    dataJunctionBoxState.jBoxState.burnFuseOnJBox 		= receiveData[1] & bit(0) ? true : false;
    dataJunctionBoxState.jBoxState.jBoxNotCalibrated 	= receiveData[1] & bit(7) ? true : false;
    dataJunctionBoxState.jBoxState.jBoxOvercurrent 		= receiveData[1] & bit(4) ? true : false;
    dataJunctionBoxState.jBoxState.jBoxOvertemperature 	= receiveData[1] & bit(1) ? true : false;
    dataJunctionBoxState.jBoxState.jBoxOvervoltage 		= receiveData[1] & bit(2) ? true : false;
    dataJunctionBoxState.jBoxState.noCommunication 		= receiveData[1] & bit(6) ? true : false;
    dataJunctionBoxState.jBoxState.powerOff 			= receiveData[1] & bit(5) ? true : false;
    dataJunctionBoxState.jBoxState.unbalancedStringCurrent = receiveData[1] & bit(3) ? true : false;

    dataJunctionBoxState.fuseBurnt[10] 	= receiveData[2] & bit(0) ? true : false;
    dataJunctionBoxState.fuseBurnt[20] 	= receiveData[2] & bit(1) ? true : false;
    dataJunctionBoxState.fuseBurnt[9] 	= receiveData[2] & bit(2) ? true : false;
    dataJunctionBoxState.fuseBurnt[19] 	= receiveData[2] & bit(3) ? true : false;
    dataJunctionBoxState.fuseBurnt[8] 	= receiveData[2] & bit(4) ? true : false;
    dataJunctionBoxState.fuseBurnt[18] 	= receiveData[2] & bit(5) ? true : false;
    dataJunctionBoxState.fuseBurnt[7] 	= receiveData[2] & bit(6) ? true : false;
    dataJunctionBoxState.fuseBurnt[17] 	= receiveData[2] & bit(7) ? true : false;

    dataJunctionBoxState.fuseBurnt[06] 	= receiveData[3] & bit(0) ? true : false;
    dataJunctionBoxState.fuseBurnt[16] 	= receiveData[3] & bit(1) ? true : false;
    dataJunctionBoxState.fuseBurnt[5] 	= receiveData[3] & bit(2) ? true : false;
    dataJunctionBoxState.fuseBurnt[15] 	= receiveData[3] & bit(3) ? true : false;
    dataJunctionBoxState.fuseBurnt[4] 	= receiveData[3] & bit(4) ? true : false;
    dataJunctionBoxState.fuseBurnt[14] 	= receiveData[3] & bit(5) ? true : false;
    dataJunctionBoxState.fuseBurnt[3] 	= receiveData[3] & bit(6) ? true : false;
    dataJunctionBoxState.fuseBurnt[13] 	= receiveData[3] & bit(7) ? true : false;

    dataJunctionBoxState.fuseBurnt[2] 	= receiveData[4] & bit(0) ? true : false;
    dataJunctionBoxState.fuseBurnt[12] 	= receiveData[4] & bit(1) ? true : false;
    dataJunctionBoxState.fuseBurnt[1] 	= receiveData[4] & bit(2) ? true : false;
    dataJunctionBoxState.fuseBurnt[1] 	= receiveData[4] & bit(3) ? true : false;

    dataJunctionBoxState.stringCurrentUnbalanced[9] 	= receiveData[4] & bit(6) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[8] 	= receiveData[4] & bit(7) ? true : false;

    dataJunctionBoxState.stringCurrentUnbalanced[7] 	= receiveData[5] & bit(0) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[6] 	= receiveData[5] & bit(1) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[5] 	= receiveData[5] & bit(2) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[4] 	= receiveData[5] & bit(3) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[3] 	= receiveData[5] & bit(4) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[2] 	= receiveData[5] & bit(5) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[1] 	= receiveData[5] & bit(6) ? true : false;
    dataJunctionBoxState.stringCurrentUnbalanced[0] 	= receiveData[5] & bit(7) ? true : false;

    return dataJunctionBoxState;
}

bool Aurora::readJunctionBoxVal(byte nj, byte par) {
    return send(this->inverterAddress, (byte)201, nj, par, (byte)0, (byte)0, (byte)0, (byte)0);
}

// Inverters

Aurora::DataSystemPN Aurora::readSystemPN() {
	DataSystemPN systemPN;
    systemPN.readState = send(this->inverterAddress, (byte)COMMAND_GET_PN, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    systemPN.PN = String(String((char)receiveData[0]) + String((char)receiveData[1]) + String((char)receiveData[2]) + String((char)receiveData[3]) + String((char)receiveData[4]) + String((char)receiveData[5]));

    return systemPN;
}

Aurora::DataSystemSerialNumber Aurora::readSystemSerialNumber() {
	DataSystemSerialNumber systemSerialNumber;
    systemSerialNumber.readState = send(this->inverterAddress, (byte)COMMAND_GET_SN, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    systemSerialNumber.SerialNumber = String(String((char)receiveData[0]) + String((char)receiveData[1]) + String((char)receiveData[2]) + String((char)receiveData[3]) + String((char)receiveData[4]) + String((char)receiveData[5]));

    return systemSerialNumber;
}

Aurora::DataManufacturingWeekYear Aurora::readManufacturingWeekYear() {
	DataManufacturingWeekYear manufacturingWeekYear;
    manufacturingWeekYear.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_MANUFACTURING_WEEK_YEAR, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (manufacturingWeekYear.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    manufacturingWeekYear.state.transmissionState = receiveData[0];
    manufacturingWeekYear.state.globalState = receiveData[1];
    manufacturingWeekYear.Week = String(String((char)receiveData[aWeekH]) + String((char)receiveData[aWeekL]));
    manufacturingWeekYear.Year = String(String((char)receiveData[aYearH]) + String((char)receiveData[aYearL]));

    return manufacturingWeekYear;
}

Aurora::DataFirmwareRelease Aurora::readFirmwareRelease() {
	DataFirmwareRelease firmwareRelease;
    firmwareRelease.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_FIRMWARE_RELEASE, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (firmwareRelease.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    firmwareRelease.state.transmissionState = receiveData[0];
    firmwareRelease.state.globalState = receiveData[1];
    firmwareRelease.release = String(String((char)receiveData[aRel3]) + "." + String((char)receiveData[aRel2]) + "." + String((char)receiveData[aRel1]) + "." + String((char)receiveData[aRel0]));

    return firmwareRelease;
}

Aurora::DataCumulatedEnergy Aurora::readCumulatedEnergy(byte par) {
	DataCumulatedEnergy cumulatedEnergy;
    if (/*(int)par >= 0 && */(int)par <= 6) {
        cumulatedEnergy.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_CUMULATED_ENERGY, par, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

        if (cumulatedEnergy.state.readState == false) {
            receiveData[0] = 255;
            receiveData[1] = 255;
        }

    }
    else {
        cumulatedEnergy.state.readState = false;
        clearReceiveData();
        receiveData[0] = 255;
        receiveData[1] = 255;
    }

    cumulatedEnergy.state.transmissionState = receiveData[0];
    cumulatedEnergy.state.globalState = receiveData[1];
    if (cumulatedEnergy.state.readState == true) {
        ulo.asBytes[0] = receiveData[5];
        ulo.asBytes[1] = receiveData[4];
        ulo.asBytes[2] = receiveData[3];
        ulo.asBytes[3] = receiveData[2];

        cumulatedEnergy.energy = ulo.asUlong;
    }
    return cumulatedEnergy;
}

bool Aurora::writeBaudRateSetting(byte baudcode) {
    if (/*(int)baudcode >= 0 && */(int)baudcode <= 3) {
        return send(this->inverterAddress, (byte)COMMAND_BAUD_RATE_SETTING_WRITE, baudcode, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
    }
    else {
        clearReceiveData();
        return false;
    }
}


Aurora::DataConfigStatus Aurora::readConfig() {
	DataConfigStatus configStatus;
	configStatus.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_CONFIG, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (configStatus.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
        receiveData[2] = 255;
    }

    configStatus.state.transmissionState = receiveData[0];
    configStatus.state.globalState = receiveData[1];
    configStatus.configStatus = receiveData[aConfCode];

    return configStatus;

}

Aurora::DataTimeCounter Aurora::readTimeCounter(byte param) {
	DataTimeCounter timeCounter;
	timeCounter.state.readState = send(this->inverterAddress, (byte)COMMAND_GET_TIME_COUNTER, param, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (timeCounter.state.readState == false) {
        receiveData[0] = 255;
        receiveData[1] = 255;
        receiveData[2] = 0;
        receiveData[3] = 0;
        receiveData[4] = 0;
        receiveData[5] = 0;
    }

    timeCounter.state.transmissionState = receiveData[0];
    timeCounter.state.globalState = receiveData[1];
    timeCounter.upTimeInSec = ((unsigned long)receiveData[2] << 24) + ((unsigned long)receiveData[3] << 16) + ((unsigned long)receiveData[4] << 8) + (unsigned long)receiveData[5];

    return timeCounter;

}

// Central
bool Aurora::readFlagsSwitchCentral() {
    return send(this->inverterAddress, (byte)67, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool Aurora::readCumulatedEnergyCentral(byte var, byte ndays_h, byte ndays_l, byte global) {
    return send(this->inverterAddress, (byte)68, var, ndays_h, ndays_l, global, (byte)0, (byte)0);
}

bool Aurora::readFirmwareReleaseCentral(byte var) {
    return send(this->inverterAddress, (byte)72, var, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool Aurora::readBaudRateSettingCentral(byte baudcode, byte serialline) {
    return send(this->inverterAddress, (byte)85, baudcode, serialline, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool Aurora::readSystemInfoCentral(byte var) {
    return send(this->inverterAddress, (byte)101, var, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool Aurora::readJunctionBoxMonitoringCentral(byte cf, byte rn, byte njt, byte jal, byte jah) {
    return send(this->inverterAddress, (byte)103, cf, rn, njt, jal, jah, (byte)0);
}

bool Aurora::readSystemPNCentral() {
    return send(this->inverterAddress, (byte)105, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool Aurora::readSystemSerialNumberCentral() {
    return send(this->inverterAddress, (byte)107, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

