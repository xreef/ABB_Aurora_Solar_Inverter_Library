#ifndef Aurora_h
#define Aurora_h
#include <Arduino.h>

#define ADD_SOFTWARE_SERIAL

#ifdef ADD_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif

#include <Wire.h> 
#include <include/names.h>
#include <include/statesNaming.h>
#include <include/utils.h>

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

//#define AURORA_CP_DEBUG

// Setup debug printing macros.
#ifdef AURORA_CP_DEBUG
	#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
	#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
	#define DEBUG_PRINT(...) {}
	#define DEBUG_PRINTLN(...) {}
#endif

//RS485 control
#define SERIAL_COMMUNICATION_CONTROL_PIN 5
#define RS485_TX_PIN_VALUE HIGH
#define RS485_RX_PIN_VALUE LOW

#define MAX_ATTEMP 1

class Aurora {
    private:
		HardwareSerial* hs;
#ifdef ADD_SOFTWARE_SERIAL
		SoftwareSerial* ss;
#endif

		bool isSoftwareSerial = true;

		struct NeedsStream{

		  template< typename T >
		  void begin( T &t, int baud ){
			  DEBUG_PRINTLN("Begin ");
			  t.setTimeout(500);
			  t.begin(baud);
			  stream = &t;
		  }

		  void listen(){

		  }


		  Stream *stream;
		};

		NeedsStream serialDef;

        byte inverterAddress = 0;
        byte serialCommunicationControlPin;

        byte rxPin;
        byte txPin;

        void clearData(byte *data, byte len);
        int crc16(byte *data, int offset, int count);

        bool send(byte address, byte param0, byte param1, byte param2, byte param3, byte param4, byte param5, byte param6);

        union {
            byte asBytes[4];
            float asFloat;
        } foo;

        union {
            byte asBytes[4];
            unsigned long asUlong;
        } ulo;

        String _getAlarmState(byte id);

    public:
        bool sendStatus = false;
        bool receiveStatus = false;
        byte receiveData[8];

#ifdef ADD_SOFTWARE_SERIAL
        Aurora(byte inverterAddress, byte rxPin, byte txPin, byte serialCommunicationControlPin = SERIAL_COMMUNICATION_CONTROL_PIN);
#endif
        Aurora(byte inverterAddress, HardwareSerial* serial = &Serial, byte serialCommunicationControlPin = SERIAL_COMMUNICATION_CONTROL_PIN);
#ifdef ADD_SOFTWARE_SERIAL
        Aurora(byte inverterAddress, SoftwareSerial* serial, byte serialCommunicationControlPin = SERIAL_COMMUNICATION_CONTROL_PIN);
#endif

        void begin();

        void setInverterAddress(byte);
        byte getInverterAddress();

        void clearReceiveData();

        typedef struct {
			byte transmissionState;
			byte globalState;
			bool readState;


			String getTransmissionState() {
				return getTransmissionStateByParams(this->transmissionState);
			}

			String getGlobalState() {
				return getGlobalStateByParams(this->globalState);
			}
		} OutcomeState;

        typedef struct {
            byte inverterState;
            byte channel1State;
            byte channel2State;
            byte alarmState;

            const String getDcDcChannel1State(){
            	return getDcDcStateByParams(this->channel1State);
            }
            const String getDcDcChannel2State(){
            	return getDcDcStateByParams(this->channel2State);
            }

            const String getInverterState() {
            	return getInverterStateByParams(this->inverterState);
            }

            const String getAlarmState() {
                return getAlarmDescription(this->alarmState);
            }

            OutcomeState state;
        } DataState;

        DataState readState();

        typedef struct {
            char par1;
            char par2;
            char par3;
            char par4;

            InverterModel getModelName(){
            	return getModelNameByParams(this->par1);
            }

            const String getIndoorOutdoorAndType(){
            	return getIndoorOutdoorAndTypeByParams(this->par1);
            }

            const String getGridStandard(){
            	return getGridStandardByParams(this->par2);
            }

            const String getGridStandardInt(){
            	return getGridStandardByParams(this->par2);
            }

            const String getTrafoOrNonTrafo(){
            	return getTrafoOrNonTrafoByParams(this->par3);
            }

            const String getWindOrPV(){
            	return getWindOrPVByParams(this->par4);
            }

            OutcomeState state;
        } DataVersion;

