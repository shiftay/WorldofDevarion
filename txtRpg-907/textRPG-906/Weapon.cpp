#include "Weapon.h"

Weapon::Weapon()
{
	srand(time(0));

	int holder, holder1;
	holder = rand() % 5;
	holder1 = rand() % 4 + 1;

	name = "Weapon";
	setSuffix(holder);
	setType(holder);

	baseDamage = holder1 * 2;

	goldValue = 50 * holder1;
}