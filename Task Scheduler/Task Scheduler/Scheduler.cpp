#include "Scheduler.h"
#include <map>
#include <stdio.h>


Scheduler::Scheduler(void): cores(0), tasks(0){}
Scheduler::Scheduler(int _cores, int _tasks): cores(_cores), tasks(_tasks){}

void findmin( int ** comptime, int * comptasks, int * min, int task, int core){
	int* currentmin = new int[2];
	int minimum = comptime[currentmin[0]][currentmin[1]];
	for (int i = 0; i < task; i++){
		if(comptasks[i] ==1){
			minimum = comptime[i][0];
			currentmin[0] = i;
			currentmin[1] = 0;
			break;
		}
	}

	for (int i = 0; i < task; i++){
		for( int j = 0; j < core; j++){
			if(comptasks[i] ==1 && comptime[i][j] <= minimum){
				minimum = comptime[i][j];
				currentmin[0] = i;
				currentmin[1] = j;
			}
		}
	}
	comptasks[currentmin[0]] = 0;
	min[0] = currentmin[0];
	min[1] = currentmin[1];
	delete [] currentmin;
}

	
 void Scheduler::Schedule_minmin(int ** ETC, int * cores_time){
	 int** comp_time = new int*[tasks];
	 for(int i = 0; i < tasks; i++)
	     comp_time[i] = new int[cores];
	int* current_min = new int[2];
	int* comp_tasks = new int[tasks];
	for(int i = 0; i< tasks; i++){
		comp_tasks[i] = 1;
	}
	
    	
	for(int i = 0; i < tasks; i++){
		for(int j = 0; j < cores; j++){
			comp_time[i][j] = ETC[i][j] + cores_time[j];
		}
	}
	for(int i = 0;i < tasks; i++){
		findmin(comp_time, comp_tasks, current_min, tasks, cores);
		cores_time[current_min[1]] = cores_time[current_min[1]] +  ETC[current_min[0]][current_min[1]];
		
		for(int i = 0; i < tasks; i++){
			for(int j = 0; j < cores; j++){
				comp_time[i][j] = ETC[i][j] + cores_time[j];
			}
		}
	}
	delete [] comp_tasks;
	delete [] current_min;

	for(int i = 0; i < tasks;i++) {
	    delete [] comp_time[i];
	}
	delete [] comp_time;


}
		
		                                                                                              
	
