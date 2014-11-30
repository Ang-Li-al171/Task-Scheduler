#include <iostream>
#include <unistd.h>
#include "Scheduler.h"
#include <cstdlib>
#include <stdio.h>

int main(){

Scheduler init(2,4);

int** etc = new int*[4];
for(int i = 0; i < 4;i++)
    etc[i] = new int[2];

int* corestime = new int[2];

corestime[0] = 55;
corestime[1] = 47;

for(int i = 0; i < 4; i++){
	for (int j = 0; j <2; j++){
		etc[i][j] = rand() % 7 + 5;
	}
}

init.Schedule_minmin(etc, corestime);

cout << corestime[0] << corestime[1];
for(int i = 0; i < 4; i++) {
    delete [] etc[i];
}
delete [] etc;
delete [] corestime;
return 0;
}
