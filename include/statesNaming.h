
static String getGridStandardByParams(byte id){
	switch (id)
	{
		case 'A':
			return F("UL1741");
			break;
		case 'E':
			return F("VDE0126");
			break;
		case 'S':
			return F("DR 1663 / 2000");
			break;
		case 'I':
		case 'i':
			return F("ENEL DK 5950");
			break;
		case 'U':
			return F("UK G83");
			break;
		case 'K':
			return F("AS 4777");
			break;
		default:
			return F("Unknown");
			break;
	}
}

static String getTransmissionStateByParams(byte transmissionStateId) {
    switch (transmissionStateId)
    {
        case 0:
            return F("Everything is OK.");
            break;
        case 51:
            return F("Command is not implemented");
            break;
        case 52:
            return F("Variable does not exist");
            break;
        case 53:
            return F("Variable value is out of range");
            break;
        case 54:
            return F("EEprom not accessible");
            break;
        case 55:
            return F("Not Toggled Service Mode");
            break;
        case 56:
            return F("Can not send the command to internal micro");
            break;
        case 57:
            return F("Command not Executed");
            break;
        case 58:
            return F("The variable is not available, retry");
            break;
        default:
            return F("Unknown");
            break;
    }
}

static String getGlobalStateByParams(byte globalStateId) {
    switch (globalStateId)
    {
        case 0:
            return F("Sending Parameters");
            break;
        case 1:
            return F("Wait Sun / Grid");
            break;
        case 2:
            return F("Checking Grid");
            break;
        case 3:
            return F("Measuring Riso");
            break;
        case 4:
            return F("DcDc Start");
            break;
        case 5:
            return F("Inverter Start");
            break;
        case 6:
            return F("Run");
            break;
        case 7:
            return F("Recovery");
            break;
        case 8:
            return F("Pausev");
            break;
        case 9:
            return F("Ground Fault");
            break;
        case 10:
            return F("OTH Fault");
            break;
        case 11:
            return F("Address Setting");
            break;
        case 12:
            return F("Self Test");
            break;
        case 13:
            return F("Self Test Fail");
            break;
        case 14:
            return F("Sensor Test + Meas.Riso");
            break;
        case 15:
            return F("Leak Fault");
            break;
        case 16:
            return F("Waiting for manual reset");
            break;
        case 17:
            return F("Internal Error E026");
            break;
        case 18:
            return F("Internal Error E027");
            break;
        case 19:
            return F("Internal Error E028");
            break;
        case 20:
            return F("Internal Error E029");
            break;
        case 21:
            return F("Internal Error E030");
            break;
        case 22:
            return F("Sending Wind Table");
            break;
        case 23:
            return F("Failed Sending table");
            break;
        case 24:
            return F("UTH Fault");
            break;
        case 25:
            return F("Remote OFF");
            break;
        case 26:
            return F("Interlock Fail");
            break;
        case 27:
            return F("Executing Autotest");
            break;
        case 30:
            return F("Waiting Sun");
            break;
        case 31:
            return F("Temperature Fault");
            break;
        case 32:
            return F("Fan Staucked");
            break;
        case 33:
            return F("Int.Com.Fault");
            break;
        case 34:
            return F("Slave Insertion");
            break;
        case 35:
            return F("DC Switch Open");
            break;
        case 36:
            return F("TRAS Switch Open");
            break;
        case 37:
            return F("MASTER Exclusion");
            break;
        case 38:
            return F("Auto Exclusion");
            break;
        case 98:
            return F("Erasing Internal EEprom");
            break;
        case 99:
            return F("Erasing External EEprom");
            break;
        case 100:
            return F("Counting EEprom");
            break;
        case 101:
            return F("Freeze");
        default:
            return F("Unknown");
            break;
    }
}

static String getDcDcStateByParams(byte dcDcStateId) {
    switch (dcDcStateId)
    {
        case 0:
            return F("DcDc OFF");
            break;
        case 1:
            return F("Ramp Start");
            break;
        case 2:
            return F("MPPT");
            break;
        case 3:
            return F("Not Used");
            break;
        case 4:
            return F("Input OC");
            break;
        case 5:
            return F("Input UV");
            break;
        case 6:
            return F("Input OV");
            break;
        case 7:
            return F("Input Low");
            break;
        case 8:
            return F("No Parameters");
            break;
        case 9:
            return F("Bulk OV");
            break;
        case 10:
            return F("Communication Error");
            break;
        case 11:
            return F("Ramp Fail");
            break;
        case 12:
            return F("Internal Error");
            break;
        case 13:
            return F("Input mode Error");
            break;
        case 14:
            return F("Ground Fault");
            break;
        case 15:
            return F("Inverter Fail");
            break;
        case 16:
            return F("DcDc IGBT Sat");
            break;
        case 17:
            return F("DcDc ILEAK Fail");
            break;
        case 18:
            return F("DcDc Grid Fail");
            break;
        case 19:
            return F("DcDc Comm.Error");
            break;
        default:
            return F("Unknown");
            break;
    }
}

