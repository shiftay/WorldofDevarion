#pragma once
#include <string>
#include <ctime>

using std::time;
using std::string;

const string potentialSuffixs[5] = { "of the Gorilla", "of the Fox", "of the Bear", "of the Unicorn", "of the Raven" };
const string potentialTypes[5] = { "Iron", "Silver", "Gold", "Platinum", "Diamond" }; 
const string weapNames[5] = { "Staff", "Axe", "Mace", "Dagger", "Sword" }; // used for later implementations.

class Item
{
protected:
	int goldValue;
	string name;
	string type;
	string suffix;

public:
	inline void setSuffix(const int newVal){ suffix = potentialSuffixs[newVal]; }
	inline const string Suffix() { return suffix; }

	inline void setType(const int newVal) { type = potentialTypes[newVal]; }
	inline const string getType() const { return type; }

	inline void setGold(const int newVal) { goldValue = newVal; }
	inline const int GoldValue() const { return goldValue; }

	inline const string getName() const { return name; }
	
	virtual const int itemUse() =0;
};