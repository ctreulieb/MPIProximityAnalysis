
#include"Residence.h"

/*
	Residence.cpp
	@Created 06/11/2014
	@Author Tyler Garrow

	Implements residence Class
*/

	/*Constructors*/
residence::residence() {}

residence::residence(double x, double y) : 
	m_EastingCoordinate(x),  
	m_NorthingCoordinate(y) { }


	/*Getters*/
double residence::getEastingCoordinate() {
	return m_EastingCoordinate;
}

double residence::getNorthingCoordinate() {
	return m_NorthingCoordinate;
}

	/*Setters*/
void residence::setEastingCoordinate(double x) {
	m_EastingCoordinate = x;
}

void residence::setNorthingCoordinate(double y) {
	m_NorthingCoordinate = y;
}