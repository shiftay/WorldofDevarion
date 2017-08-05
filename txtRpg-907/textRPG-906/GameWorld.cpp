#include "GameWorld.h"


void GameWorld::Begin()
{
	Creator creator;
	string input;
	int intInput;
	MSConsole::SetTextColor(ConsoleColor::DARKYELLOW);
	Prologue();
	MSConsole::SetTextColor(ConsoleColor::WHITE);
	system("cls");
	MSConsole::Output("Alright let's get into the nitty gritty\n");

	vector<Player> player;
	player.push_back(creator.creator());

	MSConsole::Output("\n\nThe world of Devarion is a harsh and unforgiving place,\n");
	MSConsole::Output("it is a great idea to bring along some followers to help\n");
	MSConsole::Output("you within your quest, would you like any? (yes/no)");
	cin >> input;
	
	if (StringUtil::stringToUpper(input) == "YES")
	{
		MSConsole::Output("You may have up to 2 followers, how many would you like? (1/2) ");
		cin >> intInput;

		for (int i = 0; i < intInput; i++)
			player.push_back(creator.follower());
	}
	else
		MSConsole::Output("I wish you luck in your solo travels, you will need it.\n");

	introtoSebastian(player);
	dragonsBreathInn(player);
}

void GameWorld::introtoSebastian(vector<Player>& player)
{
	system("cls");

	MSConsole::Output("After for walking for what seems like days you\n");
	MSConsole::Output("stumble upon a decrepit looking building with\n");
	MSConsole::Output("a broken sign that reads:\n\n");

	MSConsole::Output("Dragon's Breath Inn\n");
	MSConsole::Output("--We don't serve Trolls--\n\n");

	MSConsole::Output("You push open the door, to hear a roaring fire\n");
	MSConsole::Output("and a bunch of cloaked people huddling in a\n");
	MSConsole::Output("corner together.\n\n");

	MSConsole::Output("You walk up to what seems to be the main bar\n");
	MSConsole::Output("and tap you arm on the edge of the bar and\n");
	MSConsole::Output("a Head pops up from underneath the bar.\n\n");

	system("pause");

	MSConsole::Output("\"Who are you?\" he exclaims.\n\n");

	MSConsole::Output("You tell him your name is " + player[0].Name() + " and\n");
	MSConsole::Output("that you are a " + player[0].Job() + " from the hills of\n");
	MSConsole::Output("the west.\n\n");

	MSConsole::Output("\"West eh... This isn't a place for westerners,\n");
	MSConsole::Output("get out of here.\"\n\n");

	MSConsole::Output("The barkeep turns away from you and begins to\n");
	MSConsole::Output("toy with some papers. He begins to turn back:\n\n");

	MSConsole::Output("\"...Actually, You know what I was being too...\n");
	MSConsole::Output("hasty. I need some help around here.\"\n\n");

	MSConsole::Output("You look around at the cloaked people who are\n");
	MSConsole::Output("turned towards the corner whispering with each\n");
	MSConsole::Output("other.\n\n");

	system("pause");

	MSConsole::Output("\"Not them... I'm sorry I haven't introduced\n");
	MSConsole::Output("myself, I am Sebastian DeLouvre. I'm the \n");
	MSConsole::Output("owner and barkeep at this establisment.\"\n\n");

	MSConsole::Output("\"I need your help with some unruly settlers\n");
	MSConsole::Output("that have recently moved in around here.\n");
	MSConsole::Output("I am willing to pay for your services, and\n");
	MSConsole::Output("in turn I can also sell you any wares you \n");
	MSConsole::Output("might need.\"\n\n");

	MSConsole::Output("You agree to help him, and he arranges some\n");
	MSConsole::Output("papers infront of you:\n\n");

	system("pause");
}

