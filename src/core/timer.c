#include "timer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

Time* InitTime(float update_count) {
	Time* time = (Time*) malloc(sizeof(Time));
	memset(time, 0, sizeof(Time));
	
	time->last = clock() / 1000.0f;
	time->delta = 0;
	time->update_count = update_count;
	
	return time;
}

void UpdateTime(Time* time) {
	float current = clock() / 1000.0f;
	time->delta = current - time->last;
	time->last = current;
	
	time->counter += time->delta;
	time->second_counter += time->delta;
	
	if (time->counter >= time->update_count) {
		time->waiting = false;
		time->counter -= time->update_count;
	} else {
		time->waiting = true;
	}
	
	if (time->second_counter > 1.0f) {
		
		time->second_counter -= 1.0f;
		
		if (time->elapsed_seconds < ULLONG_MAX) {
			time->elapsed_seconds += 1;
		}
		else {
			time->elapsed_seconds = 0;
		}
		
	}
}

void PrintElapsedTime(Time* time) {
	printf("Elapsed time: %llus", time->elapsed_seconds);
}

/*
 *	End Of File
 */