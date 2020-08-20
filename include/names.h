/* # 50 State Request */

#define	COMMAND_GET_STATE	50
#define COMMAND_GET_STATE_DESC "State Request"


/* # 52 P/N Reading */

#define COMMAND_GET_PN		52
#define COMMAND_GET_PN_DESC "P/N Reading"

#define	aChar6	0
#define aChar5  1
#define aChar4  2
#define aChar3  3
#define aChar2  4
#define aChar1  5


/* # 58 Version Reading */

#define COMMAND_GET_VERSION	58
#define COMMAND_GET_VERSION_DESC "Version Reading"

#define aPar1	2
#define aPar1i	"PVI-2000"
#define aPar1o	"PVI-2000-OUTD"
#define aPar1I	"PVI-3600"
#define aPar1O	"PVI-3.6-OUTD"
#define aPar15	"PVI-5000-OUTD"
#define aPar16	"PVI-6000-OUTD"
#define aPar1P	"3-phase interface (3G74)"
#define aPar1C	"PVI-CENTRAL-50 module"
#define aPar14	"PVI-4.2-OUTD"
#define aPar13	"PVI-3.6-OUTD"
#define aPar12	"PVI-3.3-OUTD"
#define aPar11	"PVI-3.0-OUTD"
#define aPar1D	"PVI-12.5-OUTD"
#define aPar1X	"PVI-10.0-OUTD"
#define aPar1H	"PVI-4.6-I-OUTD"
#define aPar1h	"PVI-3.8-I-OUTD"
#define aPar1T	"PVI-12.0-I-OUTD (output 480 VAC)"
#define aPar1t	"PVI-10.0-I-OUTD (output 480 VAC)"
#define aPar1U	"PVI-12.0-I-OUTD (output 208 VAC)"
#define aPar1u	"PVI-10.0-I-OUTD (output 208 VAC)"
#define aPar1V	"PVI-12.0-I-OUTD (output 380 VAC)"
#define aPar1v	"PVI-10.0-I-OUTD (output 380 VAC)"
#define aPar1Z	"PVI-12.0-I-OUTD (output 600 VAC)"
#define aPar1z	"PVI-10.0-I-OUTD (output 600 VAC)"
#define aPar1M	"PVI-CENTRAL-250"
#define aPar1w	"PVI-10.0-I-OUTD (output 480 VAC current limit 12 A)"
#define aPar1Y	"TRIO-27.6-TL-OUTD"
#define aPar1y	"TRIO-20-TL"
#define aPar1g	"UNO-2.0-I"
#define aPar1G	"UNO-2.5-I"
#define aPar1L	"PVI-CENTRAL-350 Liquid Cooled (control board)"
#define aPar1B	"PVI-CENTRAL-350 Liquid Cooled (display board)"
#define aPar1A	"PVI-CENTRAL-350 Liquid Cooled (AC gathering)"

#define aPar2   3
#define aPar2A	"USA - UL1741"
#define aPar2E	"Germany - VDE0126"
#define aPar2S	"Spain - DR 1663/2000"
#define aPar2I	"Italy - ENEL DK 5950"
#define aPar2U	"UK - UK G83"
#define aPar2K	"Australia - AS 4777"
#define aPar2F	"France - VDE French Model"
#define aPar2R	"Ireland - EN50438"
#define aPar2B	"Belgium - VDE Belgium Model"
#define aPar2O	"Korea"
#define aPar2G	"Greece - VDE Greece Model"
#define aPar2T	"Taiwan"
#define aPar2C	"Czech Republic"
#define aPar2Q	"People’s Republic of China"
#define aPar2a	"USA - UL1741 Vout = 208 single phase"
#define aPar2b	"USA - UL1741 Vout = 240 single phase"
#define aPar2c	"USA - UL1741 Vout = 277 single phase"
#define aPar2X	"Debug Standard 1"
#define aPar2x	"Debug Standard 2"
#define aPar2u	"UK – UK-G59"
#define aPar2k	"Israel – Derived from AS 4777"
#define aPar2W	"Germany – BDEW"
#define aPar2H	"Hungary"
#define aPar2o	"Corsica"
#define aPar2P	"Portugal"
#define aPar2e	"VDE AR-N-4105"

