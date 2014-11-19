#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <iostream>
#include "Location.h"

/*
	Service.h
	@Created 06/11/2014
	@Author Tyler Garrow, Craig Treulieb

	Contains Information Related to a Service and The Service Locations
*/

class service {
private:
	std::string m_serivceTypeCode;
	std::string m_serviceType;
	
public:
	/*Constructors*/
	service(std::string);
	
	void print(std::ostream&);
	std::vector<location> m_locations;
};

#endif