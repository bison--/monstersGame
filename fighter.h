#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <string>

class fighter
{
	private:
		std::string fName;
	
		bool isHuman;
		char battleAction;
		uint32_t level;
		uint32_t maxHealthPoints;
		uint32_t healthPoints;
		uint32_t attackPoints;
		uint32_t defensePoints;
	
		void setHumanXp(uint32_t xps);
	public:		
		// fName
		std::string fighterName();
		void setFighterName(std::string newName);

		// isHuman
		bool isFighterHuman();
		void setFighterIsHuman(bool setHuman);
	
		// battleAction
		char fighterBattleAction();
		void setFighterBattleAction(char newAction);
		
		// level
		uint32_t fighterLevel();
		void increaseFighterLevelsBy(uint32_t levelsUp);
		
		// XP-action
		uint32_t getXPsForFighterLevel();
		enum setXPen {addHealthPoints, addAttackPoints, addDefensePoints};
		void setXP(setXPen setDest);
		void setXP(uint32_t xp, setXPen setDest);
		
		// healthPoints
		uint32_t fighterHp();
		void setFighterHp(uint32_t newHp);
		void regenByPercent(uint32_t regenPercent);
		
		// maxHealthPoints
		uint32_t fighterMaxHp();
		void setFighterMaxHp(uint32_t newMaxHp);
		
		// print health-bar
		void printHealthBar();
		
		// isAlive
		bool isAlive();
		uint32_t recieveDamage(uint32_t damage);
		
		// attackPoints
		uint32_t fighterAttackPoints();
		
		// defensePoints
		uint32_t fighterDefensePoints();
};

#endif
