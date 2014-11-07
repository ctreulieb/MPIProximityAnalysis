#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include<vector>
#include<iostream>

/*
	Distribution.h
	@Created 07/11/2014
	@Author Tyler Garrow

	@Notes
	Distribution Bands (Kms)
		Band One - 0 to 1
		Band Two - > 1 to 2
		Band Three > 2 to 5
		Band Four  > 5

	Assumes distances are given as Metres
*/

class distrabution {
private:

	int m_bandOne; 
	int m_bandTwo;
	int m_bandThree;
	int m_bandFour;

public:
	distrabution(std::vector<double> const&);

	void print(std::ostream&);
};


#endif