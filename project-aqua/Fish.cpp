#include "Fish.h"

Fish::Fish()
{
	age = 0;
	int xpos = rand() % 760 + 20;
	this->sprite.setPosition(xpos, xpos%550);

	fish_texture.loadFromFile("fish.png");
	this->sprite.setTexture(fish_texture);
	//this->sprite.setTextureRect(sf::IntRect(5, 5, 43, 43));
	this->sprite.setOrigin(fish_texture.getSize().x / 2, fish_texture.getSize().y / 2);
	this->sprite.setScale(0.25, 0.25);

	int a = rand() % 360;
	this->direction.x = cos(a * 3.14 / 180);
	this->direction.y = sin(a * 3.14 / 180);
}

void Fish::run()
{
	if (age > bioparametres.fish_time || hunger_time > bioparametres.fish_hunger_time)
	{
		death();
		return;
	}
	reproduction();

	float planktonDir = findPlankton();
	if (planktonDir != 0 && age > 15 && eaten_plank < 2)
	{
		this->direction.x = cos(planktonDir * 3.14 / 180);
		this->direction.y = sin(planktonDir * 3.14 / 180);
	}
	else if (eaten_plank >= 2)
	{
		doesnt_want_eat++;
		if (doesnt_want_eat == 200) { eaten_plank = 0; doesnt_want_eat = 0; }
	}
	
	if (this->sprite.getPosition().x > 800 - 20 || this->sprite.getPosition().y > 600 - 20 ||
		this->sprite.getPosition().x < 5 || this->sprite.getPosition().y < 5)
	{
		this->direction.x = this->direction.x * (-1);
		this->direction.y = this->direction.y * (-1);
	}

	this->sprite.setPosition(this->sprite.getPosition().x + (this->direction.x)*bioparametres.fish_speed/speed_skale, this->sprite.getPosition().y + (this->direction.y)*bioparametres.fish_speed/speed_skale);
	age++;
	hunger_time++;
}

void Fish::update()
{
	double a = rand() % (radius - (-radius) + 1) + (-radius);

	double pi = 3.14;
	double new_dir;
	new_dir = (a * (pi / 180));

	float alpha = abs(atan(float(this->direction.y / this->direction.x)));

	if (this->direction.x > 0 && this->direction.y > 0)
	{
		this->direction.x = cos(alpha - new_dir); // +
		this->direction.y = sin(alpha - new_dir); // +
	}
	else if (this->direction.x < 0 && this->direction.y > 0)
	{
		this->direction.x = -cos(alpha + new_dir); // - 
		this->direction.y = sin(alpha + new_dir); // +
	}
	else if (this->direction.x > 0 && this->direction.y < 0)
	{
		this->direction.x = cos(alpha + new_dir); //
		this->direction.y = -sin(alpha + new_dir); //
	}
	else if (this->direction.x < 0 && this->direction.y < 0)
	{
		this->direction.x = -cos(alpha - new_dir); //
		this->direction.y = -sin(alpha - new_dir); //
	}
	//this->run();
	this->sprite.setPosition(this->sprite.getPosition().x + this->direction.x * bioparametres.fish_speed/speed_skale, this->sprite.getPosition().y + this->direction.y * bioparametres.fish_speed/speed_skale);
}

void Fish::reproduction()
{
	if (age % bioparametres.fish_reproduction_time == 0 && age > 0)
	{
		//std::cout << bioparametres.plankton_reproduction_time << std::endl;
		Fish* newFish = new Fish();
		newFish->setOrganisms(organisms);
		newFish->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
		organisms->push_back(newFish);
	}
}

void Fish::death()
{
	auto pos = std::find(organisms->begin(), organisms->end(), this);
	if (pos != organisms->end()) organisms->erase(pos);
	delete this;
}

void Fish::setOrganisms(std::vector<Organism*>* organisms_)
{
	organisms = organisms_;
}

float Fish::findPlankton()
{
	int nearPlankton = 1500;
	for (auto i = organisms->begin(); i != organisms->end(); ++i)
		if ((*i)->getType() == 0) {
			{
				sf::Vector2f planktonPos = (*i)->sprite.getPosition();
				if (nearPlankton > sqrt(pow((*i)->sprite.getPosition().x - sprite.getPosition().x, 2) + pow((*i)->sprite.getPosition().y - sprite.getPosition().y, 2)))
				{
					nearPlankton = sqrt(pow((*i)->sprite.getPosition().x - sprite.getPosition().x, 2) + pow((*i)->sprite.getPosition().y - sprite.getPosition().y, 2));
					target = *i;
				}
			}
		}

	if (nearPlankton > bioparametres.fish_vision)
	{
		return 0;
	}
	if (nearPlankton < 5)
	{
		std::cout << "eat\n";
		target->death();
		hunger_time = 0;
		eaten_plank++;
		return 0;
	}
	else
	{
		sf::Vector2f plankton = target->sprite.getPosition();
		if (plankton.x >= sprite.getPosition().x)
		{
			if (plankton.y < sprite.getPosition().y)
			{
				return -atan(abs(plankton.y - sprite.getPosition().y) / (plankton.x - sprite.getPosition().x))*180 / 3.14;
			}
			return atan(abs(plankton.y - sprite.getPosition().y) / (plankton.x - sprite.getPosition().x))*180 / 3.14;
		}
		if (plankton.x < sprite.getPosition().x)
		{
			if (plankton.y < sprite.getPosition().y)
			{
				return 180 + atan(abs(plankton.y - sprite.getPosition().y) / abs(plankton.x - sprite.getPosition().x))*180 / 3.14;
			}
			return 180 - atan(abs(plankton.y - sprite.getPosition().y) / abs(plankton.x - sprite.getPosition().x))*180 / 3.14;
		}
	}
}

int Fish::getType()
{
	return 1;
}
