#pragma once
#include "Organism.h"

class Plankton : public Organism
{
public:
	Plankton();
	virtual void reproduction();
	virtual void death();
	virtual void run();
	virtual void update();
	virtual int getType();
	std::vector<Organism*>* organisms;
	void setOrganisms(std::vector<Organism*>* organisms_);
};

