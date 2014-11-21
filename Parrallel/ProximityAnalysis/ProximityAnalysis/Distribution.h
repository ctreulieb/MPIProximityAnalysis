#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include<vector>
#include<iostream>
#include"RecType.h"

/*
	Distribution.h
	@Created 07/11/2014
	@Author Tyler Garrow & Craig Treulieb

	@Notes
	Distribution Bands (Kms)
		Band One - 0 to 1
		Band Two - > 1 to 2
		Band Three > 2 to 5
		Band Four  > 5

	Assumes distances are given as Metres
*/

class distribution {
private:


public:
	int m_bandOne; 
	int m_bandTwo;
	int m_bandThree;
	int m_bandFour;
	int m_total;

	double m_bandOneP, m_bandTwoP, m_bandThreeP, m_bandFourP; 
	distribution(std::vector<double> const&);
	distribution(Rec_t const&);
	distribution();

	void print(std::ostream&);

	distribution& operator +=(const distribution& b) 
	{
		this->m_total += b.m_total;

		this->m_bandOne += b.m_bandOne;
		this->m_bandTwo += b.m_bandTwo;
		this->m_bandThree += b.m_bandThree;
		this->m_bandFour += b.m_bandFour;

		this->m_bandOneP = ((double)this->m_bandOne/(double)this->m_total) * 100;
		this->m_bandTwoP = ((double)this->m_bandTwo/(double)this->m_total) * 100;
		this->m_bandThreeP = ((double)this->m_bandThree/(double)this->m_total) * 100;
		this->m_bandFourP = ((double)this->m_bandFour/(double)this->m_total) * 100;

		return *this;
	}

};



#endif