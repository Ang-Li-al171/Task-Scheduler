#include "Scheduler.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>


Scheduler::Scheduler(void): cores(0), tasks(0){}
Scheduler::Scheduler(int _cores, int _tasks): cores(_cores), tasks(_tasks){}

void findmin( int ** comptime, int * comptasks, int * min, int task, int core){
	int* currentmin = new int[2];
	int minimum;
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
	for (int i = 0; i < 2; i++){
	min[i] = currentmin[i];
	}
	delete [] currentmin;
}

void findmax( int ** comptime, int * comptasks, int * max, int task, int core){
	int* currentmax = new int[2];
	
	int* minimum = new int[task];
	int* corenum = new int[task];
		for(int j = 0; j < task; j++){
			if(comptasks[j] ==1){
				currentmax[0] = j;
				minimum[j] = comptime[j][0];
				corenum[j] = 0;
			}
		}
	

	for (int i = 0; i < task; i++){
		for( int j = 0; j < core; j++){
			if(comptasks[i] ==1 && comptime[i][j] <= minimum[i]){
				minimum[i] = comptime[i][j];
				corenum[i] = j;
			}
		}
	}
	 
	for(int j = 0; j < task; j++){
			if(comptasks[j] ==1 && (minimum[j] >= minimum[currentmax[0]])){
				currentmax[0] = j;
				currentmax[1] = corenum[j];
				}
	}
	comptasks[currentmax[0]] = 0;
	max[0] = currentmax[0];
	max[1] = currentmax[1];
	delete [] currentmax;
	delete [] minimum;
	delete [] corenum;
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
		
		                                                                                              
void Scheduler::Schedule_maxmin(int ** ETC, int * cores_time){
	 int** comp_time = new int*[tasks];
	 for(int i = 0; i < tasks; i++)
	     comp_time[i] = new int[cores];
	int* current_max = new int[2];
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
		findmax(comp_time, comp_tasks, current_max, tasks, cores);
		cores_time[current_max[1]] = cores_time[current_max[1]] +  ETC[current_max[0]][current_max[1]];
		
		for(int i = 0; i < tasks; i++){
			for(int j = 0; j < cores; j++){
				comp_time[i][j] = ETC[i][j] + cores_time[j];
			}
		}
	}
	delete [] comp_tasks;
	delete [] current_max;

	for(int i = 0; i < tasks;i++) {
	    delete [] comp_time[i];
	}
	delete [] comp_time;


}
			
void Scheduler::Schedule_greedy(int ** ETC, int * cores_time){
	 int** comp_time = new int*[tasks];
	 for(int i = 0; i < tasks; i++)
	     comp_time[i] = new int[cores];
	int currenttask, mincore;
	int number = tasks;
	int* comp_tasks = new int[tasks];
	for(int i = 0; i< tasks; i++){
		comp_tasks[i] = 1;
	}
	
    	
	for(int i = 0; i < tasks; i++){
		for(int j = 0; j < cores; j++){
			comp_time[i][j] = ETC[i][j] + cores_time[j];
		}
	}
	while(number != 0){
		currenttask = (rand()%tasks);
		printf("%d \n", currenttask);
		if(comp_tasks[currenttask] == 1){
		mincore = 0;
		for(int p = 1; p < cores; p++){
			if(comp_time[currenttask][p] <= comp_time[currenttask][mincore]){
				mincore = p;
			}
		}		
		printf("%d \n", mincore);	
		cores_time[mincore] = cores_time[mincore] +  ETC[currenttask][mincore];
		comp_tasks[currenttask] = 0;
		for(int i = 0; i < tasks; i++){
			for(int j = 0; j < cores; j++){
				comp_time[i][j] = ETC[i][j] + cores_time[j];
			}
		}
		number = number - 1;
	}
}
		
	
	delete [] comp_tasks;
	
	for(int i = 0; i < tasks;i++) {
	    delete [] comp_time[i];
	}
	delete [] comp_time;


}
