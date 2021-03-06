#include "JFET.h"

using namespace std;

int main()
{
	int size_x = 13;
	int size_y = 17;
	Jfet jfet = Jfet(size_x, size_y); // cree une matrice de potentiels de taille 14 x 18

	double potentials_init[13][17] =
	{
	 { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -150 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -150 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -150 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -150 } };
	

	
	//remplir le tableau des potentiels avec les valeurs initiales (JFET a l'etat initial)
	for( int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++)
			jfet.setpot(i, j, potentials_init[i][j]); 

	jfet.setPotsModif();

	cout << "\n\n";
	double Seuil = 0.01;
	int MaxItera = 10000;

	jfet.finiteDifferenceMethod(Seuil, MaxItera);
	jfet.printpots();
	cout << "densite : " << jfet.findCurrentDensity(0,1) << endl;
	cout << "courant : " << jfet.findCurrent() << endl;
	return 0;
}