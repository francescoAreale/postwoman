/*
 * Parcel.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#ifndef PARCEL_H_
#define PARCEL_H_

#include "Timestamp.h"
#include <string>

class Parcel {

public:
	Parcel();
	virtual ~Parcel();

	bool isPremium() const;
	void setPremium(bool premium);
	const Timestamp& getTimestamp() const;
	void setTimestamp(const Timestamp& timestamp);
	unsigned long long int getScheduledTime() const;
	void setScheduledTime(unsigned long long int scheduledTime);
	std::string getNameOfParcel() const;
	void setNameOfParcel(std::string nameOfParcel);
	int getRescheduled() const;
	void incrementRescheduled();
	std::string getNameOfDest() const;
	void setNameOfDest(std::string nameOfDest);

private:
	bool premium;
	Timestamp timestamp;
	unsigned long long int scheduledTime;
	std::string nameOfParcel;
	int rescheduled; // number of time the parcel has been rescheduled
	std::string nameOfDest; // name of the destinatary Employ
};

#endif /* PARCEL_H_ */
