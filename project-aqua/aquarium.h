#pragma once
#include "vector"
#include "Organism.h"
//class Organism;
class Aquarium
{
public:
	Aquarium();
	int width;
	int height;

	std::vector<Organism*> organisms;
	void run(); // ��������� ����� run ���� ���������� ���������
	void draw();
	void update();
};