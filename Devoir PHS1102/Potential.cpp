#include "Potential.h"

Potential::Potential()
{
	value = 0;
	modifiable = true;
}

Potential::Potential(const double& val, const bool& modif): value(val), modifiable(modif)
{}

Potential::Potential(const Potential& pot)
{
	value = pot.value;
	modifiable = pot.modifiable;
}

Potential::~Potential()
{}

double Potential::getValue() const
{
	return value;
}

bool Potential::isModif() const
{
	return modifiable;
}

void Potential::setValue(const double& val)
{
	value = val;
}

void Potential::setModif(const bool& modif)
{
	modifiable = modif;
}