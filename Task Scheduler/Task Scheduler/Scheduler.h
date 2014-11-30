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
		friend void findmin( int ** comptime, std::vector<int> & comptasks, std::vector<int> & min);
};