static String getInverterStateByParams(byte inverterStateId) {
    switch (inverterStateId)
    {
        case 0:
            return F("Stand By");
            break;
        case 1:
            return F("Checking Grid");
            break;
        case 2:
            return F("Run");
            break;
        case 3:
            return F("Bulk OV");
            break;
        case 4:
            return F("Out OC");
            break;
        case 5:
            return F("IGBT Sat");
            break;
        case 6:
            return F("Bulk UV");
            break;
        case 7:
            return F("Degauss Error");
            break;
        case 8:
            return F("No Parameters");
            break;
        case 9:
            return F("Bulk Low");
            break;
        case 10:
            return F("Grid OV");
            break;
        case 11:
            return F("Communication Error");
            break;
        case 12:
            return F("Degaussing");
            break;
        case 13:
            return F("Starting");
            break;
        case 14:
            return F("Bulk Cap Fail");
            break;
        case 15:
            return F("Leak Fail");
            break;
        case 16:
            return F("DcDc Fail");
            break;
        case 17:
            return F("Ileak Sensor Fail");
            break;
        case 18:
            return F("SelfTest: relay inverter");
            break;
        case 19:
            return F("SelfTest : wait for sensor test");
            break;
        case 20:
            return F("SelfTest : test relay DcDc + sensor");
            break;
        case 21:
            return F("SelfTest : relay inverter fail");
            break;
        case 22:
            return F("SelfTest timeout fail");
            break;
        case 23:
            return F("SelfTest : relay DcDc fail");
            break;
        case 24:
            return F("Self Test 1");
            break;
        case 25:
            return F("Waiting self test start");
            break;
        case 26:
            return F("Dc Injection");
            break;
        case 27:
            return F("Self Test 2");
            break;
        case 28:
            return F("Self Test 3");
            break;
        case 29:
            return F("Self Test 4");
            break;
        case 30:
            return F("Internal Error");
            break;
        case 31:
            return F("Internal Error");
            break;
        case 40:
            return F("Forbidden State");
            break;
        case 41:
            return F("Input UC");
            break;
        case 42:
            return F("Zero Power");
            break;
        case 43:
            return F("Grid Not Present");
            break;
        case 44:
            return F("Waiting Start");
            break;
        case 45:
            return F("MPPT");
            break;
        case 46:
            return F("Grid Fail");
            break;
        case 47:
            return F("Input OC");
            break;
        default:
            return F("Unknown");
            break;
    }
}

static String getIndoorOutdoorAndTypeByParams(byte indoorOutdoorAndTypeId){
	switch (indoorOutdoorAndTypeId)
	{
		case 'i':
			return F("Aurora 2 kW indoor");
			break;
		case 'o':
			return F("Aurora 2 kW outdoor");
			break;
		case 'I':
			return F("Aurora 3.6 kW indoor");
			break;
		case 'O':
			return F("Aurora 3.0 - 3.6 kW outdoor");
			break;
		case '5':
			return F("Aurora 5.0 kW outdoor");
			break;
		case '6':
			return F("Aurora 6 kW outdoor");
			break;
		case 'P':
			return F("3 - phase interface (3G74)");
			break;
		case 'C':
			return F("Aurora 50kW module");
			break;
		case '4':
			return F("Aurora 4.2kW new");
			break;
		case '3':
			return F("Aurora 3.6kW new");
			break;
		case '2':
			return F("Aurora 3.3kW new");
			break;
		case '1':
			return F("Aurora 3.0kW new");
			break;
		case 'D':
			return F("Aurora 12.0kW");
			break;
		case 'X':
			return F("Aurora 10.0kW");
			break;
		default:
			return F("Unknown");
			break;
	}
}

static String getTrafoOrNonTrafoByParams(byte trafoOrNonTrafoId){
	switch (trafoOrNonTrafoId)
	{
		case 'N':
			return F("Transformerless Version");
			break;
		case 'T':
			return F("Transformer Version");
			break;
		default:
			return F("Unknown");
			break;
	}
}

