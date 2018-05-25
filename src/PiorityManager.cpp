/*
 * PiorityManager.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: duser
 */

#include "PiorityManager.h"

PiorityManager::PiorityManager() {

	normalParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > () ;
	premiunParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > () ;
    errorParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > () ;

}

// int the distructor i need to destroy the queues and the objet stored inside if any
PiorityManager::~PiorityManager() {
	this->deleteQueues();
}

// this is the producer
void PiorityManager::storeParcelToBeProcessed(Parcel *p) {

	// need to implement a limit about parcel to process
	// first of all check if the parcel to process is ready
	std::unique_lock<std::mutex> lock(m);

	if(p->isPremium())			// check on which queue store the parcel
		premiunParcel->push(p);
	else
		normalParcel->push(p);

	cond_var.notify_one();		// if a new parcel is available wake up the consumer
}


// this is the consumer
Parcel* PiorityManager::getNextParcel() {

	Timestamp now;
	Parcel *tmp = NULL;
	unsigned long long int nowTime ;
	std::unique_lock<std::mutex> lock(m);

	if (premiunParcel->empty() && normalParcel->empty())
		cond_var.wait_for(lock, std::chrono::milliseconds(SECOND_MILLIS_TOWAIT));
	// unlock the cv each second
	// i need to unlock cv and return the exception to close correctly all the thread
	// if i will have spurious wakeup it is okay i will be back in this function

	nowTime = now.getStdValue();	// get the actual timestamp

	if(!premiunParcel->empty()){
		tmp = premiunParcel->top();
		if(tmp->getScheduledTime() <=  nowTime)	// is the parcel processing time passed?
		{
			 std::cout << " NEW PARCEL "<< tmp->getNameOfParcel()<<" PREMIUM GOOD TO BE PROCESSED" << std::endl;
			 premiunParcel->pop();			// ok - remove the element and process it
			 return tmp;
		}
	}

	if(!normalParcel->empty()){

		tmp = normalParcel->top();
		if(tmp->getScheduledTime() <= nowTime)	// is the parcel processing time passed?
		{
			std::cout << " NEW PARCEL "<< tmp->getNameOfParcel()<<" NORMAL OKAY TO BE PROCESSED" << std::endl;
			normalParcel->pop();				// ok - remove the element and process it
			return tmp;
		}
	}
	// the processing time of the Parcels has not been passed now - so throw exception
	throw new NoParcelAvailableException("NOT PARCEL AVAILABLE RIGHT NOW");

}

void PiorityManager::storeParcelInError(Parcel *p) {
	errorParcel->push(p);	// store the parcel in the tree
}



void PiorityManager::deleteQueues(){

	Parcel *tmp = NULL;
				if(normalParcel != NULL){
					while(!normalParcel->empty()){
						tmp = normalParcel->top();
						normalParcel->pop();
						if(tmp!= NULL){
							delete tmp;
							tmp = NULL;
						}
					}
					delete normalParcel;
					normalParcel = NULL;
				}

				if(premiunParcel != NULL){
					while(!premiunParcel->empty()){
						tmp = premiunParcel->top();
						premiunParcel->pop();
						if(tmp!= NULL){
							delete tmp;
							tmp = NULL;
						}
					}
					delete premiunParcel;
					premiunParcel = NULL;
				}

				if(errorParcel != NULL){
					while(!errorParcel->empty()){
						tmp = errorParcel->top();
						errorParcel->pop();
						if(tmp!= NULL){
							delete tmp;
							tmp = NULL;
						}
					}
						delete errorParcel;
						errorParcel = NULL;
				}


};

PiorityManager& PiorityManager::operator=(PiorityManager&& pm){

	if (this!=&pm)
	{
		this->deleteQueues();
		Parcel * tmp = NULL;
		normalParcel = new std::priority_queue<Parcel*, std::vector<Parcel*>,
				compare>();
		if (pm.normalParcel != NULL) {
			while (!pm.normalParcel->empty()) {
				tmp = pm.normalParcel->top();
				Parcel *newParcel = new Parcel(*tmp);
				normalParcel->push(newParcel);
			}
		}
		premiunParcel = new std::priority_queue<Parcel*, std::vector<Parcel*>,
				compare>();
		if (pm.premiunParcel != NULL) {
			while (!pm.premiunParcel->empty()) {
				tmp = pm.premiunParcel->top();
				Parcel *newParcel = new Parcel(*tmp);
				premiunParcel->push(newParcel);
			}
		}

		errorParcel = new std::priority_queue<Parcel*, std::vector<Parcel*>,
				compare>();
		if (pm.errorParcel != NULL) {
			while (!pm.errorParcel->empty()) {
				tmp = pm.errorParcel->top();
				Parcel *newParcel = new Parcel(*tmp);
				errorParcel->push(newParcel);
			}
		}
		pm.deleteQueues();
	}
	return *this;
}



PiorityManager::PiorityManager(const PiorityManager& pm) {
	Parcel * tmp  = NULL;
	normalParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > () ;
	if (pm.normalParcel != NULL) {
		while (!pm.normalParcel->empty()) {
			tmp = pm.normalParcel->top();
			Parcel *newParcel = new Parcel(*tmp);
			normalParcel->push(newParcel);
		}
	}
	premiunParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > ();
	if (pm.premiunParcel != NULL) {
			while (!pm.premiunParcel->empty()) {
				tmp = pm.premiunParcel->top();
				Parcel *newParcel = new Parcel(*tmp);
				premiunParcel->push(newParcel);
			}
		}

	errorParcel = new std::priority_queue<Parcel*,std::vector<Parcel*>, compare > ();
		if (pm.errorParcel != NULL) {
				while (!pm.errorParcel->empty()) {
					tmp = pm.errorParcel->top();
					Parcel *newParcel = new Parcel(*tmp);
					errorParcel->push(newParcel);
				}
			}
}
