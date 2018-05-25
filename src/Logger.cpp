/*
 * Logger.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#include "Logger.h"

Logger* Logger::istance = 0;

Logger* Logger::getIstance(std::string filename, LOG_FILTER logfilt) {

	if(istance==0)
	 Logger::istance=new Logger(filename,logfilt);
	return Logger::istance;
}

Logger::Logger( std::string filename, LOG_FILTER logfilt ) {

	this->severity=logfilt;
	fileToWrite.open (filename);

};

Logger::~Logger() {
	fileToWrite.close();
}

void Logger::info(std::string NameOfParcel,int NumberRetry, std::string NameOfEmploy) {
	if(severity > INFO)
		return ;
	now.setValue();
	fileToWrite <<  now.toString() << " [INFO] " << "Parcel "<< NameOfParcel << " successfully delivered to "<<NameOfEmploy<<". Retries: " << NumberRetry<< std::endl <<std::flush  ;
}

void Logger::warning(std::string NameOfParcel,int NumberRetry,std::string NameOfEmploy) {

	if(severity > WARNING)
		return;

	now.setValue();
	fileToWrite <<  now.toString() << " [WARN] " << "Parcel "<< NameOfParcel << " failed to be delivered to " <<NameOfEmploy<<". Retries: " << NumberRetry << std::endl <<std::flush ;

}

void Logger::error(std::string NameOfParcel,int NumberRetry,std::string NameOfEmploy) {

	if(severity > ERROR)
		return;

	now.setValue();
	fileToWrite <<  now.toString() <<" [ERROR] " << "Parcel "<< NameOfParcel << " parcel won't be delivered (max retries exceeded). to "<<NameOfEmploy<<". Retries: " <<NumberRetry <<std::endl <<std::flush;
}

void Logger::critical() {

	if(severity > CRITICAL)
		return;

	now.setValue();
	fileToWrite <<  now.toString() << " [CRITICAL] postwoman not available." << std::endl << std::flush;
}
