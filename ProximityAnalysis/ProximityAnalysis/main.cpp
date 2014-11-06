

#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "Service.h"
using namespace std;

/*
	main.cpp
	@Created 06/11/2014
	@Author Tyler Garrow
*/

const string SERVICES_DATA_PATH = "data/services.dat";
vector<service> services;

void populateServices() {
	ifstream file;
	file.open(SERVICES_DATA_PATH);
	int codeHold;
	double xHold, yHold;

	while(file >> codeHold >> xHold >> yHold) {
		
		services.push_back(service(codeHold, xHold, yHold));
	}

	file.close();
}



int main (int argc, char* argv[]) 
{
	if( !MPI_Init(&argc, &argv) == MPI_SUCCESS )
		return EXIT_FAILURE;
	
	populateServices();

	MPI_Finalize();
}