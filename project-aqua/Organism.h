#pragma once
#include "SFML\Graphics.hpp"
#include "iostream"
#include "time.h"
#include "cmath"
#include "vector"
#include "Bioparametres.h"

class Plankton;
class Fish;
class Shark;

class Organism
{
protected:
	Bioparametres bioparametres;
	int age;
	sf::Vector2f direction;
	int radius = 25;
	int speed_skale = 2;
	//sf::Sprite plankton_sprite;
	//sf::Sprite fish_sprite;
	sf::Texture plankton_texture;
	sf::Texture fish_texture;
	sf::Texture shark_texture;
public:
	sf::Sprite sprite;
	virtual void run() = 0;   //перемещает организм 
	virtual void update() = 0; 
	virtual void death() = 0;
	virtual void reproduction() = 0;
	virtual int getType() = 0;
	std::vector<Organism*>* organisms;
};

#include "Plankton.h"
#include "Fish.h"
#include "Shark.h"