#define aPar3   4
#define aPar3T	"Transformer Version"
#define aPar3N	"Transformerless Version"
#define aPar3t	"Transformer HF version"
#define aPar3X	"Dummy transformer type"

#define aPar4   5
#define aPar4W	"Wind Version"
#define aPar4N	"Photovoltaic Version"
#define aPar4X  "Dummy inverter type"

/* # 59 Measure request to the DSP - Type of Measure */

#define	COMMAND_DSP	59
#define COMMAND_DSP_DESC "Measure request to the DSP"

#define DSP_GRID_VOLTAGE_ALL								1   /* Grid Voltage (All) */
#define DSP_GRID_CURRENT_ALL								2   /* Grid Currrent (All) */
#define DSP_GRID_POWER_ALL									3   /* Grid Power (All) */
#define DSP_FREQUENCY_ALL									4   /* Frequency All) */
#define DSP_VBULK_WAS_ILEAK_DCDC_READING_ALL				5   /* VBulk was Ileak (Dc/Dc) reading All) */
#define DSP_ILEAK_DCDC_WAS_ILEAK_INVERTER_READING			6   /* Ileak (Dc/Dc) was Ileak (Inverter) Reading*/
#define DSP_ILEAK_INVERTER									7   /* Ileak (Inverter) */
#define DSP_PIN1_ALL										8   /* Pin 1 (All) */
#define DSP_PIN2											9   /* Pin 2 */
#define DSP_INVERTER_TEMPERATURE_GT							21  /* Inverter Temperature (Grid-Tied) */
#define DSP_BOOSTER_TEMPERATURE_GT							22  /* Booster Temperatuer (Grid-Tied) */
#define DSP_VOLTAGE_ALL										23  /* Input 1 Voltage */
#define DSP_CURRENT_ALL 									25  /* Input 1 Current (All) */
#define DSP_VOLTAGE_GT										26  /* Input 2 Voltage (Grid-Tied) */
#define DSP_CURRENT_GT										27  /* Input 2 Current (Grid-Tied) */
#define DSP_GRID_VOLTAGE_DCDC_GT							28  /* Grid Voltage (Dc/Dc) (Grid-Tied) */
#define DSP_GRID_FREQUENCY_DCDC_GT							29  /* Grid Frequency (Dc/Dc) (Grid-Tied) */
#define DSP_ISOLATION_RESISTANCE_RISO_ALL					30  /* Isolation Resistance (Riso) (All) */
#define DSP_VBULK_DCDC_GT									31  /* Vbulk (Dc/Dc) (Grid-Tied) */
#define DSP_AVERAGE_GRID_VOLTAGE_VGRIDAVG_GT				32  /* Average Grid Voltage (VgridAvg) (Grid-Tied) */
#define DSP_VBULKMID_GT										33  /* Vbulk Mid (Grid-Tied) */
#define DSP_POWER_PEAK_ALL									34  /* Power Peak (All) */
#define DSP_POWER_PEAK_TODAY_ALL							35  /* Power Peak Today (All) */
#define DSP_GRID_VOLTAGE_NEUTRAL_GT							36  /* Grid Voltage neutral (Grid-Tied) */
#define DSP_WIND_GENERATOR_FREQUENCY						37  /* Wind Generator Frequency */
#define DSP_GRID_VOLTAGE_NEUTRAL_PHASE_CENTRAL				38  /* Grid Voltage neutral-phase (Central) */
#define DSP_GRID_CURRENT_PHASE_R_CENTRAL_3P					39  /* Grid Current phase r (Central & 3 Phase) */
#define DSP_GRID_CURRENT_PHASE_S_CENTRAL_3P					40  /* Grid Current phase s (Central & 3 Phase) */
#define DSP_GRID_CURRENT_PHASE_T_CENTRAL_3P					41  /* Grid Current phase t (Central & 3 Phase) */
#define DSP_FREQUENCY_PHASE_R_CENTRAL_3P					42  /* Frequency phase r (Central & 3 Phase) */
#define DSP_FREQUENCY_PHASE_S_CENTRAL_3P					43  /* Frequency phase s (Central & 3 Phase) */
#define DSP_FREQUENCY_PHASE_T_CENTRAL_3P					44  /* Frequency phase t (Central & 3 Phase) */
#define DSP_VBULK_PLUS_CENTRAL_3P							45  /* Vbulk + (Central & 3 Phase) */
#define DSP_VBULK_MINUS_CENTRAL								46  /* Vbulk - (Central) */
#define DSP_SUPERVISOR_TEMPERATURE_CENTRAL					47  /* Supervisor Temperature (Central) */
#define DSP_ALIM_TEMPERATURE_CENTRAL						48  /* Alim Temperature (Central) */
#define DSP_HEAT_SINK_TEMPERATURE_CENTRAL					49  /* Heak Sink Temperature (Central) */
#define DSP_TEMPERATURE_1_CENTRAL							50  /* Temperature 1 (Central) */
#define DSP_TEMPERATURE_2_CENTRAL							51  /* Temperature 2 (Central) */
#define DSP_TEMPERATURE_3_CENTRAL							52  /* Temperature 3 (Central) */
#define DSP_FAN_1_SPEED_CENTRAL								53  /* Fan 1 Speed (Central) */
#define DSP_FAN_2_SPEED_CENTRAL								54  /* Fan 2 Speed (Central) */
#define DSP_FAN_3_SPEED_CENTRAL								55  /* Fan 3 Speed (Central) */
#define DSP_FAN_4_SPEED_CENTRAL								56  /* Fan 4 Speed (Central) */
#define DSP_FAN_5_SPEED_CENTRAL								57  /* Fan 5 Speed (Central) */
#define DSP_POWER_SATURATION_LIMIT_DER_CENTRAL				58  /* Power Saturation limit (Der.) (Central) */
#define DSP_RIFERIMENTO_ANELLO_BULK_CENTRAL					59  /* Reference Ring Bulk (Central) */
#define DSP_VPANEL_MICRO_CENTRAL							60  /* Vpanel micro (Central) */
#define DSP_GRID_VOLTAGE_PHASE_R_CENTRAL_3P					61  /* Grid Voltage phase r (Central & 3 Phase) */
#define DSP_GRID_VOLTAGE_PHASE_S_CENTRAL_3P					62  /* Grid Voltage phase s (Central & 3 Phase) */
#define DSP_GRID_VOLTAGE_PHASE_T_CENTRAL_3P					63  /* Grid Voltage phase t (Central & 3 Phase) */
#define DSP_FAN1_SPEED_CENTRAL								95  /* Fan 1 Speed (rpm) (Central) */
#define DSP_FAN2_SPEED_RPM_CENTRAL								96  /* Fan 2 Speed (rpm) (Central) */
#define DSP_FAN3_SPEED_RPM_CENTRAL								97  /* Fan 3 Speed (rpm) (Central) */
#define DSP_FAN4_SPEED_RPM_CENTRAL								98  /* Fan 4 Speed (rpm) (Central) */
#define DSP_FAN5_SPEED_RPM_CENTRAL								99  /* Fan 5 Speed (rpm) (Central) */
#define DSP_FAN6_SPEED_RPM_CENTRAL								100 /* Fan 6 Speed (rpm) (Central) */
#define DSP_FAN7_SPEED_RPM_CENTRAL								101 /* Fan 7 Speed (rpm) (Central) */


