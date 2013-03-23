#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm> // tolower

#include "randomHelper.h"
#include "fighter.h"
#include "helper.h"
#include "fighterAi.h"

using namespace std;

uint32_t getDamageForFighter(uint32_t attackPoints,uint32_t defensePoints)
{
	uint32_t damage = random_range(0, attackPoints);
	if (defensePoints > damage)
	{ damage = 1; }
	else
	{ damage -= defensePoints; }
	return damage;
}

const string battle(fighter& fighter1, fighter& fighter2)
{
	uint32_t damageForPlayer2 = 0;
	switch (fighter1.fighterBattleAction())
	{

		case 'a':
			cout << fighter1.fighterName() << " Attacks!" << endl;
			damageForPlayer2 = getDamageForFighter(fighter1.fighterAttackPoints(), fighter2.fighterDefensePoints());
			break;
		case 'd':
			cout << fighter1.fighterName() << " defends!" << endl;
			fighter1.regenByPercent(10);
			break;
	};


	uint32_t damageForPlayer1 = 0;
	switch (fighter2.fighterBattleAction())
	{
		case 'a':
			cout << fighter2.fighterName() << " Attacks!" << endl;
			damageForPlayer1 = getDamageForFighter(fighter2.fighterAttackPoints(), fighter1.fighterDefensePoints());
			break;
		case 'd':
			cout << fighter2.fighterName() << " defends!" << endl;
			fighter2.regenByPercent(10);
			break;
	};
	
		
	damageForPlayer1 = fighter1.recieveDamage(damageForPlayer1);
	damageForPlayer2 = fighter2.recieveDamage(damageForPlayer2);
	
	cout << endl;
	
	cout << fighter1.fighterName() << " takes " << damageForPlayer1 << " damage \n" 
		 << fighter2.fighterName() << " takes " << damageForPlayer2 << " damage \n";
	return "";
}

int main()
{
	srand ( time(NULL) );
	clearScreen();
	//double test = 120 / 50;
	//cout << test;
	
	cout << "########################" << endl
		 << "# MonstersGame 0.0.0.4 #" << endl
		 << "# by General Bison     #" << endl
		 << "########################" << endl
		 << endl;
		 
	string playerName = "";
	cout << "Enter your Name: ";
	cin >> playerName;

	fighter fighter1 = fighter();
	fighter1.setFighterName(playerName);
	fighter1.increaseFighterLevelsBy(1);
	fighter1.setFighterMaxHp(100);
	fighter1.setFighterHp(100);
	fighter1.setFighterIsHuman(true);
	
	fighter fighter2  = createEnemyFighter(1);
	clearScreen();
	
	char command;
	bool keepPlaying = true;
	while (keepPlaying)
	{
		/*
		cout << endl << " ####################### " << endl
			 << endl
			 << fighter1.fighterName() << " HP: " << fighter1.fighterHp() << " / " << fighter1.fighterMaxHp() << endl
			 << fighter2.fighterName() << " HP: " << fighter2.fighterHp() << " / " << fighter2.fighterMaxHp() << endl
			 << endl;
		*/
		cout << endl << " ####################### " << endl
			 << endl;
			 
		fighter1.printHealthBar();
		cout << "   ";
		fighter2.printHealthBar();
		cout << endl;
		
		cout.width(32);
		cout << fighter1.fighterName();
		//cout.width(3);
		cout << "   ";
		//cout.width(32);
		cout << fighter2.fighterName() << endl;
		
		cout << endl;
		
		if (fighter2.isAlive()==false)
		{
			cout << "You have beaten " << fighter2.fighterName() << "!!! \n Wanna fight more? \n (y)es / (n)o \n";
		}
		else
		{
			cout << "a)ttack | d)efend (regen " << int((static_cast<double>(fighter1.fighterMaxHp()) / 100) * 10) << " HP)" << endl;
		}
		
		cin >> command;
		clearScreen();
		cout << endl;
		
		if (fighter2.isAlive())
		{
			if (command == 'a' || command == 'd')
			{
				fighter1.setFighterBattleAction(command);
				fighter2.setFighterBattleAction(aiChooseAction(fighter2, fighter1.fighterHp(), fighter1.fighterMaxHp()));
				cout << battle(fighter1, fighter2);
			}
		}
		else
		{
			if (command == 'y')
			{
				fighter1.increaseFighterLevelsBy(1);
				fighter2 = createEnemyFighter(fighter2.fighterLevel() + 1);
			}
		}

		if (command == 'q' || fighter1.fighterHp() == 0 || (fighter2.isAlive() == false && command == 'n' ))
		{ 
			if (fighter1.fighterHp() == 0)
			{
				clearScreen();
				cout << "You were Killed by " << fighter2.fighterName() << endl
					 << "and it has still " << fighter2.fighterHp() << " HP left" << endl
					 << "Sorry but, you FAILED !!1!" << endl 
					 << endl; 
			}
			keepPlaying = false; 
		}
	}
	
	cout << "You reached  Level: " << fighter1.fighterLevel() << endl
		 << endl
		 << "#############" << endl
		 << "# GAME OVER #" << endl
		 << "#############" << endl
		 << endl;
		 /*<< "Press ENTER to exit..."
		 << endl;
	cin.get(command);*/
}

