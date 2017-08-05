#pragma once
#include "Item.h"

class Potion : public Item
{
private:
	int healValue;
	
public:
	Potion(); // CTor -- accepts boolean.

	//accessors
	const int itemUse() { return healValue; }
};