void GameWorld::CombatItems(vector<Player>& p)
{
	int input;
	int choice;

	p[0].inventory.display();
	if (!p[0].inventory.bag.empty())
	{
		MSConsole::Output("Which item would you like to use? ");
		cin >> input;

		if (p[0].inventory.bag[input]->getName() == "Potion")
		{
			for (int i = 0; i < p.size(); i++)
			{
				MSConsole::Output(p[i].Name() + "\t\t" + StringUtil::ToString_i(p[i].CurrentHealth()) + " / " + StringUtil::ToString_i(p[i].MaxHealth()) + " HP\n");
			}
			MSConsole::Output("Who would you like to use it on? ");
			cin >> choice;
			p[choice].useItem(p[0].inventory.bag[input]);
			p[0].inventory.removeItem(p[0].inventory.bag[input]);
		}
		else
			MSConsole::Output("This item has no use currently.\n");
	}

}

void GameWorld::basicCombat(const string type, const int amount, vector<Player>& party)
{
	system("cls");
	int input;

	vector<Enemy*> enemies;
	for (int i = 0; i < amount; i++)
		enemies.push_back(new Enemy(type, party[0].Level()));

	int deadEnemies;

	do{
		deadEnemies = 0;
		for (int i = 0; i < enemies.size(); i++)
		{
			if (!enemies[i]->isDead())
			{
				cout << i << "\t";
				enemies[i]->displayStats();
			}
		}

		MSConsole::Output("\n");
		for (int i = 0; i < party.size(); i++)
		{
			MSConsole::Output(party[i].Name() + "\t\t" + StringUtil::ToString_i(party[i].CurrentHealth()) + " / " + StringUtil::ToString_i(party[i].MaxHealth()) + " HP\n");
		}
		MSConsole::Output("\n");
		MSConsole::Output("What do you do?\n");
		MSConsole::Output("1. Fight\n");
		MSConsole::Output("2. Use Item\n");
		cin >> input;

		switch (input)
		{
		case 1:
			party[0].CombatChoice(enemies, party);
			for (int i = 1; i < party.size(); i++)
			{
				if (!party[i].isDead())
					party[i].followerMove(enemies, party);
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Attack(party);
			}
			break;
		case 2:
			CombatItems(party);
			break;
		default:
			MSConsole::Output("INVALID CHOICE\n");
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->isDead())
				deadEnemies++;
		}
	} while (deadEnemies != amount || party[0].isDead());

	if (party[0].isDead())
	{
		gameOver = true;
	}
	else
	{
		for (int x = 0; x < enemies.size(); x++)
		{
			party[0].gainXP(enemies[x]->giveXP());
		}
		party[0].gainGold(50 * enemies.size());


	}
	MSConsole::SetTextColor(ConsoleColor::RED);
	MSConsole::Output("\nYou have defeated the " + type + "\n");
	MSConsole::SetTextColor(ConsoleColor::WHITE);
	system("pause");
}

void GameWorld::dragonsBreathInn(vector<Player>& player)
{

	int input;
	// main game loop
	do
	{

		MSConsole::Output("1. Cemetary of Old -- Necromancer Yorick\n");
		MSConsole::Output("2. The Kennel -- Jacob Warrock\n");
		MSConsole::Output("3. Encampment on the River -- Chieftain Grug\n");
		MSConsole::Output("4. Look at Sebastian's Wares.\n\n");

		MSConsole::Output("Where to go? ");
		cin >> input;

		switch (input)
		{
		case 1:
			// CEMETARY
			cemetaryCmpltd = cemetaryOfOld(player);
			if (cemetaryCmpltd == true)
			{
				MSConsole::Output("Oh you killed Yorick? Well done have some gold.\n");
				MSConsole::Output("You gained 150 gold.\n");
					player[0].gainGold(150);
			}
			break;
		case 2:
			// KENNEL
			kennelCmpltd = Kennel(player);
			if(kennelCmpltd == true)
			{
				MSConsole::Output("Oh you killed Jacob? Well done have some gold.\n");
				MSConsole::Output("You gained 250 gold.\n");
				player[0].gainGold(250);
			}
			break;
		case 3:
			 // ENCAMPMENT - Gauntlet
			encampmentCmpltd = orcEncampment(player);
			if(encampmentCmpltd == true)
			{
				MSConsole::Output("Oh you killed Glug? Well done have some gold.\n");
				MSConsole::Output("You gained 225 gold.\n");
				player[0].gainGold(250);
			}
			break;
		case 4:
			sebastianShop(player);
			break;
		default:
			MSConsole::Output("**INVALID SELECTON**\n");
		}

		if (encampmentCmpltd && kennelCmpltd && cemetaryCmpltd)
			dragonsBreathKeep(player);


		if (gameOver)
		{
			MSConsole::Output("You blacked out and returned to Dragonsbreath Inn\n");
			MSConsole::Output("Sebastian is standing over you..\n");
			MSConsole::Output("\"Don't adventure so hard... You have too much to get done.\"\n");
			for (int i = 0; i < player.size(); i++)
				player[i].reFill();
			gameOver = false;
		}
	} while (!gameOver);
}

