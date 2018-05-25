/*
 * PostWoman.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#include "PostWoman.h"


PostWoman::PostWoman(){}

PostWoman::PostWoman(std::string nameOfLogFIle) {
	Timestamp now;
	finish = false;
	log = Logger::getIstance(nameOfLogFIle,INFO);

	totalDeliveries = 0;
	successDeliveries = 0;
	ratioDeliveries = TOTAL_DELIVERIES_PERC;
}

PostWoman::~PostWoman() {
	if(log!=NULL){
		delete log;
		log = NULL;
	}
}

void PostWoman::runPostWoman() {

	  std::thread waitingParcel (&PostWoman::waitIncomingParcel,this);
	  std::thread processTheParcel (&PostWoman::processParcel,this);
	  std::thread probability ( &PostWoman::changeSuccessProbability,this);
	  std::thread finish ( &PostWoman::finishThread,this);

	  waitingParcel.join();
	  processTheParcel.join();
	  probability.join();
	  finish.join();
}

void PostWoman::waitIncomingParcel() {
	std::string newParcel;

	Parcel *p = NULL ;
	std::cout << "starting Postwoman ! OKAY IM READY TO GO!!! "<<std::endl;
	while(!finish){
		std::string nameOfParcel;
		std::string nameOfDest;
		std::string premium;


		std::cout << "waiting for Parcel ..." << std::endl;
		std::cin >> newParcel;
		std::stringstream   lineStream(newParcel);
		std::cout << "--------------------" << std::endl;

		// check if the parcel is right
		if (!(std::getline(lineStream, nameOfParcel, ',').eof()))
			if (nameOfParcel.size() != 0) {
				std::cout << "nameofParcel " << nameOfParcel << std::endl;

				if (!(std::getline(lineStream, nameOfDest, ',').eof()))
					if (nameOfDest.size() != 0) {
						std::cout << "NameOfDest " << nameOfDest << std::endl;

						std::getline(lineStream, premium);
						if (premium.size() != 0) {
							std::cout << "Premium " << premium << std::endl;
							// okay let's create the parcel object
							p =  new Parcel();
							p-> setNameOfParcel(nameOfParcel);
							p->setNameOfDest(nameOfDest);
							if (std::atoi(premium.c_str()) == 1)
								p->setPremium(true);
							else
								p->setPremium(false);

							postManager.storeParcelToBeProcessed(p);
						}
					}
				}

			if(newParcel == CLOSE_ALL){
				std::cout << "Bye..."<<std::endl;
				finish = true;
			}

		std::cout << "--------------------" << std::endl;
	}

	std::cout << "waitIncomingParcel() - FINISHING ... " << std::endl;
}


void PostWoman::processParcel() {

	unsigned long long int timestampOfParcel;
	Parcel *p = NULL;
	while(!finish){

		try{
			p = postManager.getNextParcel();

			if(!checkPostWomanAvailability())
			{
				log->critical();
				std::cout<<"POST WOMAN NOT PRESENT"<< std::endl;
				sleep(1);

			}

			if(checkEmployAvailability()){
				successTofindPostWoman.lock();
				successDeliveries++;
				successTofindPostWoman.unlock();
				std::cout<<p->getNameOfParcel()<<" DELIVERED !!!!"<< std::endl;
				log->info(p->getNameOfParcel(),p->getRescheduled(),p->getNameOfDest());
				delete p;
				p = NULL;
			}else{
				std::cout<<"EMPLOY NOT PRESENT"<< std::endl;
				if(p->getRescheduled()<3){
					std::cout<<"RESCHEDULING ... "<< std::endl;
					log->warning(p->getNameOfParcel(),p->getRescheduled(),p->getNameOfDest());
					p->incrementRescheduled();
					switch(p->getRescheduled()){
						case  0:
							timestampOfParcel = p->getScheduledTime();
							timestampOfParcel += FIRST_RESCHEDULE;
							p->setScheduledTime(timestampOfParcel);
							break;
						case 1:
							timestampOfParcel = p->getScheduledTime();
							timestampOfParcel += SECOND_RESCHEDULE;
							p->setScheduledTime(timestampOfParcel);
							break;
						case 2:
							timestampOfParcel = p->getScheduledTime();
							timestampOfParcel += THIRD_RESCHEDULE; // TODO: check here
							p->setScheduledTime(timestampOfParcel);
							break ;
					}
					postManager.storeParcelToBeProcessed(p);
				}
				else{
					std::cout<<" CANCELLED ... "<< std::endl;
					log->error(p->getNameOfParcel(),p->getRescheduled(),p->getNameOfDest());
					postManager.storeParcelInError(p);
				}
			}

			successTofindPostWoman.lock();
			totalDeliveries++;
			std::cout << "TOTAL DELIVERIES -> " << totalDeliveries << std::endl;
			successTofindPostWoman.unlock();
		}catch(NoParcelAvailableException * ex){
			std::cout << ex->what() << std::endl;
		}
	}
	std::cout << "processParcel() - FINISHING ... " << std::endl;
}


void PostWoman::changeSuccessProbability(){
	Timestamp now ;
	lastTimeStampForCHangeRand  = now.getStdValue();
	while(!finish){

				successRandNum.lock();
				randNum = rand()%(MAX_PROB-MIN_PROB + 1) + MIN_PROB;
				std::cout<<"rand now is" << randNum << std::endl;
				successRandNum.unlock();
				successTofindPostWoman.lock();
				if(totalDeliveries>0){
					std::cout << "rapport " << (successDeliveries/totalDeliveries)<< std::endl;
					ratioDeliveries = (successDeliveries/totalDeliveries)*100.0;
					successDeliveries = 0;
					totalDeliveries = 0;
				}
				successTofindPostWoman.unlock();
		sleep(1);
	}
	std::cout << "changeSuccessProbability() - FINISHING ... " << std::endl;
}


bool PostWoman::checkPostWomanAvailability() {
	bool foundedpw = false;
	successTofindPostWoman.lock();
	std::cout<<"RATIO is " << ratioDeliveries << std::endl;
	if(ratioDeliveries >= TOTAL_DELIVERIES_PERC)
		foundedpw=true;
	successTofindPostWoman.unlock();
	return foundedpw;
}


bool PostWoman::checkEmployAvailability() {
	bool availability = false;
	int randomic = rand() % 100;
	std::cout<<"randomic now is" << randomic << std::endl;
	successRandNum.lock();
	if((randomic) > randNum)
		availability=true;
	successRandNum.unlock();
	return availability;
}

static void signal_callback_handler(int signum)
{
   std::cout<<"Caught signal " << signum << std::endl;
   finish = true;
}

void PostWoman::finishThread() {
	sigset_t SigSet;
	sigemptyset(&SigSet);
	sigaddset(&SigSet, SIGINT);
	sigaddset(&SigSet, SIGTERM);
	sigaddset(&SigSet, SIGQUIT);
	sigaddset(&SigSet, SIGHUP);
	sigprocmask(SIG_BLOCK, &SigSet, NULL);
	struct sigaction SigAct;
	memset(&SigAct, 0, sizeof(SigAct));
	SigAct.sa_handler = signal_callback_handler;
			
	if (sigaction(SIGINT, &SigAct, NULL) == -1)
		std::cout <<"SIGINT failed" <<std::endl;

	if (sigaction(SIGTERM, &SigAct, NULL) == -1)
		std::cout <<"SIGTERM failed" <<std::endl;

	if (sigaction(SIGQUIT, &SigAct, NULL) == -1)
		std::cout <<"SIGQUIT failed" <<std::endl;

	if (sigaction(SIGHUP, &SigAct, NULL) == -1)
		std::cout <<"SIGHUP failed" <<std::endl;

}
