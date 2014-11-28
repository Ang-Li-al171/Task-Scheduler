//
//  ControlPenalty.h
//  Task Scheduler
//
//  Created by Ang Li on 11/22/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#ifndef __Task_Scheduler__ControlPenalty__
#define __Task_Scheduler__ControlPenalty__

#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

struct processor{
    string name;
    int branchPenaltyPerMiss;
    processor(string s, int bp){
        name = s;
        branchPenaltyPerMiss = bp;
    }
};


class ControlPenalty{
    
public:
    
    ControlPenalty(void);
    pair<string,string> nextToken(string line, const string& delimiter);
    int calculateBranchPenalty(processor* p, ifstream& inFile);
    int calculateLoopPenalty(processor* p, ifstream& inFile);
    
};

#endif /* defined(__Task_Scheduler__ControlPenalty__) */
