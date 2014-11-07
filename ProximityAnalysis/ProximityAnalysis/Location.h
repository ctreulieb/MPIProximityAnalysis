#ifndef RESIDENCE_H
#define RESIDENCE_H

/*
	Residence.h
	@Created 06/11/2014
	@Author Tyler Garrow

	Class to contain  a individual recored read from residence.dat 
*/

class location {
private:
	double m_EastingCoordinate;
	double m_NorthingCoordinate;

public:
	/*Constructors*/
	location();
	location(double, double);
	
	/*Getters*/
	double getEastingCoordinate();
	double getNorthingCoordinate();

	/*Setters*/
	void setEastingCoordinate(double);
	void setNorthingCoordinate(double);

};

#endif