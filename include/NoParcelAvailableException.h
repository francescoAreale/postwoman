/*
 * NoParcelAvailableException.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#ifndef NOPARCELAVAILABLEEXCEPTION_H_
#define NOPARCELAVAILABLEEXCEPTION_H_

#include <string>
#include<iostream>

class NoParcelAvailableException {
public:
	NoParcelAvailableException();
	virtual ~NoParcelAvailableException() throw();
	const std::string &getMessage() const;
	NoParcelAvailableException(const std::string &message);
	const char *what() const throw();
private:
	std::string message;
};

#endif /* NOPARCELAVAILABLEEXCEPTION_H_ */
