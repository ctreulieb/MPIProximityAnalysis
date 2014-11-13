

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
	@Author Tyler Garrow
*/


const string RESIDENCES_DATA_PATH = "data/residences.dat";

const string USAGE = "USAGE ERROR: Include the name of the input file on the command line!";

vector<location> services;
vector<double> distances;

double calcShortestStraightLineDistance(location, vector<location>);
void proccessResidences();

void proccessResidences(int rank, int numProcs,vector<location> const &services) {
	ifstream file(RESIDENCES_DATA_PATH.c_str());
	if (!file.is_open() || file.fail())
	{
		cerr << "ERROR (process " << rank << "): Could not open file '"
			<< RESIDENCES_DATA_PATH << "'" << endl;
		return;
	}

	string rec;
	getline(file, rec);
	int sinBytes = (int)file.tellg();

	// Move the file pointer to MY first record
	file.seekg(sinBytes * rank, ios::beg);

	double xHold, yHold;
	while(file >> xHold >> yHold) {
		distances.push_back(calcShortestStraightLineDistance(location(xHold,yHold),services));

		// Move file pointer to MY next record
		file.seekg(sinBytes * (numProcs-1), ios::cur);
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

	if( !MPI_Init(&argc, &argv) == MPI_SUCCESS )
		return EXIT_FAILURE;

	int numProcs, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(argc < 2) {
		if(rank = 0)
			cerr  << USAGE << endl;
		MPI_Finalize();
		return EXIT_SUCCESS;
	}

	

	locale loc("");
	cout.imbue(loc);

	double start, end;
	start = MPI_Wtime();

	service s(argv[1]);
	proccessResidences(rank,numProcs,s.m_locations);

	end = MPI_Wtime();

	if(rank == 0) {
		s.print(cout);
		cout.width(30); cout << left <<"Elapsed Time in Seconds: ";
		cout.width(15); cout << right << end - start;
		cout << endl << endl;
	}

	distrabution dist(distances);
	dist.print(cout);

	
}