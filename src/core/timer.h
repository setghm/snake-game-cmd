#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>

typedef struct TagTime {
	float delta;
	float last;
	
	float counter;
	float update_count;
	
	bool waiting;
	
	float second_counter;
	unsigned long long elapsed_seconds;
}Time;

Time* InitTime(float update_count);
void UpdateTime(Time* time);
void PrintElapsedTime(Time* time);

#endif//__TIMER_H__
/*
 *	End Of File
 */