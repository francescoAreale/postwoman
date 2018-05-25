/*
 * PiorityManager.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#ifndef PIORITYMANAGER_H_
#define PIORITYMANAGER_H_

#include "Parcel.h"
#include <queue>
#include <vector>
#include <condition_variable>
#include <mutex>
#include "NoParcelAvailableException.h"
#include <chrono>

#define SECOND_MILLIS_TOWAIT				1000
class PiorityManager {

	 struct compare
	 {
	   bool operator()(Parcel * l, Parcel* r)
	   {
		   // schedule the parcel based from time arrival
	       return l->getScheduledTime() > r->getScheduledTime();
	   }
	 };

public:

	PiorityManager();
	virtual ~PiorityManager();
	void storeParcelToBeProcessed(Parcel *p); // store the parcel in the priority queue to be processed
	Parcel* getNextParcel (); // get the next parcel
	void storeParcelInError(Parcel *p);	// store the parcels not more valid
	PiorityManager (const PiorityManager &pm);
	PiorityManager& operator=(PiorityManager&& other);
	void deleteQueues();


private:

	std::mutex m;
	std::condition_variable cond_var;
	std::priority_queue<Parcel*,std::vector<Parcel*>, compare > *normalParcel ;
	std::priority_queue<Parcel*,std::vector<Parcel*>, compare > *premiunParcel ;
	std::priority_queue<Parcel*,std::vector<Parcel*>, compare > *errorParcel ;
};

#endif /* PIORITYMANAGER_H_ */
