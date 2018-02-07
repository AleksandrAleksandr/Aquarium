#include "Plankton.h"

Plankton::Plankton()
{
	age = 0;
	int xpos = rand() % 760 + 20;
	int ypos = rand() % 560 + 20;
	this->sprite.setPosition(xpos, ypos);

	plankton_texture.loadFromFile("plankton.png");
	this->sprite.setTexture(plankton_texture);
	this->sprite.setTextureRect(sf::IntRect(5, 5, 43, 50));
	this->sprite.setScale(0.4, 0.4);

	int a = rand() % 360;
	this->direction.x = cos(a * 3.14 / 180);
	this->direction.y = sin(a * 3.14 / 180);
}

void Plankton::run()
{
	if (age > bioparametres.plankton_time + rand()/50)
	{
		death();
		//std::cout << bioparametres.plankton_time << std::endl;
		return;
	}
	reproduction();
	if (this->sprite.getPosition().x > 800 - 10 || this->sprite.getPosition().y > 600 - 10 ||
		this->sprite.getPosition().x < 1 || this->sprite.getPosition().y < 1)
	{
		this->direction.x = this->direction.x * (-1);
		this->direction.y = this->direction.y * (-1);
	}

	this->sprite.setPosition(this->sprite.getPosition().x + (this->direction.x)*bioparametres.plankton_speed/speed_skale, this->sprite.getPosition().y + (this->direction.y)*bioparametres.plankton_speed/speed_skale);
	age++;
}

void Plankton::update()
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
	this->sprite.setPosition(this->sprite.getPosition().x + this->direction.x * bioparametres.plankton_speed/speed_skale, this->sprite.getPosition().y + this->direction.y * bioparametres.plankton_speed/speed_skale);
}

void Plankton::reproduction()
{
	if (age % bioparametres.plankton_reproduction_time == 0 && age > 0)
	{
		//std::cout << bioparametres.plankton_reproduction_time << std::endl;
		Plankton* newPlankton = new Plankton();
		newPlankton->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
		newPlankton->setOrganisms(organisms);
		organisms->push_back(newPlankton);
	}
}

void Plankton::death()
{
	auto pos = std::find(organisms->begin(), organisms->end(), this);
	if (pos != organisms->end()) organisms->erase(pos);
	delete this;
}

void Plankton::setOrganisms(std::vector<Organism*>* organisms_)
{
	organisms = organisms_;
}

int Plankton::getType()
{
	return 0;
}