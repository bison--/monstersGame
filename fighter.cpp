#include "fighter.h"
#include "helper.h"
#include <iostream>
#include <string>

using namespace std;

//private
	void fighter::setHumanXp(uint32_t xps)
	{
		clearScreen();
		xps += level;
		char command;
		while (xps > 0)
		{
			cout << "LEVEL UP! " << level << endl
				 << "Set your XPs: (" << xps << ")" << endl
				 << "1) healthPoints:  " << healthPoints << " / " << maxHealthPoints << endl
				 << "2) attackPoints:  " << attackPoints << endl
				 << "3) defensePoints: " << defensePoints << endl;
			cin >> command;
			
			switch (command)
			{
				case '1':
					setXP(addHealthPoints);
					//maxHealthPoints++;
					setFighterHp(healthPoints + 1);
					xps--;
					break;
				case '2':
					setXP(addAttackPoints);
					//attackPoints++;
					xps--;
					break;
				case '3':
					setXP(addDefensePoints);
					//defensePoints++;
					xps--;
					break;
			};
			
			clearScreen();
		}
	}
	
//public
		// fName
		string fighter::fighterName()
		{ return fName; }
		void fighter::setFighterName(string newName)
		{ 	
			fName = newName;
			// inizialise
			isHuman = false;
			battleAction = 'a';
			healthPoints = 0;
			maxHealthPoints = 0;
			attackPoints = 0;
			defensePoints = 0;
		}
		
		// isHuman
		bool fighter::isFighterHuman()
		{ return isHuman; }
		void fighter::setFighterIsHuman(bool setHuman)
		{ isHuman = setHuman; }
		
		// battleAction
		char fighter::fighterBattleAction()
		{ return battleAction; }
		void fighter::setFighterBattleAction(char newAction)
		{ battleAction = newAction; }
		
		// level
		uint32_t fighter::fighterLevel()
		{ return level; }
		void fighter::increaseFighterLevelsBy(uint32_t levelsUp)
		{ 
			for (uint32_t i = 0; i < levelsUp; ++i)
			{
				level++;
				maxHealthPoints += 25 * level;
				//setFighterHp(healthPoints += 25 * level);
				regenByPercent(41 + level);
				attackPoints += 11 * level;
				defensePoints += 4  * level;
			}
			
			if (isHuman == true)
			{ setHumanXp(levelsUp); }
			// ToDo: SetRandom CPU-XPs
		}
		
		//XPs
		uint32_t fighter::getXPsForFighterLevel()
		{
			return level + ((level / 10) * 2);
		}
		//uint32_t getIntForLevel(uint32_t lvl);
		
		void fighter::setXP(setXPen setDest)
		{ setXP(1, setDest); }
		
		void fighter::setXP(uint32_t xp, setXPen setDest)
		{
			switch(setDest)
			{
				case addHealthPoints:
					maxHealthPoints += xp;
					break;
				case addAttackPoints:
					attackPoints += xp;
					break;
				case addDefensePoints:
					defensePoints += xp;
					break;
			}
		}
		
		// healthPoints
		uint32_t fighter::fighterHp()
		{ return healthPoints; }
		void fighter::setFighterHp(uint32_t newHp)
		{ 
			if (newHp > maxHealthPoints)
			{ healthPoints = maxHealthPoints; }
			else
			{ healthPoints = newHp; }
		}
		void fighter::regenByPercent(uint32_t regenPercent)
		{ setFighterHp(healthPoints + ((static_cast<double>(maxHealthPoints) / 100) * regenPercent)); }
		
		// maxHealthPoints
		uint32_t fighter::fighterMaxHp()
		{ return maxHealthPoints; }
		void fighter::setFighterMaxHp(uint32_t newMaxHp)
		{ maxHealthPoints = newMaxHp; }
		
		// print health-bar
		void fighter::printHealthBar()
		{
			int hpPercent = (static_cast<double>(healthPoints) / maxHealthPoints * 100);
			cout << "[";
			for (int i = 0; i < 20; i++)
			{
				if (hpPercent > 0)
				{ cout << "=" ;}
				else
				{ cout << " "; }
				hpPercent -= 5;
			}
			cout << "] " << healthPoints << " / " << maxHealthPoints;
		}
		
		// isAlive
		bool fighter::isAlive()
		{ return (healthPoints > 0?true:false); }
		uint32_t fighter::recieveDamage(uint32_t damage)
		{ 
			if (healthPoints < damage)
			{ damage = healthPoints; }
			healthPoints -= damage;
			return damage;
		}
		
		// attackPoints
		uint32_t fighter::fighterAttackPoints()
		{ return attackPoints; }
		
		// defensePoints
		uint32_t fighter::fighterDefensePoints()
		{ return defensePoints; }
