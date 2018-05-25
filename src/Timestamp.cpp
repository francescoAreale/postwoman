#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "Timestamp.h"



Timestamp::Timestamp() {
	this->setValue();
}

Timestamp::~Timestamp() {}

std::string Timestamp::toString() {

	struct tm *tm;
	
	tm = localtime(&this->Value.tv_sec);

	sprintf(this->StringValue,"%d-%02d-%02d %d:%02d:%02d:%03d",
			tm->tm_year+1900,
			tm->tm_mon+1,
			tm->tm_mday,
			tm->tm_hour,
			tm->tm_min,
			tm->tm_sec,
			(int)(this->getValue().tv_usec / 1000));

	return std::string(this->StringValue);
}

timeval Timestamp::getValue() {

	return this->Value;
}

void Timestamp::setValue() {

	struct timezone tz;

	gettimeofday(&this->Value, &tz);

	return;
}

unsigned long long int Timestamp::getStdValue() {

	unsigned long long int millisecondsSince1970;

	this->setValue();

	millisecondsSince1970 = (unsigned long long int)(this->getValue().tv_sec)* 1000 + (unsigned long long int)(this->getValue().tv_usec) / 1000;

	return millisecondsSince1970;
}
