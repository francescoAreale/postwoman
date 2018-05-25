/*
 * PostWoman.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#ifndef POSTWOMAN_H_
#define POSTWOMAN_H_

#include "PiorityManager.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <signal.h>
#include <sys/signalfd.h>
#include <cstring>
#include <algorithm>
#define SEC						1000
#define MIN_PROB				5
#define MAX_PROB				25
#define FIRST_RESCHEDULE		100
#define SECOND_RESCHEDULE		300
#define THIRD_RESCHEDULE		1000
#define TOTAL_DELIVERIES_PERC	85
#define NUMBER_OF_OBJECT_FROM_INPUT	3
#define CLOSE_ALL				"close"

static volatile sig_atomic_t finish;

class PostWoman {
public:
	PostWoman();
	PostWoman(std::string);
	virtual ~PostWoman();
	void runPostWoman();
	void waitIncomingParcel ();
	void processParcel();
	bool checkEmployAvailability();
	void changeSuccessProbability();
	bool checkPostWomanAvailability();
	void finishThread();
	//static volatile sig_atomic_t finish;
private:

	PiorityManager postManager;
	Logger *log;
	int randNum ;
	double totalDeliveries;
	double successDeliveries;
	int ratioDeliveries;
	std::mutex successRandNum;
	std::mutex successTofindPostWoman;

	unsigned long long int lastTimeStampForCHangeRand;
};

#endif /* POSTWOMAN_H_ */
