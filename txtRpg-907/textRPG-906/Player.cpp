#include "Player.h"
#include "Creator.h"

Player::Player()
{
	name = "TEST CTOR";
	job_ = "Wizard";


}
//used exclusively for setting up a follower
Player::Player(const string nameV, const string jobV, bool follower)
{
	name = nameV;
	job_ = jobV;
	this->follower = follower;

	GoldAmount = 0;
	// SET MOST BASE STATS
	if (jobV == "Barbarian")
	{
		strength = 25; // 7-12
		constitution = 25; // 5-10
		dexterity = 10; // 5-7
		intellect = 10; // 1-3 
		faith = 10; // 1-3
	}
	else if (jobV == "Wizard")
	{
		strength = 6; // 1-3
		constitution = 14; // 5-7
		dexterity = 14; // 5-7
		intellect = 30; // 10 - 15 
		faith = 6; // 1-3
		spells.push_back(intSpells[rand() % NUM_SPELLS]);
	}
	else if (jobV == "Rogue")
	{
		strength = 15;
		constitution = 10;
		dexterity = 25;
		intellect = 6;
		faith = 2;
	}
	else if (jobV == "Paladin")
	{
		strength = 20;
		constitution = 25;
		dexterity = 8;
		intellect = 8;
		faith = 20;
		spells.push_back(faithSpells[rand() % NUM_SPELLS]);
	}

	cooking = false;
	if (dexterity > strength)
		baseDamage = dexterity;
	else
		baseDamage = strength;
	armor = constitution / 2;

	critChance = 25;
	evasion = 20;
	
	max_health = 50 + constitution * 10;
	current_health = max_health;
}

Player::Player(const string nameV, const string jobV, int stats[], vector<string> passives)
{
	name = nameV;
	job_ = jobV;

	strength = stats[0];
	dexterity = stats[1];
	intellect = stats[2];
	constitution = stats[3];
	faith = stats[4];

	GoldAmount = 0;
	cooking = false;

	// starting values
	max_health = 50 + constitution * 10;
	
	level = 1;
	currentXP = 0;
	maxXP = 750;
	if (dexterity > strength)
		baseDamage = dexterity;
	else
		baseDamage = strength;
	armor = constitution / 2;

	if (strength >= 10)
		baseDamage += 2;

	if (constitution >= 15)
	{
		max_health += 10;
		armor += 1;
	}

	if (dexterity >= 10)
	{
		critChance = 10;
		evasion = 10;
	}
	else
	{
		critChance = 0;
		evasion = 0;
	}

	switch (StringUtil::StringToInteger(passives[0]))
	{
	case 1:
		cooking = true;
		break;
	case 2:
		critChance += 2;
		break;
	case 3:
		intellect += 5;
		break;
	case 4:
		armor += 5;
		break;
	}

	if (jobV == "Paladin" || jobV == "Wizard")
		spells.push_back(passives[1]);


	current_health = max_health;
	follower = false;

	inventory.equipItem(new Weapon());

}

void Player::checkStats()
{
	MSConsole::Output(name + "\t\t" + StringUtil::ToString_i(current_health) + " / " + StringUtil::ToString_i(max_health) + "HP");
	MSConsole::Output("\t" + StringUtil::ToString_i(current_mana) + " / " + StringUtil::ToString_i(max_mana) + "MP");
	MSConsole::Output("\n"+ job_ +"\t\t" + StringUtil::ToString_i(currentXP)+ " / " +StringUtil::ToString_i(maxXP) + "XP");
	MSConsole::Output("\n\n");
	MSConsole::Output("Your current stats:\n");
	MSConsole::Output("STRENGTH: "+ StringUtil::ToString_i(strength) + "\tDEXTERITY: " + StringUtil::ToString_i(dexterity));
	MSConsole::Output("\nINTELLECT: " + StringUtil::ToString_i(intellect) +"\tFAITH: " + StringUtil::ToString_i(faith));
	MSConsole::Output("\nCONSTITUTION: " + StringUtil::ToString_i(constitution) + "\n");
}

