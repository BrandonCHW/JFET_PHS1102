#include "JFET.h"

Jfet::Jfet()
{
	size_x = 1;
	size_y = 1;
	potentials = new Potential*[size_x];
	for (int i = 0; i < size_x; ++i) {
		potentials[i] = new Potential[size_y];
	}
}

Jfet::Jfet(const int& x, const int& y): size_x(x), size_y(y)
{
	potentials = new Potential*[x];
	for (int i = 0; i < size_x; ++i) {
		potentials[i] = new Potential[y];
	}
}

Jfet::~Jfet()
{

	for (int i = 0; i < size_x; ++i)
		delete[] potentials[i];

	delete[] potentials;
}


int Jfet::getsize_x() const
{
	return size_x;
}
int Jfet::getsize_y() const
{
	return size_y;
}

Potential Jfet::getpot(const int& x, const int& y) const
{
	return potentials[x][y];
}

void Jfet::setsize_x(const int& size) 
{
	size_x = size;
}

void Jfet::setsize_y(const int& size) 
{
	size_y = size;
}

void Jfet::setpot(const int& x, const int& y, const double& pot)
{
	potentials[x][y].setValue(pot);
}

// Marque les potentiels qui ne peuvent pas etre modifies (constants)
void Jfet::setPotsModif()
{
	for (int toprow = 0; toprow <= 3; toprow++) // grille du haut
		for (int topcol = 5; topcol <= 11; topcol++) {
			potentials[toprow][topcol].setModif(false);
		}

	for (int bottomrow = 9; bottomrow <= 12; bottomrow++) // grille du base
		for (int bottomcol = 5; bottomcol <= 11; bottomcol++) {
			potentials[bottomrow][bottomcol].setModif(false); 
	}

	for (int sourcerow = 0; sourcerow <= 3; sourcerow++) // potentiels a la source
		potentials[sourcerow][0].setModif(false);

	for (int drainrow = 9; drainrow <= 12; drainrow++) // potentiels au drain
		potentials[drainrow][16].setModif(false);
}

void Jfet::finiteDifferenceMethod(const double& Seuil, const double& MaxItera)
{
	double v1, v2, v3, v4 = 0.0; //potentiels autour du point recherche. 
							   //v0 = potentiel recherche. v1 = pot. gauche, v2 = pot. haut, v3 = bas, v4 = droite
	double vertical, horizontal = 0;
	bool isVerticalEdge, isHorizontalEdge;

	unsigned Nitera = 0; // nombre d'iterations presentement
	bool Convergence = false;
	double Vnouveau = 0.0;

	while (!Convergence && Nitera < MaxItera)
	{
			Nitera++;
			Convergence = true;
	
			for (int row = 0; row < getsize_x(); ++row) { // pour chaque point
				for (int col = 0; col < getsize_y(); ++col) {
					if (getpot(row, col).isModif()) { //verifier que le potentiel peut etre modifiable

						vertical = 0;
						horizontal = 0;
						isVerticalEdge = false;
						isHorizontalEdge = false;


						if (col - 1 < 0) { // potentiel a la frontiere conducteur/dielectrique gauche
							v1 = 0; //aucun potentiel
							isVerticalEdge = true;
						}
						else {
							v1 = getpot(row, col - 1).getValue();
						}

						if (col + 1 > getsize_y() - 1) {// potentiel a la frontiere conducteur/dielectrique droite
							v4 = 0;
							isVerticalEdge = true;
						}
						else
							v4 = getpot(row, col + 1).getValue();

						if (row - 1 < 0) {// potentiel a la frontiere conducteur/dielectrique haut
							v2 = 0;
							isHorizontalEdge = true;
						}
						else
							v2 = getpot(row - 1, col).getValue();

						if (row + 1 > getsize_x() - 1) {
							v3 = 0;
							isHorizontalEdge = true;
						}
						else
							v3 = getpot(row + 1, col).getValue();

						vertical = v2 + v3;
						horizontal = v1 + v4;
					
						//moyenne
						if (isVerticalEdge && !isHorizontalEdge) { //est un interface conducteur/dielectrique vertical
							Vnouveau = (2.0 * horizontal + vertical) / 4.0;
						}
						else if (!isVerticalEdge && isHorizontalEdge) { //est un interface conducteur/dielectrique horizontal
							Vnouveau = (2.0 * vertical + horizontal) / 4.0;
						}
						else if (isVerticalEdge && isHorizontalEdge) { // est un interface dielectrique/coin conducteur
							Vnouveau = (vertical + horizontal) / 2.0;
						}
						else if (!isVerticalEdge && !isHorizontalEdge) { //condition de dirichlet
							Vnouveau = (vertical + horizontal) / 4.0;
						}
					
						//voir si difference est plus grande que le seuil
						if (abs(Vnouveau - potentials[row][col].getValue()) > Seuil)
							Convergence = false;

						setpot(row, col, Vnouveau);
					}				
				}
			}
	} 
}
double Jfet::findFieldIntensity(const int& i, const int& j)
{
	double deltaX = 0.06 * (10 ^ -6); //0.06 um
	double deltaV = getpot(i + 1, j + 1).getValue() - getpot(i, j).getValue();
	double fieldIntensity = -(deltaV / deltaX);
	return fieldIntensity;
}

double Jfet::findCurrentDensity(const int& i, const int& j)
{
	double fieldIntensity = findFieldIntensity(i, j);
	double resistivity = 0.09 * (10 ^ -2); // resistivite, ohm / metre
	double conductivity = 1.0 / resistivity; // conductivite, siemen / metre
	double currentDensity = conductivity * fieldIntensity;
	return currentDensity;
}

double Jfet::findCurrent()
{
	double resistivity = 0.09 * (10 ^ -2); // resistivite, ohm / metre
	double conductivity = 1.0 / resistivity; // conductivite, siemen / metre
	double depth = 30.0 * (10 ^ -6); // profondeur, metre
	double deltaY = 0.06 * (10 ^ -6); // hauteur, metre
	double sumPot = 0.0; // somme des differences de potentiels

	for (int row = 4; row < 7; ++row) {
		double left, right = 0.0;
		left = (getpot(row, 7).getValue() + getpot(row + 1, 7).getValue()) / 2.0;
		right = (getpot(row, 8).getValue() + getpot(row + 1, 8).getValue()) / 2.0;
		sumPot += (left - right) * (10 ^ -3); //diff pot en Volt
	}
	cout << "resistivity : " << resistivity << endl;
	cout << "cond : " << conductivity << ". \nprofondeur : " << depth << ". \nsumpot : " << sumPot << endl;
	double current = -(conductivity * depth * sumPot);
	return current;
}

void Jfet::printpots() 
{
	//cout << getpot(0, 1).getValue() << endl;
	
	cout << setprecision(4) << fixed;
	cout << "Tableau des potentiels du JFET (valeurs en mV) \n\n";

	int blank = 9; //variable utilise pour espacement

	for (int i = 0; i < getsize_x(); ++i) { // affiche seulement l'interieur (pas la frontiere)
		for (int j = 0; j < getsize_y(); ++j) { //affiche seulement l'interieur 
			if (getpot(i, j).getValue() > 100.0 ) {
				cout << setw(blank) << getpot(i, j).getValue();
			}
			else {
				cout << setw(blank) << getpot(i, j).getValue();
			}
		}
		cout << "\n\n";
	}
}