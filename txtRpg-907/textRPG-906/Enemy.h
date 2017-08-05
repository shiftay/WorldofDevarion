#pragma once
#include "Actor.h"
#include "Player.h"
// might need these for drops
#include "Weapon.h"
#include "Armor.h"

class Player;

const string type[5] = { "Dragonkin", "Wolvren", "Skeleton", "Orc", "Humanoid" };
const string fightStyle[3] = { "Archer", "Mage", "Warrior" };
const string nmeSpells[4] = { "Fireball", "FrostBolt", "ArcLightning", "PoisonCloud" };
const string MiniBoss[3] = { "Necromancer", "Chieftain", "BeastMaster" };

class Enemy : public Actor
{
public:
	//int parameter is player's level.
	Enemy();
	Enemy(string, int); // creates a random enemy, based on it's type. xp based on playerlevel.
	void displayStats();
	void isDamaged(const int newVal) { current_health -= newVal; };
	inline const int giveXP() const { return xpGiven; }
	
	bool isDead();
	void Attack(vector<Player>&);

protected:
	string type;
	string job;
	int xpGiven;

	bool isBoss; // might not need
};