int Player::meleeAttack(Enemy& nme)
{
	// need some way of checking weapon
	if(follower)
	{
		nme.isDamaged((((baseDamage + 6) * (1 + strength / 100)) * (1 - nme.Armor() / 100)));
		return (((baseDamage + 6) * (1 + strength / 100)) * (1 - nme.Armor() / 100));
	}

	if (isCrit())
	{
		nme.isDamaged((((baseDamage + inventory.attackBonus()) * (1 + strength / 100)) * (1 - nme.Armor() / 100)) * 2);
		return (((baseDamage + inventory.attackBonus()) * (1 + strength / 100)) * (1 - nme.Armor() / 100)) * 2;
	}
	else
	{
		nme.isDamaged(((baseDamage + inventory.attackBonus()) * (1 + strength / 100)) * (1 - nme.Armor() / 100));
		return ((baseDamage + inventory.attackBonus()) * (1 + strength / 100)) * (1 - nme.Armor() / 100);
	}
}

bool Player::isCrit()
{
	srand(time(0));

	int random = rand() % 100 + 1;

	if (random > critChance)
		return false;
	else
		return true;
}



void Player::CombatChoice(vector<Enemy*> targets, vector<Player>& party)
{
	int input;
	MSConsole::Output("1. Melee Attack\n");
	MSConsole::Output("2. Cast Spell\n");
	MSConsole::Output("Your choice: ");
	cin >> input;

	switch (input)
	{
	case 1:
		MSConsole::Output("Which enemy do you want to attack: ");
		
		cin >> input;
		if (input >= targets.size())
			input = targets.size() - 1;

		MSConsole::Output("You do " + StringUtil::ToString_i(meleeAttack(*targets[input])) + " points of damage.\n");
		break;
	case 2:
		if(job_ == "Paladin")
		{
			for(int i=0; i < party.size(); i++)
			{
				MSConsole::Output(StringUtil::ToString_i(i) + "\t" + party[i].Name() + "\t" + StringUtil::ToString_i(party[i].CurrentHealth()) + " / " + StringUtil::ToString_i(party[i].MaxHealth())+ "HP\n");
			}
			MSConsole::Output("Which player do you want to support: ");
			cin >> input;
			if (input >= party.size())
				input = party.size() - 1;
			castSpell(party, input);
		}
		else if(job_ == "Wizard")
		{
			MSConsole::Output("Which enemy do you want to attack: ");
			cin >> input;
			if (input >= targets.size())
				input = targets.size() - 1;
			castSpell(targets, input);

		}
		else
		{
			MSConsole::Output("You can not cast spells.\n");
		}
		break;
	default:
		MSConsole::Output("***INVALID CHOICE***\n");
	}

}
void Player::reFill()
{
	current_health = max_health;
}

//party is for if the follower is a paladin.
void Player::followerMove(vector<Enemy*> targets, vector<Player>& party)
{
	int randomNum;
	int healTarget = rand() % party.size();
	int atkTarget = rand() % targets.size();
	if (job_ == "Paladin" || job_ == "Wizard")
		randomNum = rand() % 2;
	else
		randomNum = 0;

	if (follower)
	{
		switch (randomNum)
		{
		case 0:
			MSConsole::Output(Name() + " does " + StringUtil::ToString_i(meleeAttack(*targets[atkTarget])) + " points of damage\n");
			break;
		case 1:
			if (job_ == "Paladin")
				castSpell(party, healTarget);
			else if (job_ == "Wizard")
				castSpell(targets, atkTarget);

			break;
		}
	}
	else
		return;
}

void Player::useItem(Item* item)
{
	MSConsole::Output("You use a " + item->getType() + " " + item->getName() + " on " + Name() + " healing for 50\n");
	isHealed(50);
}

bool Player::isDead()
{
	if(current_health <= 0)
		return true;
	else
		return false;
}

