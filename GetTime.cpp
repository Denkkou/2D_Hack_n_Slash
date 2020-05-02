#include "GetTime.h"

GetTime::GetTime() {}
GetTime::~GetTime() {}

bool GetTime::getTime(char* buffer, int bufferSize) {
	//get current time
	time_t currentTime = std::time(0);

	//store individual details of time in a struct
	struct tm info;
	localtime_s(&info, &currentTime);

	//format to legible
	size_t written = strftime(buffer, bufferSize, "%d/%m/%y %T", &info);

	//return success or failure
	return written != 0;

}

