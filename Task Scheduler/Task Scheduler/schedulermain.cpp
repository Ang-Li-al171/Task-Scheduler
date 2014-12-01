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
int* corestime1 = new int[2];
corestime[0] = 50;
corestime[1] = 49;
corestime1[0] = 50;
corestime1[1] = 49;

for(int i = 0; i < 4; i++){
	for (int j = 0; j <2; j++){
		etc[i][j] =  2*i + 3 * j + 1;
	}
}

init.Schedule_minmin(etc, corestime);
init.Schedule_maxmin(etc, corestime1);

printf("%d %d\n", corestime[0], corestime[1]);
printf("%d %d", corestime1[0], corestime1[1]);
for(int i = 0; i < 4; i++) {
    delete [] etc[i];
}
delete [] etc;
delete [] corestime;
return 0;
}
