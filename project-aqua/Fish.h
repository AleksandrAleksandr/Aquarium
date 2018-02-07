#pragma once
#include "Organism.h"

class Fish : public Organism
{
	int hunger_time = 0;
	Organism * target;
	int eaten_plank;
	int doesnt_want_eat = 0;
public:
	Fish();
	virtual void reproduction();
	virtual void death();
	virtual void run();
	virtual void update();
	virtual int getType();
	std::vector<Organism*>* organisms;
	void setOrganisms(std::vector<Organism*>* organisms_);
	float findPlankton();
};

