//
// GameWorld v0.0.1
// will control the entire game
#pragma once
#include "Player.h"
#include "Console.h"
#include "stringUtil.h"
#include "Creator.h"
#include "Potion.h"
#include "Armor.h"
#include "Boss.h"

const int MAX_PLAYERS = 3;

class GameWorld
{
public:
	void Begin(); // Scene Controller
	GameWorld();
	
private:
	// bools for progression.
	bool cemetaryCmpltd;
	bool encampmentCmpltd;
	bool kennelCmpltd;
	bool gameOver;
	
	void sebastianShop(vector<Player>&);
	void sebastianSell(vector<Player>&);
	void sebastianBuy(vector<Player>&);

	//Using Items
	void CombatItems(vector<Player>&);
	//param 1 - type of combatants
	//param 2 - amount of combatants
	void bossFight(const string, vector<Player>&);
	void basicCombat(const string,const int, vector<Player>&);
	//param helps decide what is dropped
	Item* drop(int);
	void Prologue();
	void introtoSebastian(vector<Player>&);
	void dragonsBreathInn(vector<Player>&); // The main hub -- Will need some shop based methods
							// as well as interaction methods.
	bool cemetaryOfOld(vector<Player>&); // Low Level Area. -- (B) Undead Necro
	bool orcEncampment(vector<Player>&); // Forest area . -- (B) Ogre
	bool Kennel(vector<Player>&); // beast / skele area -- (B)WereWolf
	bool dragonsBreathKeep(vector<Player>&); // Castle -- Dragon


	void Finale(vector<Player>&);

	void Mausoleum(vector<Player>&);
	void KennelDoor(bool, vector<Player>&);

	void Reset();
};
