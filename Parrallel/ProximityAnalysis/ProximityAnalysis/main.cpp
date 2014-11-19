

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
#include "RecType.h"
using namespace std;

/*
	main.cpp
	@Created 06/11/2014
	@Author Tyler Garrow & Craig Treulieb
*/


const string RESIDENCES_DATA_PATH = "Data/residences.dat";

const string USAGE = "USAGE ERROR: Include the name of the input file on the command line!";

const int MAX_MSG_SIZE = 100;



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

MPI_Datatype createRecType()
{
	// Setup the five arguments for a call to MPI_Type_struct()
	int count = 2;	// 2 blocks
	int blocklens[] = { 4, 4 };	// 2 doubles, 2 ints
	MPI_Aint offsets[2];	
	offsets[0] = offsetof(Rec_t, bandOnePercent); // offset in bytes to block 1
	offsets[1] = offsetof(Rec_t, bandOneCount); // offset in bytes to block 2
	MPI_Datatype old_types[] = { MPI_DOUBLE, MPI_INT };	// input data types
	MPI_Datatype t; // output data type
	
	// Call the datatype contructor function
	MPI_Type_struct(count, blocklens, offsets, old_types, &t);

	// Allocate memory for the new type
	MPI_Type_commit(&t);

	return t;
}



int main (int argc, char* argv[]) 
{

	if( !MPI_Init(&argc, &argv) == MPI_SUCCESS )
		return EXIT_FAILURE;

	int numProcs, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(argc < 2) {
		if(rank == 0)
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


	Rec_t rec;
	vector<distrabution> ds(numProcs);

	MPI_Datatype recType = createRecType();

	distrabution dist(distances);

	rec.bandOneCount = dist.m_bandOne;
	rec.bandTwoCount = dist.m_bandTwo;
	rec.bandThreeCount = dist.m_bandThree;
	rec.bandFourCount = dist.m_bandFour;
	rec.bandOnePercent = dist.m_bandOneP;
	rec.bandTwoPercent = dist.m_bandTwoP;
	rec.bandThreePercent = dist.m_bandThreeP;
	rec.bandFourPercent = dist.m_bandFourP;

	if(rank != 0) {
		MPI_Send(&rec, 1, recType, 0, 1, MPI_COMM_WORLD);
	}


	end = MPI_Wtime();

	if(rank == 0) {
		ds[0] = dist;
		MPI_Status status;
		for(unsigned i = 1; i < numProcs; i++) {
			MPI_Recv(&rec, 1, recType, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			ds[i] = distrabution(rec);
		}

		s.print(cout);
		cout.width(30); cout << left <<"Elapsed Time in Seconds: ";
		cout.width(15); cout << right << end - start;
		cout << endl << endl;

		for(unsigned i = 0; i < ds.size(); ++i) {
			cout << "Process #" << i  << " Results for " << ds[i].m_total  << " Addresses ........" << endl << endl;
			ds[i].print(cout);
		}
	}


	MPI_Type_free(&recType);
	MPI_Finalize();
}