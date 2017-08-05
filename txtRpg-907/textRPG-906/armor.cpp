#include "Armor.h"


//NAME NEEDS TO BE ADDED AND RANDOMIZED.
Armor::Armor()
{
	srand(time(NULL));

	int holder, holder1;
	holder = rand() % 5;
	holder1 = rand() % 4+1;

	name = "Breastplate";

	setSuffix(holder);
	setType(holder);

	armorValue = holder1 * 2;

	goldValue = 50*holder1;
}

Armor::Armor(int number)
{
	name = "Breastplate";

	setSuffix(number);
	setType(number);

	armorValue = (number+1) * 2;

	goldValue = 50 * (number + 1);
}