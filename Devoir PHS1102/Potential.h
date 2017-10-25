#ifndef POTENTIAL_H
#define POTENTIAL_H
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Potential
{
public:
	Potential();
	Potential(const double& val, const bool& modif);
	Potential(const Potential& pot);
	~Potential();

	double getValue() const;
	bool isModif() const; // retourne vrai si c'est un potentiel modifiable
	void setValue(const double& val);
	void setModif(const bool& modif);


private:
	bool modifiable; //indique si on peut appliquer la methode des differences finies
					 //(faux si region de condictivite nulle, dielectrique, source ou drain)
	double value;
};

#endif