#define DSP_GRID_VOLTAGE_ALL_DESC								"Grid Voltage Reading "		/* Global */
#define DSP_GRID_CURRENT_ALL_DESC								"Grid Current Reading "		/* Global */
#define DSP_GRID_POWER_ALL_DESC									"Grid Power Reading "		/* Global */
#define DSP_FREQUENCY_ALL_DESC									"Grid Power Calculated"
#define DSP_VBULK_WAS_ILEAK_DCDC_READING_ALL_DESC				"Frequency Reading"
#define DSP_ILEAK_DCDC_WAS_ILEAK_INVERTER_READING_DESC			"Vbulk"				/* was"Ileak (Dc/Dc) Reading" */
#define DSP_ILEAK_INVERTER_DESC									"Ileak (Dc/Dc) Reading"		/* was "Ileak (Inverter) Reading" */
#define DSP_PIN1_ALL_DESC										"Ileak (Inverter) Reading"
#define DSP_PIN2_DESC											"Pin 1 "			/* Global */
#define DSP_INVERTER_TEMPERATURE_GT_DESC						"Pin 2"
#define DSP_BOOSTER_TEMPERATURE_GT_DESC							"Inverter Temperature"
#define DSP_VOLTAGE_ALL_DESC										"Booster Temperature"		/* was Environment Temperature */
#define DSP_CURRENT_ALL_DESC 									"Input 1 Voltage"		/* Global was "West String Voltage" */
#define DSP_VOLTAGE_GT_DESC										"Input 1 Current"		/* was "West String Current" */
#define DSP_CURRENT_GT_DESC										"Input 2 Voltage"		/* was "East String Voltage" */
#define DSP_GRID_VOLTAGE_DCDC_GT_DESC							"Input 2 Current"		/* was "East String Current" */
#define DSP_GRID_FREQUENCY_DCDC_GT_DESC							"Grid Voltage (Dc/Dc)"
#define DSP_ISOLATION_RESISTANCE_RISO_ALL_DESC					"Grid Frequency (Dc/Dc)"
#define DSP_VBULK_DCDC_GT_DESC									"Isolation Resistance (Riso)"
#define DSP_AVERAGE_GRID_VOLTAGE_VGRIDAVG_GT_DESC				"Vbulk (Dc/Dc)"
#define DSP_VBULKMID_GT_DESC									"Grid Voltage Average (VgridAvg)"
#define DSP_POWER_PEAK_ALL_DESC									"Vbulk Mid"
#define DSP_POWER_PEAK_TODAY_ALL_DESC							"Power Peak"
#define DSP_GRID_VOLTAGE_NEUTRAL_GT_DESC						"Power Peak Today"
#define DSP_WIND_GENERATOR_FREQUENCY_DESC						"Grid Voltage neutral"
#define DSP_GRID_VOLTAGE_NEUTRAL_PHASE_CENTRAL_DESC				"Wind Generator Frequency"
#define DSP_GRID_CURRENT_PHASE_R_CENTRAL_3P_DESC					"Grid Voltage neutral-phase"
#define DSP_GRID_CURRENT_PHASE_S_CENTRAL_3P_DESC					"Grid Current phase r"
#define DSP_GRID_CURRENT_PHASE_T_CENTRAL_3P_DESC					"Grid Current phase s"
#define DSP_FREQUENCY_PHASE_R_CENTRAL_3P_DESC					"Grid Current phase t"
#define DSP_FREQUENCY_PHASE_S_CENTRAL_3P_DESC					"Frequency phase r"
#define DSP_FREQUENCY_PHASE_T_CENTRAL_3P_DESC					"Frequency phase s"
#define DSP_VBULK_PLUS_CENTRAL_3P_DESC							"Frequency phase t"
#define DSP_VBULK_MINUS_CENTRAL_DESC							"Vbulk +"
#define DSP_SUPERVISOR_TEMPERATURE_CENTRAL_DESC					"Vbulk -"
#define DSP_ALIM_TEMPERATURE_CENTRAL_DESC						"Supervisor Temperature"
#define DSP_HEAT_SINK_TEMPERATURE_CENTRAL_DESC					"Alim Temperature"
#define DSP_TEMPERATURE_1_CENTRAL_DESC							"Heak Sink Temperature"
#define DSP_TEMPERATURE_2_CENTRAL_DESC							"Temperature 1"
#define DSP_TEMPERATURE_3_CENTRAL_DESC							"Temperature 2"
#define DSP_FAN_1_SPEED_CENTRAL_DESC							"Temperature 3"
#define DSP_FAN_2_SPEED_CENTRAL_DESC							"Fan 1 Speed"
#define DSP_FAN_3_SPEED_CENTRAL_DESC							"Fan 2 Speed"
#define DSP_FAN_4_SPEED_CENTRAL_DESC							"Fan 3 Speed"
#define DSP_FAN_5_SPEED_CENTRAL_DESC							"Fan 4 Speed"
#define DSP_POWER_SATURATION_LIMIT_DER_CENTRAL_DESC				"Fan 5 Speed"
#define DSP_RIFERIMENTO_ANELLO_BULK_CENTRAL_DESC					"Power Saturation limit (Der.)"
#define DSP_VPANEL_MICRO_CENTRAL_DESC							"Reference Ring Bulk"
#define DSP_GRID_VOLTAGE_PHASE_R_CENTRAL_3P_DESC					"Vpanel micro"
#define DSP_GRID_VOLTAGE_PHASE_S_CENTRAL_3P_DESC					"Grid Voltage phase r"
#define DSP_GRID_VOLTAGE_PHASE_T_CENTRAL_3P_DESC					"Grid Voltage phase s"
#define DSP_FAN1_SPEED_CENTRAL_DESC								"Grid Voltage phase t"
#define DSP_FAN1_SPEED_RPM_CENTRAL_DESC								"Fan 1 RPM"
#define DSP_FAN2_SPEED_RPM_CENTRAL_DESC								"Fan 2 RPM"
#define DSP_FAN3_SPEED_RPM_CENTRAL_DESC								"Fan 3 RPM"
#define DSP_FAN4_SPEED_RPM_CENTRAL_DESC								"Fan 4 RPM"
#define DSP_FAN5_SPEED_RPM_CENTRAL_DESC								"Fan 5 RPM"
#define DSP_FAN6_SPEED_RPM_CENTRAL_DESC								"Fan 6 RPM"
#define DSP_FAN7_SPEED_RPM_CENTRAL_DESC								"Fan 7 RPM"

