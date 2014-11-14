
#include<string>
#include<vector>
#include<ostream>
#include<fstream>
#include<mpi.h>
#include"Service.h"
#include"Location.h"




using namespace std;
/*
	Service.cpp
	@Created 06/11/2014
	@Author Tyler Garrow

	Implements service Class
*/


const string SERVICES_DATA_PATH = "Data/services.dat";
const string SERVICES_CODES_PATH = "Data/service-codes.csv";




	/*Constructors*/
service::service(std::string code) : m_serivceTypeCode(code)
{ 
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	//grab the locations of services
	ifstream file(SERVICES_DATA_PATH.c_str());
	if (!file.is_open() || file.fail())
	{
		cerr << "ERROR (process " << rank << "): Could not open file '"
			<< SERVICES_DATA_PATH << "'" << endl;
		return;
	}

	string codeHold;
	double xHold, yHold;

	while(file >> codeHold >> xHold >> yHold) {
		if(code == codeHold) {
			m_locations.push_back(location(xHold, yHold));
		}
	}
	file.close();

	//grab name of service
	file.open(SERVICES_CODES_PATH.c_str());
	if (!file.is_open() || file.fail())
	{
		cerr << "ERROR (process " << rank << "): Could not open file '"
			<< SERVICES_CODES_PATH << "'" << endl;
		return;
	}
	string  lineHold , nameHold;
	
	while(file.good()) {
		getline(file, codeHold, ',');
		getline(file, nameHold);
		if(codeHold == code) {
			m_serviceType = nameHold;
		}
	}

	file.close();


}

	/*Public Methods*/
void service::print(ostream &out) {
	out.width(30); out << left <<"Service: ";
	out.width(15); out << right << m_serviceType;
	out << endl;

	out.width(30); out << left <<"Service Code: ";
	out.width(15); out << right << m_serivceTypeCode;
	out << endl;

	out.width(30); out << left <<"Number of Service Locations:";
	out.width(15); out << right << m_locations.size();
	out << endl;

	int numProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	out.width(30); out << left <<"Number of Processes";
	out.width(15); out << right << numProcs;
	out << endl;



}

