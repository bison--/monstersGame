#ifndef RANDOMHELPER_H
#define RANDOMHELPER_H

#define RAND_MAX24 16777216

uint32_t rand24b()
{
	//old code with warning:
	// warning: suggest parentheses around arithmetic in operand of '^'
	//	return (rand() << 12) ^ (rand()) & (0xFFFFFF);
	return ((rand() << 12) ^ (rand())) & (0xFFFFFF);
}

int32_t random_range(int32_t lowest_number, int32_t highest_number)
{
	if(highest_number == lowest_number){
		return lowest_number;
	}
	
	if(lowest_number > highest_number){
		int32_t nTmp = highest_number;
		highest_number = lowest_number;
		lowest_number = nTmp;
	}
	
	int range = 1 + highest_number - lowest_number;
	
	int32_t r = rand24b() % range;
	return lowest_number + r;
}

#endif
