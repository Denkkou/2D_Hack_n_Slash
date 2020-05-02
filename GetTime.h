#ifndef aGetTimeFile
#define aGetTimeFile

#include <iostream>
#include <ctime>

class GetTime {
public:
	GetTime();
	~GetTime();
	bool getTime(char* buffer, int bufferSize);
};

#endif 
