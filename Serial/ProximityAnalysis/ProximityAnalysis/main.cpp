

#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "Service.h"
#include "Location.h"
#include "Distribution.h"
using namespace std;

/*
	main.cpp
	@Created 06/11/2014
	@Author Tyler Garrow, Craig Treulieb
*/


const string RESIDENCES_DATA_PATH = "data/residences.dat";

const string USAGE = "ProximityAnalysis [serviceCode]";

vector<location> services;
vector<double> distances;

double calcShortestStraightLineDistance(location, vector<location>);
void proccessResidences();

void proccessResidences(vector<location> const &services) {
	ifstream file;
	file.open(RESIDENCES_DATA_PATH);
	double xHold, yHold;
	while(file >> xHold >> yHold) {
		distances.push_back(calcShortestStraightLineDistance(location(xHold,yHold),services));
	}
}

double calcShortestStraightLineDistance(location r, vector<location> s) {
	double shortest = -1;
	for(unsigned i = 0; i < s.size(); ++i) {
		double D = sqrt(
			pow(
				(s[i].getEastingCoordinate() - r.getEastingCoordinate()),   
				2.0
			)
			+
			pow(
			(s[i].getNorthingCoordinate() - r.getNorthingCoordinate()),
				2.0
			)
		);

		if(shortest > D || shortest == -1) {
			shortest = D;
		}
	}
	return shortest;
}

int main (int argc, char* argv[]) 
{
	if(argc < 2) {
		cout  << USAGE << endl;
		return EXIT_SUCCESS;
	}

	if( !MPI_Init(&argc, &argv) == MPI_SUCCESS )
		return EXIT_FAILURE;

	locale loc("");
	cout.imbue(loc);

	double start, end;
	start = MPI_Wtime();

	service s(argv[1]);
	proccessResidences(s.m_locations);

	end = MPI_Wtime();

	s.print(cout);
	cout.width(30); cout << left <<"Elapsed Time in Seconds: ";
	cout.width(15); cout << right << end - start;
	cout << endl << endl;


	distribution dist(distances);
	dist.print(cout);

	MPI_Finalize();
}