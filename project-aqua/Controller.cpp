#include "Controller.h"



Controller::Controller()
{
	aquarium = Aquarium();
	colonisation(15, 5, 1);
	back_texture.loadFromFile("background2.png");
	background.setTexture(back_texture);
	background.setScale(0.8, 0.8);
}

void Controller::colonisation(int plankton_num, int fish_num, int shark_num)
{
	for (int i = 0; i < plankton_num; i++)
	{
		Plankton* newPlankton = new Plankton();
		newPlankton->setOrganisms(&aquarium.organisms);
		aquarium.organisms.push_back(newPlankton);
	}

	for (int i = 0; i < fish_num; i++)
	{
		Fish* newFish = new Fish();
		newFish->setOrganisms(&aquarium.organisms);
		aquarium.organisms.push_back(newFish);
	}
	for (int i = 0; i < shark_num; i++)
	{
		Shark* newShark = new Shark();
		newShark->setOrganisms(&aquarium.organisms);
		aquarium.organisms.push_back(newShark);
	}
}

Aquarium* Controller::getAquarium()
{
	return &aquarium;
}

void Controller::init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Aquarium");

	while (window->isOpen())
	{
		tic++;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		if (tic == 15 || tic == 30 || tic == 45)
		{
			run();
		}
		else if (tic == 60)
		{
			update();
			tic = 0;
		}
		window->draw(background);
		draw();
		window->display();
	}
}

void Controller::run()
{
	aquarium.run();
}

void Controller::update()
{
	aquarium.update();
}

void Controller::draw()
{
	for (auto i : aquarium.organisms)
		window->draw(i->sprite);
}