static String getWindOrPVByParams(byte windOrPVId){
	switch (windOrPVId)
	{
		case 'W':
			return F("Wind version");
			break;
		case 'N':
			return F("PV version");
			break;
		default:
			return F("Unknown");
			break;
	}
}

static String getAlarmDescription(byte alarmCode) {
    switch (alarmCode)
    {
        case 0:
            return F("No Alarm");
            break;
        case 1:
            return F("Sun Low");
            break;
        case 2:
            return F("Input OC");
            break;
        case 3:
            return F("Input UV");
            break;
        case 4:
            return F("Input OV");
            break;
        case 5:
            return F("Sun Low");
            break;
        case 6:
            return F("No Parameters");
            break;
        case 7:
            return F("Bulk OV");
            break;
        case 8:
            return F("Comm.Error");
            break;
        case 9:
            return F("Output OC");
            break;
        case 10:
            return F("IGBT Sat");
            break;
        case 11:
            return F("Bulk UV");
            break;
        case 12:
            return F("Internal error");
            break;
        case 13:
            return F("Grid Fail");
            break;
        case 14:
            return F("Bulk Low");
            break;
        case 15:
            return F("Ramp Fail");
            break;
        case 16:
            return F("Dc / Dc Fail");
            break;
        case 17:
            return F("Wrong Mode");
            break;
        case 18:
            return F("Ground Fault");
            break;
        case 19:
            return F("Over Temp.");
            break;
        case 20:
            return F("Bulk Cap Fail");
            break;
        case 21:
            return F("Inverter Fail");
            break;
        case 22:
            return F("Start Timeout");
            break;
        case 23:
            return F("Ground Fault");
            break;
        case 24:
            return F("Degauss error");
            break;
        case 25:
            return F("Ileak sens.fail");
            break;
        case 26:
            return F("DcDc Fail");
            break;
        case 27:
            return F("Self Test Error 1");
            break;
        case 28:
            return F("Self Test Error 2");
            break;
        case 29:
            return F("Self Test Error 3");
            break;
        case 30:
            return F("Self Test Error 4");
            break;
        case 31:
            return F("DC inj error");
            break;
        case 32:
            return F("Grid OV");
            break;
        case 33:
            return F("Grid UV");
            break;
        case 34:
            return F("Grid OF");
            break;
        case 35:
            return F("Grid UF");
            break;
        case 36:
            return F("Z grid Hi");
            break;
        case 37:
            return F("Internal error");
            break;
        case 38:
            return F("Riso Low");
            break;
        case 39:
            return F("Vref Error");
            break;
        case 40:
            return F("Error Meas V");
            break;
        case 41:
            return F("Error Meas F");
            break;
        case 42:
            return F("Error Meas Z");
            break;
        case 43:
            return F("Error Meas Ileak");
            break;
        case 44:
            return F("Error Read V");
            break;
        case 45:
            return F("Error Read I");
            break;
        case 46:
            return F("Table fail");
            break;
        case 47:
            return F("Fan Fail");
            break;
        case 48:
            return F("UTH");
            break;
        case 49:
            return F("Interlock fail");
            break;
        case 50:
            return F("Remote Off");
            break;
        case 51:
            return F("Vout Avg errror");
            break;
        case 52:
            return F("Battery low");
            break;
        case 53:
            return F("Clk fail");
            break;
        case 54:
            return F("Input UC");
            break;
        case 55:
            return F("Zero Power");
            break;
        case 56:
            return F("Fan Stucked");
            break;
        case 57:
            return F("DC Switch Open");
            break;
        case 58:
            return F("Tras Switch Open");
            break;
        case 59:
            return F("AC Switch Open");
            break;
        case 60:
            return F("Bulk UV");
            break;
        case 61:
            return F("Autoexclusion");
            break;
        case 62:
            return F("Grid df / dt");
            break;
        case 63:
            return F("Den switch Open");
            break;
        case 64:
            return F("Jbox fail");
            break;
        default:
            return F("Unknown");
            break;
    }
};

struct InverterModel {
    int ID;
    float multipler;
    String name;
};