void Player::isHealed(const int newVal)
{
	current_health += newVal;
	
	if(current_health > max_health)
		current_health = max_health;

}

// paladin heals etc...
void Player::castSpell(vector<Player>& teammate, int target)
{
	int holder;

	for (int i = 0; i < NUM_SPELLS; i++)
	{
		if (spells[0] == faithSpells[i])
		{
			holder = i;
			break;
		}
	}

	switch (holder)
	{
	case 0:
		//cure
		teammate[target].isHealed(50);
		MSConsole::Output(Name() + " casts " + spells[0] + " at " + teammate[target].Name() + " healing for 50 points.\n");
		break;
	case 1:
		//bastionoflight
		teammate[target].isHealed((3+Faith()/100) * 25);
		MSConsole::Output(Name() + " casts " + spells[0] + " at " + teammate[target].Name() + " healing for" + StringUtil::ToString_i((3 + Faith() / 100) * 25) + "points.\n");
		break;
	case 2:
		//aoe heal
		MSConsole::Output(Name()+ " casts " + spells[0] + " healing everyone for 25 points.\n");
		for(int i = 0; i < teammate.size(); i++)
			teammate[i].isHealed(25);
		break;
	case 3:
		MSConsole::Output(Name() + " casts " + spells[0] + " healing everyone for " + StringUtil::ToString_i((3 + Faith() / 100) * 10) + "points.\n");
		for (int i = 0; i < teammate.size(); i++)
			teammate[i].isHealed((3 + Faith()/100) * 10);
		//devotionaura
		break;
	default:
		break;
	}

}

//damage spells
void Player::castSpell(vector<Enemy*> nme, int target)
{
	int holder;

	for (int i = 0; i < NUM_SPELLS; i++)
	{
		if (spells[0] == intSpells[i])
			holder = i;
	}

	switch (holder)
	{
	case 0:
		nme[target]->isDamaged(50); // INT * 
		MSConsole::Output(Name() + " casts " + spells[0] + " at " + nme[target]->Name() + "doing 50 points of damage.\n");
		break;
	case 1:
		for (int i = 0; i < nme.size(); i++)
		{
			nme[i]->isDamaged(intellect * 5);
			MSConsole::Output(Name() + " casts " + spells[0] + " at " + nme[i]->Name() + " doing " + StringUtil::ToString_i(intellect * 5) + "\n");
		}
		//arcaneexplosion
		break;
	case 2:
		for (int i = 0; i < nme.size(); i++)
		{
			nme[i]->isDamaged(25);
			MSConsole::Output(Name() + " casts " + spells[0] + " at " + nme[i]->Name() + " doing " + StringUtil::ToString_i(25) + "\n");
		}
		//icenova
		break;
	case 3:

		if (nme.size() == 1)
		{
			nme[0]->isDamaged(intellect * 4);
			MSConsole::Output(Name() + " casts " + spells[0] + " at " + nme[0]->Name() + " doing " + StringUtil::ToString_i(intellect * 4) + "\n");
		}
		else
		{
			for (int i = 0; i < nme.size() - 1; i++)
			{
				nme[i]->isDamaged(intellect * 20);
				MSConsole::Output(Name() + " casts " + spells[0] + " at " + nme[i]->Name() + " doing " + StringUtil::ToString_i(intellect * 4) + "\n");
			}
		}
		//chainlightning
		break;
	default:
		break;
	}
}

void Player::levelUp()
{
	if(currentXP >= maxXP)
	{
		// logic for leveling up
		level++;
		MSConsole::Output("CONGRATULATIONS YOU LEVELED UP TO " + StringUtil::ToString_i(level) + "\n\n");
		
		currentXP -= maxXP;

		maxXP = level * 750;

		// STAT INCREASE
		// + 2 all stats
		strength += 2;
		constitution += 2;
		intellect += 2;
		faith += 2;
		dexterity += 2;

		checkStats();
		system("pause");
	}
	else
		return;
}