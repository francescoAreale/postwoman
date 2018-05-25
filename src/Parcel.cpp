/*
 * Parcel.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#include "Parcel.h"

Parcel::Parcel() {

	premium = false; // by default it is not a premium
	scheduledTime = timestamp.getStdValue(); // set the actual timestamp as the time when the process need to be scheduled
	nameOfParcel = "UNKNOWN_PARCEL";
	nameOfDest = "UNKNOWNDEST";
	rescheduled = 0;

}

Parcel::~Parcel() {

}

bool Parcel::isPremium() const {
	return premium;
}

void Parcel::setPremium(bool premium) {
	this->premium = premium;
}

const Timestamp& Parcel::getTimestamp() const {
	return timestamp;
}

void Parcel::setTimestamp(const Timestamp& timestamp) {
	this->timestamp = timestamp;
}

unsigned long long int Parcel::getScheduledTime() const {
	return scheduledTime;
}

void Parcel::setScheduledTime(unsigned long long int scheduledTime) {
	this->scheduledTime = scheduledTime;
}

std::string Parcel::getNameOfParcel() const {
	return nameOfParcel;
}

void Parcel::setNameOfParcel(std::string nameOfParcel) {
	this->nameOfParcel = nameOfParcel;
}

int Parcel::getRescheduled() const {
	return rescheduled;
}

void Parcel::incrementRescheduled() {
	this->rescheduled ++;
}

std::string Parcel::getNameOfDest() const {
	return nameOfDest;
}

void Parcel::setNameOfDest(std::string nameOfDest) {
	this->nameOfDest = nameOfDest;
}
