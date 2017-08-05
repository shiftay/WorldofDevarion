#pragma once
#include "Item.h"

class Armor : public Item
{
private:
	int armorValue;

public:
	//accessor
	Armor();
	Armor(int);

	const int itemUse() { return armorValue; }
	void setArmor(const int newVal) { armorValue = newVal; }
};