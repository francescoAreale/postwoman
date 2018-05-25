/*
 * Logger.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Timestamp.h"
#include <iostream>
#include <fstream>
#include <sstream>

typedef enum {

		INFO = 0,
		WARNING = 1,
		ERROR = 2,
		CRITICAL = 3

	}LOG_FILTER;
class Logger {
public:
	virtual ~Logger();
	static Logger* getIstance(std::string filename,LOG_FILTER logfilt);

	void info(std::string NameOfParcel,int NumberRetry, std::string NameOfEmploy);
	void warning(std::string NameOfParcel,int NumberRetry, std::string NameOfEmploy);
	void error(std::string NameOfParcel,int NumberRetry, std::string NameOfEmploy);
	void critical();

private:

	std::ofstream fileToWrite;
	static Logger *istance;
	Logger(std::string logfilter,LOG_FILTER logfilt);
	int severity;
	Timestamp now;
};

#endif /* LOGGER_H_ */
