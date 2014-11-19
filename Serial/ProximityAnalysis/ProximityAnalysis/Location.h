#ifndef RESIDENCE_H
#define RESIDENCE_H

/*
	Residence.h
	@Created 06/11/2014
	@Author Tyler Garrow, Craig Treulieb

	Class to contain a individual record read from residence.dat 
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