//
//  DDependency.h
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#ifndef __Task_Scheduler__DDependency__
#define __Task_Scheduler__DDependency__

#include <iostream>
#include "Graph.h"

class DDependency{
    
public:
    
    DDependency(void);
    Graph constructDependencyG(const string&);
    
};

#endif /* defined(__Task_Scheduler__DDependency__) */
