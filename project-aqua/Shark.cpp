#include "Shark.h"

Shark::Shark()
{
	age = 0;
	int xpos = rand() % 760 + 20;
	this->sprite.setPosition(xpos, xpos % 550);

	shark_texture.loadFromFile("shark.png");
	this->sprite.setTexture(shark_texture);
	//this->sprite.setTextureRect(sf::IntRect(5, 5, 43, 43));
	this->sprite.setOrigin(fish_texture.getSize().x / 2, fish_texture.getSize().y / 2);
	this->sprite.setScale(0.15, 0.15);

	int a = rand() % 360;
	this->direction.x = cos(a * 3.14 / 180);
	this->direction.y = sin(a * 3.14 / 180);
}

void Shark::run()
{
	if (age > bioparametres.shark_time || hunger_time > bioparametres.shark_hunger_time)
	{
		death();
		return;
	}
	reproduction();

	float fishDir = findFish();
	if (fishDir != 0)
	{
		this->direction.x = cos(fishDir * 3.14 / 180);
		this->direction.y = sin(fishDir * 3.14 / 180);
	}

	if (this->sprite.getPosition().x > 800 - 20 || this->sprite.getPosition().y > 600 - 20 ||
		this->sprite.getPosition().x < 5 || this->sprite.getPosition().y < 5)
	{
		this->direction.x = this->direction.x * (-1);
		this->direction.y = this->direction.y * (-1);
	}

	this->sprite.setPosition(this->sprite.getPosition().x + (this->direction.x)*bioparametres.shark_speed/speed_skale, this->sprite.getPosition().y + (this->direction.y)*bioparametres.shark_speed/speed_skale);
	age++;
	hunger_time++;
}

void Shark::update()
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
	this->sprite.setPosition(this->sprite.getPosition().x + this->direction.x * bioparametres.shark_speed / speed_skale, this->sprite.getPosition().y + this->direction.y * bioparametres.shark_speed / speed_skale);
}

void Shark::reproduction()
{
	if (age % bioparametres.shark_reproduction_time == 0 && age > 0)
	{
		//std::cout << bioparametres.plankton_reproduction_time << std::endl;
		Shark* newShark = new Shark();
		newShark->setOrganisms(organisms);
		newShark->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
		organisms->push_back(newShark);
	}
}

void Shark::death()
{
	auto pos = std::find(organisms->begin(), organisms->end(), this);
	if (pos != organisms->end()) organisms->erase(pos);
	delete this;
}

void Shark::setOrganisms(std::vector<Organism*>* organisms_)
{
	organisms = organisms_;
}

float Shark::findFish()
{
	int nearFish = 1500;
	for (auto i = organisms->begin(); i != organisms->end(); ++i)
		if ((*i)->getType() == 1) {
			{
				sf::Vector2f fishPos = (*i)->sprite.getPosition();
				if (nearFish > sqrt(pow((*i)->sprite.getPosition().x - sprite.getPosition().x, 2) + pow((*i)->sprite.getPosition().y - sprite.getPosition().y, 2)))
				{
					nearFish = sqrt(pow((*i)->sprite.getPosition().x - sprite.getPosition().x, 2) + pow((*i)->sprite.getPosition().y - sprite.getPosition().y, 2));
					target = *i;
				}
			}
		}

	if (nearFish > bioparametres.shark_vision)
	{
		return 0;
	}
	if (nearFish < 5)
	{
		std::cout << "eatF\n";
		target->death();
		hunger_time = 0;
		return 0;
	}
	else
	{
		sf::Vector2f fish = target->sprite.getPosition();
		if (fish.x >= sprite.getPosition().x)
		{
			if (fish.y < sprite.getPosition().y)
			{
				return -atan(abs(fish.y - sprite.getPosition().y) / (fish.x - sprite.getPosition().x)) * 180 / 3.14;
			}
			return atan(abs(fish.y - sprite.getPosition().y) / (fish.x - sprite.getPosition().x)) * 180 / 3.14;
		}
		if (fish.x < sprite.getPosition().x)
		{
			if (fish.y < sprite.getPosition().y)
			{
				return 180 + atan(abs(fish.y - sprite.getPosition().y) / abs(fish.x - sprite.getPosition().x)) * 180 / 3.14;
			}
			return 180 - atan(abs(fish.y - sprite.getPosition().y) / abs(fish.x - sprite.getPosition().x)) * 180 / 3.14;
		}
	}
}

int Shark::getType()
{
	return 2;
}
