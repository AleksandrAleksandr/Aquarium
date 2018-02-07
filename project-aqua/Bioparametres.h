#pragma once

struct Bioparametres
{
	//время жизни
	int fish_time = 4000;
	int plankton_time = 1000;
	int shark_time = 6000;
	//скорость;
	int fish_speed = 3;
	int plankton_speed = 1;
	int shark_speed = 4;
	//время жизни без еды
	int fish_hunger_time = 800;
	int plankton_hunger_time = 5;
	int shark_hunger_time = 800;
	//зрение
	int fish_vision = 100;
	int shark_vision = 110;
	//
	int fish_reproduction_time = 1200;
	int plankton_reproduction_time = 400;
	int shark_reproduction_time = 5000;
};