bool GameWorld::dragonsBreathKeep(vector<Player>& player)
{
	system("cls");
	MSConsole::Output("You wake up and go downstairs, there are \n");
	MSConsole::Output("papers strewn everywhere... Everything is \n");
	MSConsole::Output("a mess. Barstools crashed against the wall,\n");
	MSConsole::Output("scratches everywhere... Where is \n");
	MSConsole::Output("Sebastian...\n\n");

	MSConsole::Output("You call out to him and no response.\n\n");

	MSConsole::Output("You wander around the inn to find nothing,\n");
	MSConsole::Output("no sign of Sebastian, no sign of anything.\n");
	MSConsole::Output("It is as if Sebastian was never even here.\n");
	MSConsole::Output("What is going on...\n\n");

	MSConsole::Output("You go outside, and see smoke trails in\n");
	MSConsole::Output("the distance. Odd.. Who could be camping\n");
	MSConsole::Output("out in the old castle out there.\n\n");

	system("pause");

	MSConsole::Output("As you walk towards the bridge that leads\n");
	MSConsole::Output("to the old castle you see Sebastian in the\n");
	MSConsole::Output("distance.\n\n");

	MSConsole::Output("You run up to Sebastian to ensure he is \n");
	MSConsole::Output("alright.\n\n");

	MSConsole::Output("Sebastian lets out an exasperated sigh...\n");
	MSConsole::Output("\"You should've just left it alone\"\n\n");

	MSConsole::Output("\"I know you want the world to be a better\n");
	MSConsole::Output("place, one where we are all the best of\n");
	MSConsole::Output("ourselves... It's just not the way of life\"\n\n");

	MSConsole::Output("Sebastian begins to crack his knuckles,\n");
	MSConsole::Output("and leans on the bridge..\n\n");

	system("pause");

	MSConsole::Output("\"I'm sorry, you just were a pawn in all\n");
	MSConsole::Output("of this. arrghh\"\n\n");

	MSConsole::Output("Sebastian begins to grow in size... A tail\n");
	MSConsole::Output("begins to immerge from his back, and \n");
	MSConsole::Output("monstrous wings start to form.\n\n");

	MSConsole::Output("***HE'S A DRAGON***\n\n");

	MSConsole::Output("\"You were a great help getting rid of\n");
	MSConsole::Output("the rest of the insects, but I can't\n");
	MSConsole::Output("leave any deadends.\" He booms.\n\n");
	
	system("pause");

	bossFight("Sebastian", player);

	return true;

}

