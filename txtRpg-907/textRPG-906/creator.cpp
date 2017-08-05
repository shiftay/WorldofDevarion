#include "Creator.h"


Player Creator::creator()
{
	string name;
	string jobType;
	int stats[5];
	vector<string> choices;

	MSConsole::Output("What is your name? ");
	getline(cin, name);
	jobType = jobChoice();
	choices = passivesAndSkills(jobType);
	statCalculator(stats, jobType);

	return Player(name, jobType, stats, choices);

}

string Creator::jobChoice()
{
	string choice;
	int input;

	MSConsole::Output("\n(1) Barbarian -- Unruly and devestatingly strong.\n");
	MSConsole::Output("                 You are the one who strikes hard\n");
	MSConsole::Output("                 and care not about the finesse.\n");
	MSConsole::Output("(2) Wizard --   Master of the Arcane, ruler of the\n");
	MSConsole::Output("                Elements. You are the silencer of\n");
	MSConsole::Output("                the heretics.\n");
	MSConsole::Output("(3) Rogue --    Deep in the darkness, past the\n");
	MSConsole::Output("                horrors in the shadows. That is\n");
	MSConsole::Output("                where you come from.\n");
	MSConsole::Output("(4) Paladin --  From the heavens you were sent\n");
	MSConsole::Output("                to protect the entirety of\n");
	MSConsole::Output("                creation itself.\n");


	do{
		// lis them based on number
		MSConsole::Output("Which class would you like? ");
		cin >> input;
		cin.ignore();
		switch (input)
		{
		case 1:
			choice = "Barbarian";
			break;
		case 2:
			choice = "Wizard";
			break;
		case 3:
			choice = "Rogue";
			break;
		case 4:
			choice = "Paladin";
			break;
		default:
			MSConsole::Output("Invalid Choice");
			break;
		}

	} while (!areYouSure());

	return choice;
}

vector<string> Creator::passivesAndSkills(string& jobVal)
{
	int choices = 1;
	int input;
	vector<string> passives;

	MSConsole::Output("\n As a bonus you get a single passive, think wisely\n");
	MSConsole::Output("for it will help you on your journey:\n");
	MSConsole::Output("(1)Expert Cooking -- Consuming Food has a chance of doing\n");
	MSConsole::Output("                     double the effect\n");
	MSConsole::Output("(2)Melee Expertise -- Gives a 2% Critical Chance bonus\n");
	MSConsole::Output("(3)Mentalism -- Gives +5 flat Intellect\n");
	MSConsole::Output("(4)Iron Heart -- Base Armor increased by 5\n\n");
	 
	do{
		MSConsole::Output("Which passive would you like? ");
		cin >> input;
		switch (input)
		{
		case 1:
			passives.push_back("1");
			choices--;
			break;
		case 2:
			passives.push_back("2");
			choices--;
			break;
		case 3:
			passives.push_back("3");
			choices--;
			break;
		case 4:
			passives.push_back("4");
			choices--;
			break;
		default:
			MSConsole::Output("Invalid choice\n");
			break;
		}
	} while (choices != 0);

	choices = 1;

	if (jobVal == "Wizard")
	{
		MSConsole::Output("As a Wizard choose your tool of the elements: \n");
		MSConsole::Output("(0) " + intSpells[0] + "-- Shoots a single ball of a fire at a target.\n");
		MSConsole::Output("(1) " + intSpells[1] + "-- Explode with raw power, damaging all targets.\n");
		MSConsole::Output("(2) " + intSpells[2] + "-- Ice shards explode forward damaging two targets.\n");
		MSConsole::Output("(3) " + intSpells[3] + "-- Lightning shoots out of your hand randomly towards targets.\n");
		do{
			MSConsole::Output("Which skill would you like? ");
			cin >> input;
			switch (input)
			{
			case 0:
				if (areYouSure())
				{
					passives.push_back(intSpells[0]);
					choices--;
					break;
				}
				else
					break;
			case 1:
				if (areYouSure())
				{
					passives.push_back(intSpells[1]);
					choices--;
					break;
				}
				else
					break;
			case 2:
				if (areYouSure())
				{
					passives.push_back(intSpells[2]);
					choices--;
					break;
				}
				else
					break;
			case 3:
				if (areYouSure())
				{
					passives.push_back(intSpells[3]);
					choices--;
					break;
				}
				else
					break;
			default:
				MSConsole::Output("invalid selection\n");
				break;
			}
		}while(choices != 0);
	}
	else if (jobVal == "Paladin")
	{
		MSConsole::Output("As a paladin you must choose your tool of your faith: \n");
		MSConsole::Output("(0) " + faithSpells[0] + "-- Rips into the veins of a target to remove poison\n");
		MSConsole::Output("(1) " + faithSpells[1] + "-- Calls the creatures of heaven down to heal a target\n");
		MSConsole::Output("(2) " + faithSpells[2] + "-- Brief flash of light, healing multiple targets.\n");
		MSConsole::Output("(3) " + faithSpells[3] + "-- Devote be the one who controls the armor of all friends.\n");
		do{
			MSConsole::Output("Which skill would you like? ");
			cin >> input;
			switch (input)
			{
			case 0:
				if (areYouSure())
				{
					passives.push_back(faithSpells[0]);
					choices--;
					break;
				}
				else
					break;
			case 1:
				if (areYouSure())
				{
					passives.push_back(faithSpells[1]);
					choices--;
					break;
				}
				else
					break;
			case 2:
				if (areYouSure())
				{
					passives.push_back(faithSpells[2]);
					choices--;
					break;
				}
				else
					break;
			case 3:
				if (areYouSure())
				{
					passives.push_back(faithSpells[3]);
					choices--;
					break;
				}
				else
					break;
			default:
				MSConsole::Output("invalid selection\n");
				break;
			}
		}while(choices != 0);
	}


	return passives;

}

