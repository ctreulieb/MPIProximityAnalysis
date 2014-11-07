

#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "Service.h"
#include "Residence.h"
#include "Distribution.h"
using namespace std;

/*
	main.cpp
	@Created 06/11/2014
	@Author Tyler Garrow
*/

const string SERVICES_DATA_PATH = "data/services.dat";
const string RESIDENCES_DATA_PATH = "data/residences.dat";

vector<service> services;
vector<double> distances;

double calcShortestStraightLineDistance(residence, vector<service>);
void proccessResidences();
void populateServices(string);

void populateServices(string code) {
	ifstream file;
	file.open(SERVICES_DATA_PATH);
	string codeHold;
	double xHold, yHold;

	while(file >> codeHold >> xHold >> yHold) {
		if(code == codeHold) {
			services.push_back(service(codeHold, xHold, yHold));
		}
	}

	file.close();
}

void proccessResidences() {
	ifstream file;
	file.open(RESIDENCES_DATA_PATH);
	double xHold, yHold;
	while(file >> xHold >> yHold) {
		distances.push_back(calcShortestStraightLineDistance(residence(xHold,yHold),services));
	}
}

double calcShortestStraightLineDistance(residence r, vector<service> s) {
	double shortest = -1;
	for(unsigned i = 0; i < services.size(); ++i) {
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
		cout  << "Service Code Required " << endl;
		return EXIT_SUCCESS;
	}

	if( !MPI_Init(&argc, &argv) == MPI_SUCCESS )
		return EXIT_FAILURE;

	populateServices(argv[1]);

	proccessResidences();

	distrabution dist(distances);
	dist.print(cout);

	MPI_Finalize();
}