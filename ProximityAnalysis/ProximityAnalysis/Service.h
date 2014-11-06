#ifndef SERVICE_H
#define SERVICE_H

/*
	Service.h
	@Created 06/11/2014
	@Author Tyler Garrow

	Class to contain  a individual recored read from servie.dat 
*/

class service {
private:
	int m_serivceTypeCode;
	double m_EastingCoordinate;
	double m_NorthingCoordinate;

public:
	/*Constructors*/
	service();
	service(int, double, double);
	
	/*Getters*/
	int getServiceTypeCode();
	double getEastingCoordinate();
	double getNorthingCoordinate();

	/*Setters*/
	void setServiceTypeCode(int);
	void setEastingCoordinate(double);
	void setNorthingCoordinate(double);

};

#endif