bool Creator::areYouSure()
{
	string input;
	cout << "Are you okay with this decision? (yes/no) ";
	cin >> input;
	input = StringUtil::stringToUpper(input);
	if (input == "YES")
	{
		return true;
	}
	else
		return false;
}

void Creator::statCalculator(int intVal[], string& jobVal)
{
	srand(time(0));

	int remaining = 5;
	int input;
	int amount = 0;

	// intro all stats
	MSConsole::Output("\nIn this game a lot of your damage, and survivability\n");
	MSConsole::Output("is based off of your base stats, just as much as your\n");
	MSConsole::Output("gear. \n\n");
	MSConsole::Output("STRENGTH -- Controls Melee Attack Damage\n");
	MSConsole::Output("DEXTERITY -- Controls Critical Chance and Evasion\n");
	MSConsole::Output("INTELLECT -- Controls Mana pool and Spell Damage\n");
	MSConsole::Output("CONSTITUION -- Controls base health and armor.\n");
	MSConsole::Output("FAITH -- Controls healing effectiveness\n");

	int str, dex, intell, faith, cons;

	do{
		remaining = 5;
		// calculate random stat sheet.
		if (jobVal == "Barbarian")
		{
			//str + con weighted
			//dex 3rd highest
			//intel.faith really low 
			str = rand() % 6 + 7; // 7-12
			cons = rand() % 6 + 5; // 5-10
			dex = rand() % 3 + 5; // 5-7
			intell = rand() % 3 + 1; // 1-3 
			faith = rand() % 3 + 1; // 1-3
		}
		else if (jobVal == "Wizard")
		{
			//intell highly weighted
			//dex + con decent
			//str faith super low
			str = rand() % 3 + 1; // 1-3
			cons = rand() % 3 + 5; // 5-7
			dex = rand() % 3 + 5; // 5-7
			intell = 15; //10 - 15  
			faith = rand() % 3 + 1; // 1-3
		}
		else if (jobVal == "Rogue")
		{
			// dex str high
			// con mediocre
			// int + faith super low
			str = rand() % 6 + 5;
			cons = rand() % 3 + 5;
			dex = rand() % 6 + 10;
			intell = rand() % 3 + 1;
			faith = rand() % 3 + 1;
		}
		else if (jobVal == "Paladin")
		{
			// str con faith all good
			// int dex super low.
			str = rand() % 6 + 5;
			cons = rand() % 6 + 5;
			dex = rand() % 3 + 1;
			intell = rand() % 3 + 1;
			faith = rand() % 6 + 5;
		}

		do{
			MSConsole::Output("\nYour current stats:\n");
			MSConsole::Output("(0)STRENGTH: " + StringUtil::ToString_i(str) + "\t(1)DEXTERITY: " + StringUtil::ToString_i(dex));
			MSConsole::Output("\n(2)INTELLECT: " + StringUtil::ToString_i(intell) + "\t(3)FAITH: " + StringUtil::ToString_i(faith));
			MSConsole::Output("\n(4)CONSTITUTION: " + StringUtil::ToString_i(cons));
			//
			MSConsole::Output("\n\nYou have " + StringUtil::ToString_i(remaining) + " points to be placed.\n");

			MSConsole::Output("Where would you like to place your points? ");
			cin >> input;

			switch (input)
			{
			case 0:
				amount = howMany(input, remaining);
				str += amount;
				remaining -= amount;
				break;
			case 1:
				amount = howMany(input, remaining);
				dex += amount;
				remaining -= amount;
				break;
			case 2:
				amount = howMany(input, remaining);
				intell += amount;
				remaining -= amount;
				break;
			case 3:
				amount = howMany(input, remaining);
				faith += amount;
				remaining -= amount;
				break;
			case 4:
				amount = howMany(input, remaining);
				cons += amount;
				remaining -= amount;
				break;
			default:
				MSConsole::Output("Invalid input");
			}

			// SWITCH BASED ON INPUT
			// PLACE STAT IN SAID AREA
			// UPDATE REMAINING
			// DO WHILE REMAINING > 0
		} while (remaining > 0);

	} while (!areYouSure());

	intVal[0] = str;
	intVal[1] = dex;
	intVal[2] = intell;
	intVal[3] = cons;
	intVal[4] = faith;
}

int Creator::howMany(int input, int remaining)
{
	bool correctAmount = false;
	int amount;
	do{
		MSConsole::Output("How many would you like to place within " + stats[input] + "? ");
		cin >> amount;

		if (amount > 0 && amount <= remaining)
			return amount;
		else
			MSConsole::Output("Incorrect amount\n");
	} while (!correctAmount);
}

Player Creator::follower()
{
	string name;
	string job_;
	
	cin.ignore();

	MSConsole::Output("What is your name? ");
	name = MSConsole::GetKeyboardInput_str();

	job_ = jobChoice();

	return Player(name, job_, true);
}