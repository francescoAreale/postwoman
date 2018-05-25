/*
 * NoParcelAvailableException.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: Francesco Reale
 */

#include "NoParcelAvailableException.h"

NoParcelAvailableException::NoParcelAvailableException() {
}

NoParcelAvailableException::NoParcelAvailableException(const std::string &message) {
	this->message = message;
}
const std::string &NoParcelAvailableException::getMessage() const {
		return message;
}

const char *NoParcelAvailableException::what() const throw () {
		return message.c_str();
}

NoParcelAvailableException::~NoParcelAvailableException()  throw () {
	// TODO Auto-generated destructor stub
}

