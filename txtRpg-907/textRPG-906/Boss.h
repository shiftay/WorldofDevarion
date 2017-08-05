#include "Enemy.h"

class Jacob : public Enemy
{
public:
	Jacob()
	{
		isBoss = true;

		name = "Jacob Warrock";
		type = "Wolvren";

		baseDamage = 19;

		xpGiven = 1500;

		job = "Warrior";

		max_health = 500;
		current_health = max_health;
	}
};


class Sebastian : public Enemy
{
public:
	Sebastian()
	{
		isBoss = true;

		name = "Sebastian DeLouvre";

		type = "Dragon";

		baseDamage = 25;

		xpGiven = 1500;

		job = "Mage";

		max_health = 10000;
		current_health = max_health;
	}
	//MASSIVE AMOUNTS OF HP

};

class Yorick : public Enemy
{
public:
	Yorick()
	{
		isBoss = true;

		name = "Necromancer Yorick";

		type = "Orc";

		baseDamage = 25;

		xpGiven = 1500;

		job = "Mage";

		max_health = 450;
		current_health = max_health;
	}
};

class Grug : public Enemy
{
public:
	Grug()
	{
		isBoss = true;

		name = "Chieftain Grug";

		type = "Orc";

		baseDamage = 25;

		xpGiven = 1500;

		job = "Warrior";
		
		max_health = 700;
		current_health = max_health;
	}
};