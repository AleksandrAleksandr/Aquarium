#pragma once
#include "Organism.h"

class Shark : public Organism
{
	int hunger_time = 0;
	Organism * target;
public:
	Shark();
	virtual void reproduction();
	virtual void death();
	virtual void run();
	virtual void update();
	virtual int getType();
	std::vector<Organism*>* organisms;
	void setOrganisms(std::vector<Organism*>* organisms_);
	float findFish();
};


