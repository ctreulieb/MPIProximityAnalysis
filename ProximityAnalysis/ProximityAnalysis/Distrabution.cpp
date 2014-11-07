
#include<vector>
#include<iostream>
#include"Distribution.h"

using namespace std;
/*
	Distrabution.cpp
	@Created 07/11/2014
	@Author Tyler Garrow

	implements distribution class
*/



	/*Constructors*/
distrabution::distrabution(vector<double> const &distances) {
	m_bandOne = 0;
	m_bandTwo = 0;
	m_bandThree = 0; 
	m_bandFour = 0;
	for(unsigned i = 0; i < distances.size(); ++i) {
		if(distances[i] <= 1000) {
			m_bandOne++;
		} else if(distances[i] > 1000 && distances[i] <= 2000) {
			m_bandTwo++;
		} else if(distances[i] > 2000 && distances[i] <= 5000) {
			m_bandThree++;
		} else {
			m_bandFour++;
		}
	}
}

	/*Public Methods*/
void distrabution::print(ostream &out) {
	out << m_bandOne << endl;
	out << m_bandTwo << endl;
	out << m_bandThree << endl;
	out << m_bandFour << endl;
}
