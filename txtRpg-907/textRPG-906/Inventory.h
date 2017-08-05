//
//		Inventory V0.0.1  
//Container for managing items for each player. 
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Armor.h"
#include "Weapon.h"
#include "Console.h"
#include "stringUtil.h"

using std::string;
using std::vector;

const int MAX_SIZE = 15; // max inventory size

class Inventory
{
public:
	bool hasItem(const Item*);
	// no implementation.
	//void inventoryManager(const string&, const int); 
	void display();
	void addItem(Item*);
	int attackBonus(); // This will return the damage of weapon.
	int armorBonus();
	void equipItem(Item*);
	vector<Item*> bag; // controls items
	vector<Item*> equipped; // controls equipped items
	void removeItem(Item*);
private:
	bool isFull();


};