#include <time.h>

#define SECS_IN_MINUTES	60L
#define SECS_IN_HOURS	(60L*SECS_IN_MINUTES)
#define SECS_IN_DAYS	(24L*SECS_IN_HOURS)
#define	SECS_IN_YEARS	(365L*SECS_IN_DAYS)

#define EPOCH_TO_START_TIME 946684800

//static unsigned long convertToLong(byte receiveData[8], byte aParam1 = 2, byte aParam2 = 3, byte aParam3 = 4, byte aParam4 = 5)
//{
//    unsigned char cValue[4];
//    unsigned long *value = 0;
//
//    bool bSwapEndian = false;
//    if (! bSwapEndian) {
//        cValue[0] = receiveData[aParam4] & 0xff;
//        cValue[1] = receiveData[aParam3] & 0xff;
//        cValue[2] = receiveData[aParam2] & 0xff;
//        cValue[3] = receiveData[aParam1] & 0xff;
//    } else {
//        cValue[0] = receiveData[aParam1] & 0xff;
//        cValue[1] = receiveData[aParam2] & 0xff;
//        cValue[2] = receiveData[aParam3] & 0xff;
//        cValue[3] = receiveData[aParam4] & 0xff;
//    }
//
//    value = (unsigned long *)cValue;
//
//    return(*value & 0xffffffff);
//}

static int * getSecondsInDateElementsByParams(unsigned long seconds){
	int years = seconds / SECS_IN_YEARS;
	int days = (seconds-(years*SECS_IN_YEARS))/SECS_IN_DAYS;
	int hours = (seconds-((years*SECS_IN_YEARS)+(days*SECS_IN_DAYS)))/SECS_IN_HOURS;
	int minutes = (seconds-((years*SECS_IN_YEARS)+(days*SECS_IN_DAYS)+(hours*SECS_IN_HOURS)))/SECS_IN_MINUTES;
	int secs = (seconds-((years*SECS_IN_YEARS)+(days*SECS_IN_DAYS)+(hours*SECS_IN_HOURS)+(minutes*SECS_IN_MINUTES)));
	static int result[5];
	result[0] = years;
	result[1] = days;
	result[2] = hours;
	result[3] = minutes;
	result[4] = secs;

	return result;
}

static String getDateTimeStringByParams(tm *newtime, char* pattern = (char *)"%d/%m/%Y %H:%M:%S"){
    char buffer[30];
    strftime(buffer, 30, pattern, newtime);
    return buffer;
}

static tm getDateTimeByParams(long time){
    struct tm *newtime;
    const time_t tim = time;
    newtime = localtime(&tim);
    return *newtime;
}

static String getEpochStringByParams(long time, char* pattern = (char *)"%d/%m/%Y %H:%M:%S"){
//    struct tm *newtime;
    tm newtime;
    newtime = getDateTimeByParams(time);
    return getDateTimeStringByParams(&newtime, pattern);
}

