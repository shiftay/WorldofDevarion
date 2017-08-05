#include "Inventory.h"


void Inventory::display()
{
	if (bag.empty())
	{
		MSConsole::Output("\n**<EMPTY>**\n");
		return;
	}
	else
	{
		MSConsole::Output("\n" + StringUtil::ToString_i(bag.size()) + " / " + StringUtil::ToString_i(MAX_SIZE) + "\n");
		for (int i = 0; i < bag.size(); i++)
		{
			MSConsole::Output(StringUtil::ToString_i(i) + "\t" + bag[i]->getType() + " " + bag[i]->getName() + "\n");
		}
	}
	//display the entire inventory
	//as well as how many slots are being taken up.
}

//currently this wouldnt retain function, use with caution.
void Inventory::equipItem(Item* item)
{
	//int placeHolder = 0;

	//for (int i = 0; i < equipped.size(); i++)
	//{
	//	if( item->getName() == equipped[i]->getName())
	//	{
	//		Item* holder = equipped[i];
	//		placeHolder = i;
	//		break;
	//	}
	//}

	equipped.push_back(item);
	
	//if (holder != NULL)
	//{
	//	addItem(holder);
	//	for (int j = 0; j < bag.size(); j++)
	//	{
	//		if(item == bag[j])
	//		{
	//			removeItem(item);
	//			break;
	//		}
	//	}
	//}
}

void Inventory::addItem(Item* newItem)
{
	//check if inventory is full
	if (isFull())
	{
		MSConsole::Output("Inventory is full, can not add anymore.\n");
		return;
	}
	else
	{
		bag.push_back(newItem);
	}
	//add item
}

void Inventory::removeItem(Item* item)
{

	if (hasItem(item))
	{
		for (int i = 0; i < bag.size(); i++)
		{
			if (bag[i] == item)
			{
				delete bag[i];
				bag.erase(bag.begin() + i);
				return;
			}
		}
	}
	else
	{
		return;
	}
	//check if the item exists
	//remove item
}

bool Inventory::hasItem(const Item* testItem)
{
	bool has = false;

	for(int i = 0; i < bag.size(); i++)
	{
		if(bag[i] == testItem)
		{
			has = true;
			break;
		}
	}

	return has;
}

bool Inventory::isFull()
{
	//check if inventory is full
	if (bag.size() >= 15)
		return true;
	else
		return false;
}


int Inventory::attackBonus()
{
	int holder = 0;
	// returns the damage of the equipped weapon.
	for (int i = 0; i < equipped.size(); i++)
	{
		if (equipped[i]->getType() == "Weapon") // need to change this but rough idea
		{
			holder = i;
			break;
		}
	}


	if(equipped[holder]->itemUse() == NULL)
		return 0;
	else
		return equipped[holder]->itemUse();

}


int Inventory::armorBonus()
{
	int holder = 0;
	// returns the damage of the equipped weapon.
	for (int i = 0; i < equipped.size(); i++)
	{
		if (equipped[i]->getName() == "Breastplate")
		{
			holder = i;
			break;
		}
	}


	if (equipped[holder]->itemUse() == NULL)
		return 0;
	else
		return equipped[holder]->itemUse();

}