#include "aquarium.h"

Aquarium::Aquarium()
{
}

void Aquarium::run()
{
/*	for (auto i : organisms)
		i->run();*/
	for (size_t i = 0; i < organisms.size(); ++i)
		organisms[i]->run();
}

void Aquarium::update()
{
	for (auto i : organisms)
		i->update();
}

void Aquarium::draw()
{
	//for (auto i : organisms)
		//i->draw();
		//window->draw(i->sprite);
}