#define _Str1P	"Input 1 Power"			/* was "West String Power" */
#define _Str2P  "Input 2 Power"			/* was "East String Power" */

#define _DcAcEff	"DC/AC Conversion Efficiency"


/* # 63 Serial Number */

#define	COMMAND_GET_SN		63
#define COMMAND_GET_SN_DESC "Serial Number"


/* # 65 Manufacturing Week and Year */

#define COMMAND_GET_MANUFACTURING_WEEK_YEAR	65
#define COMMAND_GET_MANUFACTURING_WEEK_YEAR_DESC "Manufacturing Week and Year"

#define	aWeekH	2
#define aWeekL	3
#define aYearH	4
#define aYearL	5


/* # 68 Cumulated Float Energy (Central & TRIO only)*/

#define COMMAND_CUMULATED_FLOAT_ENERGY         68
#define COMMAND_CUMULATED_FLOAT_ENERGY_DESC "Cumulated Float Energy"

#define CECpar1  1               /* Daily Energy */
#define CECpar2  2               /* Weekly Energy */
#define CECpar3  3               /* Monthly Energy */
#define CECpar4  4               /* Yearly Energy */
#define CECpar5  5               /* nDays Energy */
#define CECpar6  6               /* Total Energy (total lifetime) */
#define CECpar7  7               /* Partial Energy (cumulated since reset) */

