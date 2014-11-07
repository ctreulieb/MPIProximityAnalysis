
#include<string>
#include"Service.h"
/*
	Service.cpp
	@Created 06/11/2014
	@Author Tyler Garrow

	Implements service Class
*/

	/*Constructors*/
service::service() {}

service::service(std::string code, double x, double y) : 
	m_serivceTypeCode(code),
	m_EastingCoordinate(x),
	m_NorthingCoordinate(y) { }

	/*Getters*/
std::string service::getServiceTypeCode() {
	return m_serivceTypeCode;
}

double service::getEastingCoordinate() {
	return m_EastingCoordinate;
}

double service::getNorthingCoordinate() {
	return m_NorthingCoordinate;
}

	/*Setters*/
void service::setServiceTypeCode(std::string code) {
	m_serivceTypeCode = code;
}

void service::setEastingCoordinate(double x) {
	m_EastingCoordinate = x;
}

void service::setNorthingCoordinate(double y) {
	m_NorthingCoordinate = y;
}