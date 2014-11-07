#ifndef SERVICE_H
#define SERVICE_H

#include <string>

/*
	Service.h
	@Created 06/11/2014
	@Author Tyler Garrow

	Class to contain  a individual recored read from servie.dat 
*/

class service {
private:
	std::string m_serivceTypeCode;
	double m_EastingCoordinate;
	double m_NorthingCoordinate;

public:
	/*Constructors*/
	service();
	service(std::string, double, double);
	
	/*Getters*/
	std::string getServiceTypeCode();
	double getEastingCoordinate();
	double getNorthingCoordinate();

	/*Setters*/
	void setServiceTypeCode(std::string);
	void setEastingCoordinate(double);
	void setNorthingCoordinate(double);

};

#endif