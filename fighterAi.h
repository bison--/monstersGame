#include <string>
#include <vector>
#include "randomHelper.h"
#include "fighter.h"

using namespace std;

enum whatAmI_en {iRandom, iTank, iAttacker, iDefender};
void aiSetSkills(fighter& cpuFighter, uint32_t xps)
{
	whatAmI_en whatAmI = static_cast<whatAmI_en>(random_range(0,3));
	for (uint32_t i = 0; i < xps;++i)
	{
		if ((static_cast<double>(i) / xps * 100) > 75)
		{ whatAmI = iRandom; }
		
		// cant any longer inizialise var in a switch! (dont know why... yet!)
		int selected = 0;
		switch(whatAmI)
		{
			case iRandom:
				selected = random_range(0,2);
				cpuFighter.setXP( static_cast<fighter::setXPen>(selected));
				break;
			case iTank:
				cpuFighter.setXP(fighter::addHealthPoints);
				break;
			case iAttacker:
				cpuFighter.setXP(fighter::addAttackPoints);
				break;
			case iDefender:
				cpuFighter.setXP(fighter::addDefensePoints);
				break;
		}
	}
	//cpuFighter.fighterLevel()
}

static vector<string> computerNames = {"gard","lard","super","klingon","lux","skeletton",
									   "guard","slayer","vamp","dwarf","ähhh","schmand","finger","dark","mad","bad","tree"};
fighter createEnemyFighter(uint32_t level)
{
	fighter enemy = fighter();
	
	string namePart1 = computerNames[random_range(0,computerNames.size()-1)];
	string namePart2 = computerNames[random_range(0,computerNames.size()-1)];
	namePart1[0] = toupper(namePart1[0]);
	//std::transform(namePart1.begin(), 1, namePart2.begin(), ::toupper);
	//std::transform(namePart2.begin(), namePart2.end(), namePart2.begin(), ::tolower);
	
	enemy.setFighterName(namePart1 + namePart2);
	enemy.increaseFighterLevelsBy(level);
	aiSetSkills(enemy, level);
	enemy.setFighterHp(enemy.fighterMaxHp());
	
	return enemy;
}



char aiChooseAction(fighter& cpuFighter,const uint32_t enemyHp,const uint32_t enemyMaxHp)
{
	char choosed = ' ';
	int chanceDefense = 5;
	int cpuHpPercent = (static_cast<double>(cpuFighter.fighterHp()) / cpuFighter.fighterMaxHp() * 100);
	bool cpuHasMoreHp = (enemyHp < cpuFighter.fighterHp());
	//cpuHpPercent = (cpuFighter.fighterHp() / cpuFighter.fighterMaxHp()) * 100;
	//int enemyHpPercent = (static_cast<double>(enemyHp) / enemyMaxHp * 100);
	
	if (enemyHp <= (cpuFighter.fighterAttackPoints() / 2))
	{ choosed = 'a'; }
	
	if (choosed == ' ')
	{
		/*if (enemyHpPercent <= 15)
		{ chanceDefense -= ; }*/
		//chanceDefense -= (enemyHpPercent / 10);
		//chanceDefense += 
		
		
		if (cpuHpPercent >= 95)
		{
			chanceDefense = 0;
		}
		else if (cpuHpPercent >= 90)
		{
			chanceDefense = 5;
		}
		else
		{
			if (cpuHpPercent >= 80)
			{
				chanceDefense += 10;
			}
			else if (cpuHpPercent < 80  && cpuHpPercent >= 20)
			{
				chanceDefense += random_range(20,50);
			}
			else if (cpuHpPercent >= 10 && !cpuHasMoreHp)
			{
				//choosed = 'd';
				chanceDefense += 20;
			}
			else if (cpuHpPercent <= 2 && !cpuHasMoreHp)
			{
				chanceDefense += 85;
			}
			//chanceDefense += (100 - double(cpuHpPercent)) / 2;
			
			if (cpuHasMoreHp)
			{ chanceDefense -= 10; }
			//chanceDefense =  (double(chanceDefense) / 2) + ((100 - double(cpuHpPercent)) / 2) / 2;
		}
		
		if (chanceDefense < 0)
		{ chanceDefense = 0; }
		else if (chanceDefense > 100)
		{ chanceDefense = 100; }
		
		int rnd = random_range(0,100);

		//cout << "chance: " << chanceDefense << " cpu:" << cpuHpPercent << "% "  << " md:" << ((100 - double(cpuHpPercent)) / 2) / 2 << " "<< rnd << endl << endl;
		if (rnd <= chanceDefense)
		{ choosed = 'd'; }
		else
		{ choosed = 'a'; }
	}
		
	//ToDo: Exception!
	if (choosed == ' ')
	{ cout << "!crazy 88!"; return 'a'; }
	return choosed;
}

