#pragma once
#include "Item.h"



class Weapon : public Item
{
private:
	int baseDamage;

public:
	//accessor
	Weapon();
	void setDamage(const int newVal) { baseDamage = newVal; } 
	const int itemUse() { return baseDamage; }
};