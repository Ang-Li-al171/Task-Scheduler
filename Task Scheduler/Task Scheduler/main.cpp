//
//  main.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "Graph.h"
#include "DDependency.h"
#include "ControlPenalty.h"

const char* appendWithCWD(const char* fileName){
    char buffer[200];
    getcwd(buffer, 200);
    std::string file = std::string(buffer) + fileName;
    const char* filePath = file.c_str();
    return filePath;
}

int main(int argc, const char * argv[])
{
    // cores
    processor* highPerforming = new processor("High Performing Core", 2);
    processor* lowPerforming = new processor("Low Performing Core", 1);
    
    int etcMatrix[5][2]; // assuming CPI=1
    
    // for file inputs
    ifstream inFile1 (appendWithCWD("/inputTask1.txt"));
    ifstream inFile2 (appendWithCWD("/inputTask2.txt"));
    ifstream inFile3 (appendWithCWD("/inputTask3.txt"));
    ifstream inFile4 (appendWithCWD("/inputTask4.txt"));
    ifstream inFile5 (appendWithCWD("/inputTask5.txt"));
    
    // construct the data dependency graphs and calculate maximum depths
    DDependency dDependency;
    Graph g = dDependency.constructDependencyG(inFile1);
    etcMatrix[0][0] = g.maxDepth();
    etcMatrix[0][1] = g.instrCount;
    g = dDependency.constructDependencyG(inFile2);
    etcMatrix[1][0] = g.maxDepth();
    etcMatrix[1][1] = g.instrCount;
    g = dDependency.constructDependencyG(inFile3);
    etcMatrix[2][0] = g.maxDepth();
    etcMatrix[2][1] = g.instrCount;
    g = dDependency.constructDependencyG(inFile4);
    etcMatrix[3][0] = g.maxDepth();
    etcMatrix[3][1] = g.instrCount;
    g = dDependency.constructDependencyG(inFile5);
    etcMatrix[4][0] = g.maxDepth();
    etcMatrix[4][1] = g.instrCount;
    
    int i;
    for(i = 0; i<5; i++){
        cout << etcMatrix[i][0] << " " << etcMatrix[i][1] << endl;
    }
    cout << endl;
    
    // for file inputs
    ifstream inFile11 (appendWithCWD("/inputTask1.txt"));
    ifstream inFile21 (appendWithCWD("/inputTask2.txt"));
    ifstream inFile31 (appendWithCWD("/inputTask3.txt"));
    ifstream inFile41 (appendWithCWD("/inputTask4.txt"));
    ifstream inFile51 (appendWithCWD("/inputTask5.txt"));
    
    ifstream inFile12 (appendWithCWD("/inputTask1.txt"));
    ifstream inFile22 (appendWithCWD("/inputTask2.txt"));
    ifstream inFile32 (appendWithCWD("/inputTask3.txt"));
    ifstream inFile42 (appendWithCWD("/inputTask4.txt"));
    ifstream inFile52 (appendWithCWD("/inputTask5.txt"));
    
    // handle branch penalties
    ControlPenalty cp;
    
    etcMatrix[0][0] += cp.calculateBranchPenalty(highPerforming, inFile11);
    etcMatrix[0][1] += cp.calculateBranchPenalty(lowPerforming, inFile12);
    etcMatrix[1][0] += cp.calculateBranchPenalty(highPerforming, inFile21);
    etcMatrix[1][1] += cp.calculateBranchPenalty(lowPerforming, inFile22);
    etcMatrix[2][0] += cp.calculateBranchPenalty(highPerforming, inFile31);
    etcMatrix[2][1] += cp.calculateBranchPenalty(lowPerforming, inFile32);
    etcMatrix[3][0] += cp.calculateBranchPenalty(highPerforming, inFile41);
    etcMatrix[3][1] += cp.calculateBranchPenalty(lowPerforming, inFile42);
    etcMatrix[4][0] += cp.calculateBranchPenalty(highPerforming, inFile51);
    etcMatrix[4][1] += cp.calculateBranchPenalty(lowPerforming, inFile52);
    
    // handle loop penalties
    
    // for file inputs
    ifstream inFile13 (appendWithCWD("/inputTask1.txt"));
    ifstream inFile23 (appendWithCWD("/inputTask2.txt"));
    ifstream inFile33 (appendWithCWD("/inputTask3.txt"));
    ifstream inFile43 (appendWithCWD("/inputTask4.txt"));
    ifstream inFile53 (appendWithCWD("/inputTask5.txt"));
    
    ifstream inFile14 (appendWithCWD("/inputTask1.txt"));
    ifstream inFile24 (appendWithCWD("/inputTask2.txt"));
    ifstream inFile34 (appendWithCWD("/inputTask3.txt"));
    ifstream inFile44 (appendWithCWD("/inputTask4.txt"));
    ifstream inFile54 (appendWithCWD("/inputTask5.txt"));
    
    etcMatrix[0][0] += cp.calculateLoopPenalty(highPerforming, inFile11);
    etcMatrix[0][1] += cp.calculateLoopPenalty(lowPerforming, inFile12);
    etcMatrix[1][0] += cp.calculateLoopPenalty(highPerforming, inFile21);
    etcMatrix[1][1] += cp.calculateLoopPenalty(lowPerforming, inFile22);
    etcMatrix[2][0] += cp.calculateLoopPenalty(highPerforming, inFile31);
    etcMatrix[2][1] += cp.calculateLoopPenalty(lowPerforming, inFile32);
    etcMatrix[3][0] += cp.calculateLoopPenalty(highPerforming, inFile41);
    etcMatrix[3][1] += cp.calculateLoopPenalty(lowPerforming, inFile42);
    etcMatrix[4][0] += cp.calculateLoopPenalty(highPerforming, inFile51);
    etcMatrix[4][1] += cp.calculateLoopPenalty(lowPerforming, inFile52);
    
    for(i = 0; i<5; i++){
        cout << etcMatrix[i][0] << " " << etcMatrix[i][1] << endl;
    }
    return 0;
}

