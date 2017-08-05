#include "Enemy.h"
#include "Console.h"
#include "stringUtil.h"

Enemy::Enemy()
{
	armor = 15;
}

Enemy::Enemy(string type, int playersLevel)
{
	this->type = type;

	xpGiven = 200 * playersLevel;

	baseDamage = 7 * playersLevel;
	armor = 5 * playersLevel;

	current_health = 100 * playersLevel;
	max_health = current_health;
	
	// randomly set job.
	// need to set spells if it rolls mage.
	job = fightStyle[rand() % 3];

	if (job == "Mage")
	{
		spells.push_back(nmeSpells[rand() % 4]);
	}
	else if (job == "Warrior")
	{
		armor += 5;
	}
	else if (job == "Archer")
	{
		baseDamage += 5;
	}

	isBoss = false;
}


bool Enemy::isDead()
{
	if (CurrentHealth() <= 0)
		return true;
	else
		return false;
}


void Enemy::Attack(vector<Player>& targets)
{
	int randomNum = rand() % targets.size();
	int damage = baseDamage * targets[0].Level();

	if (!isDead())
	{

		if (isBoss && job == "Mage")
		{
			targets[randomNum].isDamaged((damage * 2 * (1 - targets[randomNum].Armor() + targets[randomNum].inventory.armorBonus() / 100)));
			MSConsole::Output(Name() + " attacks, doing " + StringUtil::ToString_i(damage) + " damage to " + targets[randomNum].Name() + "\n");
		}
		else if (isBoss)
		{
			targets[randomNum].isDamaged(damage * (1 - targets[randomNum].Armor() / 100));
			MSConsole::Output(Name() + " attacks, doing " + StringUtil::ToString_i(damage) + " damage to " + targets[randomNum].Name() + "\n");
		}
		else if (job == "Mage")
		{
			targets[randomNum].isDamaged((damage * 2 *(1 - targets[randomNum].Armor() + targets[randomNum].inventory.armorBonus() / 100)));
			MSConsole::Output(type + " " + job + " casts " + spells[0] + " doing " + StringUtil::ToString_i(damage * 2) + " damage to " + targets[randomNum].Name()+ "\n");
		}
		else
		{
			targets[randomNum].isDamaged(damage * (1 - targets[randomNum].Armor() / 100));
			MSConsole::Output(type + " " + job + " attacks, doing " + StringUtil::ToString_i(damage) + " damage to " + targets[randomNum].Name()+ "\n");
		}
	}
	else
		return;
}


void Enemy::displayStats()
{
	// need to display health.
	if (!isBoss)
		MSConsole::Output(type + " " + job + "\t" + StringUtil::ToString_i(CurrentHealth()) + " / " + StringUtil::ToString_i(MaxHealth()) + "HP\n");
	else
		MSConsole::Output(name + "\t" + StringUtil::ToString_i(CurrentHealth()) + " / " + StringUtil::ToString_i(MaxHealth()) + "HP\n");
}