#define _CECpar1  "Daily Energy"
#define _CECpar2  "Weekly Energy"
#define _CECpar3  "Monthly Energy"
#define _CECpar4  "Yearly Energy"
#define _CECpar5  "Days Energy"
#define _CECpar6  "Total Energy"
#define _CECpar7  "Partial Energy"


/* # 70 0x46 Get Time/Date */

#define COMMAND_GET_TIMEDATE	70
#define COMMAND_GET_TIMEDATE_DESC "Get Time/Date"


/* # 71 Set Time/Date */

#define COMMAND_SET_TIME_DATE	71
#define COMMAND_SET_TIME_DATE_DESC "Set Time/Date"


/* # 72 Firmware Release */

#define COMMAND_GET_FIRMWARE_RELEASE	72
#define COMMAND_GET_FIRMWARE_RELEASE_DESC "Firmware Release"

#define aRel3	2
#define aRel2   3
#define aRel1   4
#define aRel0   5


/* # 75 Energy delivred to grip every 10 seconds ** Experimental ** */

#define opGetCESent	0x4b01  /* 75 01 */
#define _opGetCESent "Energy Sent To Grid"

#define aCESMemAdd	0x000a
#define aCESMaxCnt	4320


/* # 75 Energy cumulated each day address ** Experimental ** */

#define opGetCEAdd	0x4b02	/* 75 02 */
#define _opGetCEAdd "Daily Cumulated Energy Address"

#define aCEAddH		2
#define aCEAddL		3


/* # 76 Energy cumulated in the last 10 seconds */

#define	opGetEnergy10Sec	76
#define _opGetEnergy10Sec "Energy cumulated in the last 10 seconds"

#define	aEnergyH	2
#define	aEnergyL	3


/* # 77 System Configuration */

#define COMMAND_GET_CONFIG	77
#define COMMAND_GET_CONFIG_DESC "System Configuration"