void GameWorld::Finale(vector<Player>& player)
{
	MSConsole::Output("A flash of lightning streaks past your head and\n");
	MSConsole::Output("strikes Sebastian dead in the chest. \n\n");

	MSConsole::Output("A yelp of pain comes flying out of Sebastian as\n");
	MSConsole::Output("he staggers backwards.\n\n");

	MSConsole::Output("You turn to see a Massive armor cladded knight\n");
	MSConsole::Output("come riding up behind you. He begins to yell \n");
	MSConsole::Output("to Sebastian.\n\n");

	MSConsole::Output("\"I know what you have been up to Sebastian\n");
	MSConsole::Output("your corruption has come to it's end. It took\n");
	MSConsole::Output("me far too long to recognize what you've done.\"\n\n");

	system("pause");

	MSConsole::Output("Sebastian staggers back to his feet. \"You are\n");
	MSConsole::Output("far too late, great king Joran. This is but the\n");
	MSConsole::Output("beginning of the end.\"\n\n");

	MSConsole::Output("Sebastian begins to fly to the sky and yells\n");
	MSConsole::Output("\"Believe me when I tell you. It is the end\n");
	MSConsole::Output("times. Farewell for now.\"\n\n");

	MSConsole::Output("King Jorah throws another lightning bolt\n");
	MSConsole::Output("across the sky and misses the great blue\n");
	MSConsole::Output("Dragon.\n\n");

	MSConsole::Output("Sebastian slowly leaves sight.\n\n");

	system("pause");

	MSConsole::Output("\"So you are the brave "+ player[0].Job() + ",\n");
	MSConsole::Output("that has defeated Yorick and Jacob. \n");
	MSConsole::Output("I knew them both well.\"\n\n");

	MSConsole::Output("You begin to stagger into a combat stance\n");
	MSConsole::Output("threatened by the idea that this man had\n");
	MSConsole::Output("ties to the evil you had purged.\n\n");

	MSConsole::Output("\"Although I mean you no ill will, you\n");
	MSConsole::Output("will have to come back with me to the\n");
	MSConsole::Output("kingdom. To pay for the deeds you have\n");
	MSConsole::Output("done here.\"\n\n");

	MSConsole::Output("Confused, you ask why you would have to pay\n");
	MSConsole::Output("at all for cleansing the earth of their evil.\n\n");

	MSConsole::Output("\"You don't understand everything yet, they\n");
	MSConsole::Output("were cursed men. Whose will was bent by the\n");
	MSConsole::Output("Dragon who just flew from here. Once we \n");
	MSConsole::Output("return to the castle, we will discuss it all.\"\n\n");

	system("pause");

	MSConsole::Output("You just nod, your heart sinks in your\n");
	MSConsole::Output("chest thinking this clearly meant you were\n");
	MSConsole::Output("going to rot away in the dungeon.\n\n");

	MSConsole::Output("\"You owe me a debt I expect you to pay.\n");
	MSConsole::Output("You owe me... \n\n");

	MSConsole::Output("The head of Sebastian Delouvre\"\n\n");
}

void GameWorld::bossFight(const string Name, vector<Player>& party)
{
	system("cls");
	int input;
	int attacks = 0;
	int deadEnemies;

	vector<Enemy*> enemies;

	if (Name == "Grug")
		enemies.push_back(new Grug());
	else if (Name == "Jacob")
		enemies.push_back(new Jacob());
	else if (Name == "Sebastian")
		enemies.push_back(new Sebastian());
	else if (Name == "Yorick")
		enemies.push_back(new Yorick());


	do{
		deadEnemies = 0;

		if (!enemies[0]->isDead())
		{
			cout << 0 << "\t";
			enemies[0]->displayStats();
		}
	
		MSConsole::Output("\n");
		for (int i = 0; i < party.size(); i++)
		{
			MSConsole::Output(party[i].Name() + "\t\t" + StringUtil::ToString_i(party[i].CurrentHealth()) + " / " + StringUtil::ToString_i(party[i].MaxHealth()) + " HP\n");
		}
		MSConsole::Output("\n");
		MSConsole::Output("What do you do?\n");
		MSConsole::Output("1. Fight\n");
		MSConsole::Output("2. Use Item\n");
		cin >> input;

		switch (input)
		{
		case 1:
			party[0].CombatChoice(enemies, party);
			for (int i = 1; i < party.size(); i++)
			{
				if (!party[i].isDead())
					party[i].followerMove(enemies, party);
			}
			if (attacks % 2 == 0)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i]->Attack(party);
				}
			}
			attacks++;
			break;
		case 2:
			CombatItems(party);
			break;
		default:
			MSConsole::Output("INVALID CHOICE\n");
		}

		if (Name == "Sebastian")
		{
			if (enemies[0]->CurrentHealth() < 8000)
			{
				Finale(party);
			}
		}


		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->isDead())
				deadEnemies++;
		}
	} while (deadEnemies != 1 || party[0].isDead());

	if (party[0].isDead())
	{
		gameOver = true;
	}
	else
	{
		for (int x = 0; x < enemies.size(); x++)
		{
			party[0].gainXP(enemies[x]->giveXP());
		}
		party[0].gainGold(50 * enemies.size());
	}
}

