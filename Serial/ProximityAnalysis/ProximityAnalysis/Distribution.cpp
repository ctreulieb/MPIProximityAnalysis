
#include<vector>
#include<iostream>
#include<mpi.h>
#include"Distribution.h"

using namespace std;
/*
	Distribution.cpp
	@Created 07/11/2014
	@Author Tyler Garrow, Craig Treulieb

	implements distribution class
*/



	/*Constructors*/
distribution::distribution(vector<double> const &distances) {

	m_total = distances.size();
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
void distribution::print(ostream &out) {

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	out << "Process #" << rank << " Results for " << m_total  << " Addresses ........" << endl;

	out << endl;

	out.width(25); out << right << "Nearest Service (KM)";
	out.width(25); out << right << "# of Addresses";
	out.width(25); out << right << "% of Addresses";
	out << endl;

	out.width(25); out << right << "--------------------";
	out.width(25); out << right << "--------------";
	out.width(25); out << right << "--------------";
	out << endl;

	out.width(25); out << right << "0 - 1";
	out.width(25); out << right << m_bandOne;
	out.width(25); out << right << ((double)m_bandOne/(double)m_total) * 100;
	out << endl;

	out.width(25); out << right << "1 - 2";
	out.width(25); out << right << m_bandTwo;
	out.width(25); out << right << ((double)m_bandTwo/(double)m_total) * 100;
	out << endl;

	out.width(25); out << right << "2 - 5";
	out.width(25); out << right << m_bandThree;
	out.width(25); out << right << ((double)m_bandThree/(double)m_total) * 100;
	out << endl;

	out.width(25); out << right << " > 5";
	out.width(25); out << right << m_bandFour;
	out.width(25); out << right << ((double)m_bandFour/(double)m_total) * 100;
	out << endl;

}