#define	aConfCode	2

#define	CC_SYSTEM_OPERATING_WITH_BOTH_STRINGS	0
#define CC_STRING_1_CONNECTED_STRING_2_DISCONNECTED	1
#define CC_STRING_1_DISCONNECTED_STRING_2_DISCONNECTED	2

#define CC_SYSTEM_OPERATING_WITH_BOTH_STRINGS_DESC			"System operating with both strings."
#define	CC_STRING_1_CONNECTED_STRING_2_DISCONNECTED_DESC	"String 1 connected, String 2 disconnected."
#define	CC_STRING_1_DISCONNECTED_STRING_2_DISCONNECTED_DESC	"String 2 connected, String 1 disconnected."


/* # 78 Cumulated Energy */

#define	COMMAND_GET_CUMULATED_ENERGY		78
#define COMMAND_GET_CUMULATED_ENERGY_DESC "Cumulated Energy"

#define CUMULATED_DAILY_ENERGY					0				/* Daily Energy */
#define CUMULATED_WEEKLY_ENERGY  				1				/* Weekly Energy */
#define CUMULATED_ENERGY_OF_LAST_7_DAYS  		2				/* Energy of last 7 days */
#define CUMULATED_MONTHLY_ENERGY  				3				/* Monthly Energy */
#define CUMULATED_YEARLY_ENERGY  				4				/* Yearly Energy */
#define CUMULATED_TOTAL_ENERGY_LIFETIME  		5				/* Total Energy (total lifetime) */
#define CUMULATED_PARTIAL_ENERGY_SINCE_RESET  	6				/* Partial Energy (cumulated since reset) */

#define DAILY_ENERGY_DESC				  	"Daily Energy"
#define WEEKLY_ENERGY_DESC  			   	"Weekly Energy"
#define ENERGY_OF_LAST_7_DAYS_DESC  	   	"Energy last 7 days"
#define MONTHLY_ENERGY_DESC  			  	"Monthly Energy"
#define YEARLY_ENERGY_DESC  				"Yearly Energy"
#define TOTAL_ENERGY_LIFETIME_DESC  		"Total Energy"
#define PARTIAL_ENERGY_SINCE_RESET_DESC  	"Partial Energy"

/* # 80 Time Counter */

#define	COMMAND_GET_TIME_COUNTER	80
#define COMMAND_GET_TIME_COUNTER_DESC "Time Counter"

#define	CT_TOTAL_RUN		0
#define CT_PARTIAL_RUN		1
#define CT_TOTAL_GRID		2
#define CT_RESET_PARTIAL	3

#define CT_TOTAL_RUN_DESC	"Total Running Time (Lifetime)"
#define CT_PARTIAL_RUN_DESC	"Partial Running Time (since reset)"
#define CT_TOTAL_GRID_DESC	"Total Time With Grid Connection"
#define CT_RESET_PARTIAL_DESC	"Reset of Partial (Time & Energy)"


/* # 86 Last four alarms */

#define COMMAND_GET_LAST_4_ALARMS	86
#define COMMAND_GET_LAST_4_ALARMS_DESC F("Last four alarms")

/* return codes same as alarms from # 50 State request */

#define COMMAND_BAUD_RATE_SETTING_WRITE 85
#define COMMAND_BAUD_RATE_SETTING_WRITE_DESC "Write the baudrate"

#define BAUD_RATE_AT_19200bps 0
#define BAUD_RATE_AT_9600bps 1
#define BAUD_RATE_AT_4800bps 2
#define BAUD_RATE_AT_2400bps 3

/* # 105 P/N Reading */

#define COMMAND_GET_PN_READING	105
#define COMMAND_GET_PN_READING_DESC "P/N Reading (Central)"

#define aChar6  0
#define aChar5  1
#define aChar4  2
#define aChar3  3
#define aChar2  4
#define aChar1  5


///* # 56 0x38 unknown */
//
//#define opGet0x38	56
//#define _opGet0x38	"0x38 unknown"
//
//
///* # 82 0x52 unknown */
//
//#define opGet0x52	82
//#define _opGet0x52      "0x52 unknown"
//
//
///* # 83 0x53 unknown */
//
//#define opGet0x53	83
//#define _opGet0x53      "0x53 unknown"
//

