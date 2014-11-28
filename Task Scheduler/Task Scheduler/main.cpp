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
    processor* highPerforming = new processor("High Performing Core", 10);
    processor* lowPerforming = new processor("Low Performing Core", 1);
    
    // for file inputs
    ifstream inFile (appendWithCWD("/input.txt"));
    
    // construct the data dependency graph
    DDependency dDependency;
    Graph g = dDependency.constructDependencyG(inFile);
    g.printGraph();
    cout << endl << "Data dependency graph has maximum depth " << g.maximumDepth << endl;
    
    // handle branch penalties
    ControlPenalty cp;
    ifstream inFile2 (appendWithCWD("/branch.txt"));
    int p1 = cp.calculateBranchPenalty(highPerforming, inFile2);
    ifstream inFile3 (appendWithCWD("/branch.txt"));
    int p2 = cp.calculateBranchPenalty(lowPerforming, inFile3);
    cout << endl << "High performing core incurs branch penalty " << p1 << endl << "Low performing core incurs branch penalty " << p2 << endl;
    
    // handle loop penalties
    ifstream inFile4 (appendWithCWD("/loop.txt"));
    int p3 = cp.calculateLoopPenalty(highPerforming, inFile4);
    ifstream inFile5 (appendWithCWD("/loop.txt"));
    int p4 = cp.calculateLoopPenalty(lowPerforming, inFile5);
    cout << endl << "High performing core incurs loop penalty " << p3 << endl << "Low performing core incurs loop penalty " << p4 << endl;
    
    return 0;
}

