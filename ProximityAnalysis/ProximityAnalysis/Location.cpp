
#include"Location.h"

/*
	Residence.cpp
	@Created 06/11/2014
	@Author Tyler Garrow

	Implements residence Class
*/

	/*Constructors*/
location::location() {}

location::location(double x, double y) : 
	m_EastingCoordinate(x),  
	m_NorthingCoordinate(y) { }


	/*Getters*/
double location::getEastingCoordinate() {
	return m_EastingCoordinate;
}

double location::getNorthingCoordinate() {
	return m_NorthingCoordinate;
}

	/*Setters*/
void location::setEastingCoordinate(double x) {
	m_EastingCoordinate = x;
}

void location::setNorthingCoordinate(double y) {
	m_NorthingCoordinate = y;
}