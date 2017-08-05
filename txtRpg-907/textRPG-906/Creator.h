//
//	Creator - v0.0.1
//Creates player
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Player.h"

const int NUM_SPELLS = 5;

const string intSpells[NUM_SPELLS] = { "Fireball", "ArcaneExplosion", "IceNova", "ChainLightning"};
const string faithSpells[NUM_SPELLS] = { "Cure", "BastionOfLight", "DefiantToTheEnd", "Devotion" };
const string stats[5] = { "Strength", "Dexterity", "Intellect", "Faith", "Constitution" };

class Creator{

public:
	Player creator();
	Player follower();
	static bool areYouSure();

private:
	int howMany(int, int);
	void statCalculator(int*, string&);
	string jobChoice();
	vector<string> passivesAndSkills(string&);
	bool areYouSure(const int&);

};