bool GameWorld::orcEncampment(vector<Player>& party)
{
	system("cls");
	MSConsole::Output("After setting up for camp at the end of the night,\n");
	MSConsole::Output("you lay down under the stars to gather your strength\n");
	MSConsole::Output("for the day ahead.\n\n");

	MSConsole::Output("Groggily you wake up to find yourself in a makeshift\n");
	MSConsole::Output("cage... You hear a roaring crowd of what sounds like\n");
	MSConsole::Output("orcs and goblins, and think to yourself how did this\n");
	MSConsole::Output("even happen.\n\n");

	MSConsole::Output("'WELCOME' yells a rather large orc. 'DIS IS DAH\n");
	MSConsole::Output("BEGINNING OF DAH END WE ARE HERE TO WITNESS THIS\n");
	MSConsole::Output("PESKY HOOMAN DAT WE CAUGHT FIGHT FOR HES LIFE'\n\n");

	MSConsole::Output("The crowd erupts into chants and just outright\n");
	MSConsole::Output("yelling, as you are thrown into the center of an\n");
	MSConsole::Output("arena.\n\n");

	MSConsole::Output("'FIRST UP COMES THE WEIRD THING WE CAPTCHAD DAH\n");
	MSConsole::Output("OTTA WEEK, EET ATE GIMROG WE NEED TO GIT RID OF\n");
	MSConsole::Output("IT SOOMEHOO'\n\n");
	system("pause");

	//-- - FIGHT AGAINST 1 DRAGON KIN-- -
	basicCombat("Dragonkin", 1, party);

	if (gameOver)
		return false;


	MSConsole::Output("'AHA THE TINY HOOMAN DID IT GRUG IS PLEASED, \n");
	MSConsole::Output("MOR FOR HOOMAN'\n\n");

	party[0].inventory.addItem(new Potion());
	MSConsole::Output("The Chieftain Grug throws a bottle towards\n");
	MSConsole::Output("you what seems to be a healing potion you\n");
	MSConsole::Output("add it to your pack as a gate begins to open\n");
	MSConsole::Output("showing you what appears to be two figures \n");
	MSConsole::Output("draped in rags.\n\n");

	MSConsole::Output("'HOOMAN ON HOOMAN COMBATTTTTTTTTTTTTTTTT'\n");
	MSConsole::Output("Grug screams.\n\n");

	system("pause");
	//--fight against 2 humanoids--
	basicCombat("Humanoid", 2, party);

	if (gameOver)
		return false;

	MSConsole::Output("'...TINY HOOMAN NOT DED... GRUG TAKE MATTERS\n");
	MSConsole::Output("INTO OWN HANDS' Grug leaps into the arena\n");
	MSConsole::Output("BattleAxe in hand and begins to run at\n");
	MSConsole::Output("you full force.\n\n");
	system("pause");
	// fight against GRUG
	//BOSS FIGHT NEED TO CREATE.
	bossFight("Grug", party);
	if (gameOver)
		return false;
	else
		return true;
}

