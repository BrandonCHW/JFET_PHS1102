#ifndef JFET_H
#define JFET_H
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "Potential.h"

using namespace std;

class Jfet
{
public:
	Jfet();
	Jfet(const int& x, const int& y);
	~Jfet();
	
	//getters
	int getsize_x() const;
	int getsize_y() const;
	Potential getpot(const int& x, const int& y) const;

	//setters
	void setsize_x(const int& size);
	void setsize_y(const int& size);
	void setpot(const int& x, const int& y, const double& pot);

	//jfet methods
	void setPotsModif();
	void finiteDifferenceMethod(const double& Seuil, const double& MaxItera);
	void printpots();
	
private:
	int size_x;
	int size_y;
	Potential** potentials;
};

#endif