static InverterModel getModelNameByParams(byte modelId){
    switch ((char)modelId)
    {
		case '1':
			return InverterModel({'1', 0.0970019, F("PVI-3.0-OUTD")});
			break;
		case '2':
			return InverterModel({'2', 0.1617742, F("PVI-3.3-OUTD")});
			break;
		case '3':
			return InverterModel({'3', 0.1617742, F("PVI-3.6-OUTD")});
			break;
		case '4':
			return InverterModel({'4', 0.1617742, F("PVI-4.2-OUTD")});
			break;
		case '5':
			return InverterModel({'5', 0.1617742, F("PVI-5000-OUTD")});
			break;
		case '6':
			return InverterModel({'6', 0.1617742, F("PVI-6000-OUTD")});
			break;
		case 'A':
			return InverterModel({'A', 0.1617742, F("PVI-CENTRAL-350 Liquid Cooled (AC gathering)")});
			break;
		case 'B':
			return InverterModel({'B', 0.1617742, F("PVI-CENTRAL-350 Liquid Cooled (display board)")});
			break;
		case 'C':
			return InverterModel({'C', 0.1617742, F("PVI-CENTRAL-50 module")});
			break;
		case 'D':
			return InverterModel({'D', 0.5320955, F("PVI-12.5-OUTD")});
			break;
		case 'G':
			return InverterModel({'G', -1, 		 F("UNO-2.5-I")});
			break;
		case 'g':
			return InverterModel({'g', -1, 		 F("UNO-2.0-I")});
			break;
		case 'H':
			return InverterModel({'H', -1, 		 F("PVI-4.6-I-OUTD")});
			break;
		case 'h':
			return InverterModel({'h', -1, 		 F("PVI-3.8-I-OUTD")});
			break;
		case 'I':
			return InverterModel({'I', 0.1004004, F("PVI-3600")});
			break;
		case 'i':
			return InverterModel({'i', 0.0557842, F("PVI-2000")});
			break;
		case 'L':
			return InverterModel({'L', 0.1617742, F("PVI-CENTRAL-350 Liquid Cooled (control board)")});
			break;
		case 'M':
			return InverterModel({'M', 0.5320955, F("PVI-CENTRAL-250")});
			break;
		case 'O':
			return InverterModel({'O', 0.1004004, F("PVI-3.6-OUTD")});
			break;
		case 'o':
			return InverterModel({'o', 0.0557842, F("PVI-2000-OUTD")});
			break;
		case 'P':
			return InverterModel({'P', 0.1617742, F("3-phase interface (3G74)")});
			break;
		case 'T':
			return InverterModel({'T', -1, 		 F("PVI-12.0-I-OUTD (output 480 VAC)")});
			break;
		case 't':
			return InverterModel({'t', -1, 		 F("PVI-10.0-I-OUTD (output 480 VAC)")});
			break;
		case 'U':
			return InverterModel({'U', -1, 		 F("PVI-12.0-I-OUTD (output 208 VAC)")});
			break;
		case 'u':
			return InverterModel({'u', -1, 		 F("PVI-10.0-I-OUTD (output 208 VAC)")});
			break;
		case 'V':
			return InverterModel( {'V', -1, 		 F("PVI-12.0-I-OUTD (output 380 VAC)")});
			break;
		case 'v':
			return InverterModel( {'v', -1, 		 F("PVI-10.0-I-OUTD (output 380 VAC)")});
			break;
		case 'w':
			return InverterModel({'w', -1, 		 F("PVI-10.0-I-OUTD (output 480 VAC current limit 12 A)")});
			break;
		case 'X':
			return InverterModel({'X', 0.5320955, F("PVI-10.0-OUTD")});
			break;
		case 'Y':
			return InverterModel({'Y', -1, 		 F("TRIO-27.6-TL-OUTD")});
			break;
		case 'y':
			return InverterModel({'y', -1, 		 F("TRIO-20-TL")});
			break;
		case 'Z':
			return InverterModel({'Z', -1, 		 F("PVI-12.0-I-OUTD (output 600 VAC)")});
			break;
		case 'z':
			return InverterModel( {'z', -1, 		 F("PVI-10.0-I-OUTD (output 600 VAC)")});
			break;
		default:
			return InverterModel( {modelId, -1, 		 F("Unknown")});
			break;
    }
};
static String getConfigFlagByParams(byte configFlag){
    switch (configFlag)
    {
		case 0:
			return F("System operating with both strings.");
			break;
		case 1:
			return F("String 1 connected, String 2 disconnected.");
			break;
		case 2:
			return F("String 2 connected, String 1 disconnected.");
			break;
		default:
			return F("Unknown");
			break;
    }
};