bool GameWorld::Kennel(vector<Player>& party)
{
	system("cls");
	MSConsole::Output("You arrive at the old kennel of Dragonsbreath\n");
	MSConsole::Output("Keep. The travel was not as long as you had\n");
	MSConsole::Output("expected, but it was over for now. You walk\n");
	MSConsole::Output("towards the ajar door and creep inside\n\n");

	MSConsole::Output("The kennel had seen better days, the days of\n");
	MSConsole::Output("dogs just yelping for food, bussling hands\n");
	MSConsole::Output("attempting to get to all these yapping dogs\n");
	MSConsole::Output("to be quiet.\n\n");

	MSConsole::Output("Now its just broken cages, and the walls\n");
	MSConsole::Output("crumbling around you.. You begin your stroll\n");
	MSConsole::Output("looking for Jacob, he was last seen around\n"); 
	MSConsole::Output("here.\n\n");

	MSConsole::Output("As you walk through the halls, you notice\n");
	MSConsole::Output("a newly fashioned door...\n\n");
	system("pause");
	//OPEN DOOR -- item(); // potion
	//WALK AWAY
	KennelDoor(false, party);


	if (gameOver)
		return false;

	MSConsole::Output("As you continue through the halls, you\n"); 
	MSConsole::Output("wonder why any human would even live here.\n");
	MSConsole::Output("The whole place seems to be falling apart\n");
	MSConsole::Output("most of the area has seen much better days.\n");
	MSConsole::Output("Jacob has to be on the edge of losing or\n");
	MSConsole::Output("has already lost it.\n\n");

	MSConsole::Output("As you continue through the broken up\n");
	MSConsole::Output("area you come to another newly fashioned\n");
	MSConsole::Output("door...\n\n");
	system("pause");
	//OPEN DOOR -- enemy(2); // wolvren
	//walk away
	KennelDoor(true, party);

	if (gameOver)
		return false;

	MSConsole::Output("Howling in the distance, cools your heart\n");
	MSConsole::Output("the world seems so lonely. From the back\n");
	MSConsole::Output("of your mind you remember tales of creatures\n");
	MSConsole::Output("in the heart of forests snatching passerbys.\n\n");

	MSConsole::Output("Tales of Werewolves... From everything\n");
	MSConsole::Output("you had seen so far, you wouldn't doubt\n");
	MSConsole::Output("their existance anymore. As you continue\n");
	MSConsole::Output("to the depths of the kennel, you begin\n");
	MSConsole::Output("to hear a fire roaring in the distance.\n\n");

	MSConsole::Output("Maybe jacob was behind this door.\n\n");
	system("pause");
	//OPEN DOOR -- item(); // potion
	//walk away
	KennelDoor(false, party);

	if (gameOver)
		return false;

	MSConsole::Output("The warmth continues to lure you in\n");
	MSConsole::Output("like a moth to the flame...\n\n");

	MSConsole::Output("The howling grows louder...\n\n");

	MSConsole::Output("A noise from behind you sparks you to\n");
	MSConsole::Output("turn. A mammoth figure stands behind \n");
	MSConsole::Output("you... Jacob... what...\n\n");
	system("pause");

	bossFight("Jacob", party);

	//BOSS FIGHT
	if (gameOver)
		return false;
	else
		return true;
}

void GameWorld::KennelDoor(bool isEnemy, vector<Player>& party)
{
	int choice;

	MSConsole::Output("1. Open the Door\n");
	MSConsole::Output("2. Leave\n");
	MSConsole::Output("Do you want to open the door? ");
	cin >> choice;

	switch (choice)
	{
	case 1:
		if (isEnemy)
			basicCombat("Wolvren", 2, party);
		else
		{
			MSConsole::Output("You find a potion on the ground...\n");
			party[0].inventory.addItem(new Potion());
		}
		break;
	case 2:
		break;
	default:
		MSConsole::Output("**INVALID SELECTION**\n");
	}

}

GameWorld::GameWorld()
{
	cemetaryCmpltd = false;
	encampmentCmpltd = false;
	kennelCmpltd = false;
	gameOver = false;
}

// unsure if implemented....
void GameWorld::Reset()
{
	cemetaryCmpltd = false;
	encampmentCmpltd = false;
	kennelCmpltd = false;
	gameOver = false;
}

