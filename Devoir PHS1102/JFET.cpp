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

void Jfet::setpot(const double& pot, const int& x, const int& y) const 
{
	potentials[x][y].setValue(pot);
}

/*
void Jfet::fillpots(const double** &list) 
{
	for (int i = 0; i < getsize_x(); ++i) {
		for (int j = 0; j < getsize_y(); ++j) {
			double val = list[i][j];
			setpot(val, i, j);
		}
	}
			
}*/

void Jfet::initializePots()
{
	for (int toprow = 1; toprow <= 3; toprow++) // grille du haut
		for (int topcol = 7; topcol <= 9; topcol++) {
			potentials[toprow][topcol].setModif(false);
		}

	for (int bottomrow = 11; bottomrow <= 13; bottomrow++) // grille du base
		for (int bottomcol = 7; bottomcol <= 9; bottomcol++) {
			potentials[bottomrow][bottomcol].setModif(false); 
	}
}

void Jfet::finiteDifferenceMethod(const int& interations, const double& convergence, const double& maxIterations)
{
	for (int i = 1; i < getsize_x() - 2; ++i) {
		for (int j = 1; j < getsize_y() - 2; ++j) {
			if (getpot(i, j).isModif()) //le potentiel doit etre modifiable

				double v0, v1, v2, v3, v4 = 0; //potentiels autour du point recherche. 
										   //v0 = potentiel recherche. v1 = pot. gauche, v2 = pot. haut, v3 = bas, v4 = droite
				
		}
	}
}

void Jfet::printpots() 
{
	cout << setprecision(2) << fixed;
	cout << "Tableau des potentiels du JFET \n\n";

	int blank = 8; //utilise pour espacement

	for (int i = 0; i < getsize_x() - 0; ++i) { // affiche seulement l'interieur (pas la frontiere)
		for (int j = 0; j < getsize_y() - 0; ++j) { //affiche seulement l'interieur 

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