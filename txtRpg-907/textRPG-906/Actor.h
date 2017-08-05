//
//	Actor v0.0.1
//Base holder for all Characters.
#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

class Actor
{
protected:
	int armor;
	int baseDamage;

	int current_health;
	int max_health;

	int current_mana;
	int max_mana;

	string name;
	int strength;
	int dexterity;
	int intellect;
	int constitution;
	int faith;

	vector<string> spells; 

public:
	//Accessors
	inline const string Name() const { return name; }
	inline const int CurrentHealth() const { return current_health; }
	inline const int MaxHealth() const { return max_health; }
	inline const int BaseDamage() const { return baseDamage; }
	inline const int Armor() const { return armor; }


	inline const int Dexterity() const { return dexterity; }
	inline const int Strength() const { return strength; }
	inline const int Intellect() const { return intellect; }
	inline const int Constitution() const { return constitution; }
	inline const int Faith() const { return faith; }
	//Mutators
	inline void CurrentHealth(const int newVal)  { current_health = newVal; }
	inline void MaxHealth(const int newVal) { max_health = newVal; }

	inline void Dexterity(const int newVal) { dexterity = newVal; }
	inline void Strength(const int newVal)  { strength = newVal; }
	inline void Intellect(const int newVal)  { intellect = newVal; }
	inline void Constitution(const int newVal)  { constitution = newVal; }
	inline void Faith(const int newVal)  { faith = newVal; }
};