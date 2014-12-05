#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Scheduler{
	int cores;
	int tasks;
	public:
	
		Scheduler(void);
		Scheduler(int,int);
		void Schedule_minmin(int **, int *);
		void Schedule_maxmin(int **, int *);
		void Schedule_greedy(int **, int *);
	};
