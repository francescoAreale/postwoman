/**
 * @class  Timestamp
 * @author Francesco Reale
 * @date   February, 2016
 * @brief  This class is meant as a class to get the timestamp
 *
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <iostream>
#include <time.h>
#include <tr1/memory>
#include <string>


	class Timestamp
	{

	public:

		/**
		* @brief Constructor
		*
		* @param void
		* @return void
		*
		*/
		Timestamp();

		/**
		* @brief Destructor
		*
		* @param void
		* @return void
		*
		*/
		~Timestamp();

		/**
		* @brief Transform the Timestamp  in the format Y-M-D h:m:s:ms
		*
		* @param void
		* @return void
		*
		*/
		std::string toString();

		/**
		* @brief This method shall return the time stored in this instance in timeval format.
		*
		* @param void
		* @return void
		*
		*/
		timeval getValue();

		/**
		* @brief This method shall update the object with the actual time.
		*
		* @param void
		* @return void
		*
		*/
		void setValue();

		/**
		* @brief This method shall return the Timestamp in the UNIX format (since 1970).
		*
		* @param void
		* @return void
		*
		*/
		unsigned long long int getStdValue();


	private:

		char StringValue[50];
		timeval Value;


	};


#endif /* TIMESTAMP_H_ */