void GameWorld::Prologue()
{
	MSConsole::Output("Welcome to the world of Devarion...\n\n\n");

	MSConsole::Output("You might not know me yet, but you will\n");
	MSConsole::Output("everyone does in the end. For good or for\n");
	MSConsole::Output("worse, we'll be friends, more or less.\n\n");

	MSConsole::Output("The name is Sebastian, it doesn't matter\n");
	MSConsole::Output("right now, but it might at some point.\n");
	MSConsole::Output("The world of Devarian is a scary place,\n");
	MSConsole::Output("orcs, cultists, and who knows what lurking\n");
	MSConsole::Output("in the darkness.\n\n");

	MSConsole::Output("People are in constant fear, and the King\n");
	MSConsole::Output("just hides in his kingdom, contemplating\n");
	MSConsole::Output("sorcery and other such follies.\n\n");

	system("pause");

	MSConsole::Output("What is life? With the fall of the last\n");
	MSConsole::Output("dragons, too much flew away. Adventurers\n");
	MSConsole::Output("shriveled up and ran away after the\n");
	MSConsole::Output("greatest game was gone. Now... Now there\n");
	MSConsole::Output("is nothing.\n\n");

	MSConsole::Output("Hope is fleeting, life is stagnant and\n");
	MSConsole::Output("the time for humans seems lost. Day by\n");
	MSConsole::Output("day the world grows darker, most don't\n");
	MSConsole::Output("seem to care, not you though...\n\n");

	MSConsole::Output("You seem hellbent on fixing it all...\n\n\n");

	MSConsole::Output("How odd...\n\n\n");

	system("pause");
}

void GameWorld::sebastianShop(vector<Player>& party)
{

	int input;
	bool exit = false;

	do
	{
		MSConsole::Output("1. Buy Supplies\n");
		MSConsole::Output("2. Sell Items\n");
		MSConsole::Output("3. Go back.\n");
		MSConsole::Output("What would you like to do? ");
		cin >> input;

		switch(input)
		{
		case 1:
			sebastianBuy(party);
			break;
		case 2:
			sebastianSell(party);
			break;
		case 3:
			//exit shop
			exit = true;
			break;
		default:
			MSConsole::Output("**INVALID SELECTION**\n");

		}
	}while(!exit);

}

void GameWorld::sebastianBuy(vector<Player>& party)
{
	int input;
	int howMany;
	srand(time(NULL));
	int randomNum = rand() % 5;

	MSConsole::Output("We are currently only selling a few things\n");
	MSConsole::Output("1. Potions\n");
	MSConsole::Output("2. Random junk armor\n");


	MSConsole::Output("What would you like? ");
	cin >> input;

	switch(input)
	{
	case 1:
		MSConsole::Output("How many would you like? ");
		cin >> howMany;

		MSConsole::Output("That will cost you " + StringUtil::ToString_i(5*howMany) + " gold.\n");
		if(Creator::areYouSure())
		{
			if(party[0].Gold() < 5*howMany)
			{
				MSConsole::Output("You dont have enough money\n");
			}
			else
			{
				party[0].buySomething(5*howMany);
				for(int i=0; i < howMany; i++)
				{
					party[0].inventory.addItem(new Potion());
				}
			}
		}
		else
		{
			MSConsole::Output("Alright... If you say so\n");
		}
		break;
	case 2:
		MSConsole::Output("I dont really suggest buying it, but if you want it..\n");
		MSConsole::Output("It'll cost ya " + StringUtil::ToString_i(150*party[0].Level()) + " gold.\n");
		if(Creator::areYouSure())
		{
		
			if(party[0].Gold() < 150*party[0].Level())
			{
				MSConsole::Output("You dont have enough money\n");
			}
			else
			{
				party[0].buySomething(150*party[0].Level());
				party[0].inventory.addItem(new Armor(randomNum));
			}
		}
		else
		{
			MSConsole::Output("Alright... If you say so\n");
		}
		break;
	}




}