        DataVersion readVersion();

        typedef struct {
            float value;
            OutcomeState state;
        } DataDSP;

        DataDSP readDSP(byte type, byte global = (byte)1);

        typedef struct {
            unsigned long seconds;
            unsigned long epochTime;
            String getDateTimeString(){
            	return getEpochStringByParams(this->epochTime);
            }
            tm getDateTime(){
            	return getDateTimeByParams(this->epochTime);
            }
            OutcomeState state;
        } DataTimeDate;

        DataTimeDate readTimeDate();

        bool writeTimeDate(unsigned long epochTime);

        typedef struct {
        	byte alarm1;
        	byte alarm2;
        	byte alarm3;
        	byte alarm4;

            String getAlarm1State() {
                return getAlarmDescription(this->alarm1);
            }
            String getAlarm2State() {
                return getAlarmDescription(this->alarm2);
            }
            String getAlarm3State() {
                return getAlarmDescription(this->alarm3);
            }
            String getAlarm4State() {
                return getAlarmDescription(this->alarm4);
            }


            OutcomeState state;
        } DataLastFourAlarms;

        DataLastFourAlarms readLastFourAlarms();

        typedef struct {
        	bool burnFuseOnJBox;
        	bool jBoxOvertemperature;
        	bool jBoxOvervoltage;
        	bool unbalancedStringCurrent;
        	bool jBoxOvercurrent;
        	bool powerOff;
        	bool noCommunication;
        	bool jBoxNotCalibrated;
        } JBoxState;

        typedef struct {
        	JBoxState jBoxState;
        	bool fuseBurnt[21] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
        	bool stringCurrentUnbalanced[11] = {false,false,false,false,false,false,false,false,false,false,false} ;
            OutcomeState state;

        } DataJunctionBoxState;
        DataJunctionBoxState readJunctionBoxState(byte nj);

        bool readJunctionBoxVal(byte nj, byte par);

        // Inverters
        typedef struct {
            String PN;
            bool readState;
        } DataSystemPN;

        DataSystemPN readSystemPN();

        typedef struct {
            String SerialNumber;
            bool readState;
        } DataSystemSerialNumber;

        DataSystemSerialNumber readSystemSerialNumber();

        typedef struct {
            String Week;
            String Year;
            OutcomeState state;
        } DataManufacturingWeekYear;

        DataManufacturingWeekYear readManufacturingWeekYear();

        typedef struct {
            String release;
            OutcomeState state;
        } DataFirmwareRelease;

        DataFirmwareRelease readFirmwareRelease();

        typedef struct {
            unsigned long energy;
            OutcomeState state;
        } DataCumulatedEnergy;

        DataCumulatedEnergy readCumulatedEnergy(byte par);

        bool writeBaudRateSetting(byte baudcode);

        typedef struct {
        	byte configStatus;
        	String getConfigStatus() {
				return getConfigFlagByParams(this->configStatus);
			}
        	OutcomeState state;
        } DataConfigStatus;

        DataConfigStatus readConfig();

        typedef struct {
        	unsigned long upTimeInSec;
        	int * getSecondsInDateElements() {
        		return getSecondsInDateElementsByParams(this->upTimeInSec);
			}
        	OutcomeState state;
        } DataTimeCounter;

        DataTimeCounter readTimeCounter(byte param);

        // Central
        bool readFlagsSwitchCentral();

        bool readCumulatedEnergyCentral(byte var, byte ndays_h, byte ndays_l, byte global);

        bool readFirmwareReleaseCentral(byte var);

        bool readBaudRateSettingCentral(byte baudcode, byte serialline);

        bool readSystemInfoCentral(byte var);

        bool readJunctionBoxMonitoringCentral(byte cf, byte rn, byte njt, byte jal, byte jah);

        bool readSystemPNCentral();

        bool readSystemSerialNumberCentral();

};
#endif
