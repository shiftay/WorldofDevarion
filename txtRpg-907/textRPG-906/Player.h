//
//	Player v0.0.1
//The creator for a player object.
#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Console.h"
#include "stringUtil.h"

class Enemy;


class Player : public Actor
{
private:
	string job_;

	int level;
	int currentXP;
	int maxXP;

	int GoldAmount;
	//combat stats
	int evasion;
	int critChance;

	bool cooking;

	bool follower;

	void castSpell(vector<Enemy*>, int); // if damaging ability
	void castSpell(vector<Player>&, int); // if paladin's heals
public:
	Player();
	Player(const string, const string, bool); // accepts name, job, bool Follower
	Player(const string, const string, int[], vector<string>); // name, job, stats array, passives+skills



	Inventory inventory;
	void useItem(Item*);
	void checkStats();

	inline void buySomething(const int newVal) { GoldAmount -= newVal; }
	inline void gainGold(const int newVal) { GoldAmount += newVal; }
	inline void isDamaged(const int newVal) { current_health -= newVal; }
	inline void gainXP(const int newVal) { currentXP += newVal; }
	void levelUp(); // used when leveling up
	inline const int Level() const { return level; }
	inline const string Job() const { return job_; }
	inline const int Gold() const { return GoldAmount; }

	// used for combat system
	int meleeAttack(Enemy&);
	void CombatChoice(vector<Enemy*>, vector<Player>&);
	void followerMove(vector<Enemy*>, vector<Player>&);


	bool isCrit();
	void isHealed(const int);
	bool isDead();

	void reFill();
};