void GameWorld::sebastianSell(vector<Player>& party)
{
	int input;

	party[0].inventory.display();

	if(party[0].inventory.bag.empty())
	{
		MSConsole::Output("You dont have anything for me...\n");
		system("pause");
		return;
	}

	MSConsole::Output("Which item would you like to sell? ");
	cin >> input;

	MSConsole::Output("I will pay you " + StringUtil::ToString_i(party[0].inventory.bag[input]->GoldValue()) + " for this item\n");
	if(Creator::areYouSure())
	{
		party[0].gainGold(party[0].inventory.bag[input]->GoldValue());
		party[0].inventory.removeItem(party[0].inventory.bag[input]);
	}
	else
	{
		MSConsole::Output("Alright... If you say so\n");
	}
}

bool GameWorld::cemetaryOfOld(vector<Player>& party)
{
	system("cls");
	MSConsole::Output("As you walk through the broken\n");
	MSConsole::Output("gate into the main entrance of the \n");
	MSConsole::Output("cemetary, a crack of lightning flash\n");
	MSConsole::Output("across your view. You look up to see\n");
	MSConsole::Output("the outline of what appears to be\n");
	MSConsole::Output("a church in the distance.\n\n");

	MSConsole::Output("A few mausoleums are right ahead\n");
	MSConsole::Output("of you. You hear a lot of clanging.\n");
	MSConsole::Output("Odd for a cemetary to be as lively\n");
	MSConsole::Output("as it sounds...\n\n");

	system("pause");

	Mausoleum(party);

	if (gameOver)
		return false;

	MSConsole::Output("The lines of mausoleums, seem to\n");
	MSConsole::Output("be endless. The clanging just seems\n");
	MSConsole::Output("to be constant almost as if something\n");
	MSConsole::Output("is calling at whatever is doing it.\n\n");

	MSConsole::Output("You continue to stroll through the\n");
	MSConsole::Output("cemetary, with the banging becoming\n");
	MSConsole::Output("ever constant. You see another mausoleum\n");
	MSConsole::Output("and decide to investigate\n\n");

	system("pause");

	Mausoleum(party);
	
	if (gameOver)
		return false;

	MSConsole::Output("As you continue venturing towards\n");
	MSConsole::Output("the church up the hill, the clanging\n");
	MSConsole::Output("continues to get louder and louder.\n\n");

	MSConsole::Output("You stumble upon a bunch of unmarked\n");
	MSConsole::Output("graves. Nothing of worth seems to be\n");
	MSConsole::Output("in this area...\n\n");

	system("pause");

	basicCombat("Skeleton", 3, party);

	if (gameOver)
		return false;


		MSConsole::Output("The clanging seems to settle down for \n");
	MSConsole::Output("the moment, as you quell the tide of\n");
	MSConsole::Output("skeletons. The church just a few steps\n");
	MSConsole::Output("away, you continue your quest for \n");
	MSConsole::Output("Yorick...\n\n");

	MSConsole::Output("As you get to the door of the Church,\n");
	MSConsole::Output("the doors open to a massive figure. \n");
	MSConsole::Output("Carrying a shovel, the figure seems to\n");
	MSConsole::Output("be some form of Undertaker...\n\n");

	MSConsole::Output("\"You don't get to here without some\n");
	MSConsole::Output("permission to be on the grounds.\"\n\n");

	system("pause");

	bossFight("Yorick", party);



	return true;
}

void GameWorld::Mausoleum(vector<Player>& party)
{
	int choice;
	bool opened = false;

	do{
		MSConsole::Output("1. Open the Mausoleum door\n");
		MSConsole::Output("2. Leave\n");
		MSConsole::Output("Do you want to open the door? ");
		cin >> choice;

		switch (choice)
		{
		case 1:
			basicCombat("Skeleton", 1, party);
			opened = true;
			break;
		case 2:
			opened = true;
			break;
		default:
			MSConsole::Output("**INVALID SELECTION**\n");
		}
	} while (!opened);
}