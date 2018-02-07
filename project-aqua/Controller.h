#pragma once
#include "SFML\Graphics.hpp"
#include "aquarium.h"

class Controller
{
	int tic = 0;
	sf::RenderWindow* window;
	Aquarium aquarium;
	sf::Texture back_texture;
	sf::Sprite background;
public:
	Controller();
	void colonisation(int plankton_, int fish_, int shark_);
	Aquarium* getAquarium();

	void init();
	void run();
	void update();
	void draw();
};

