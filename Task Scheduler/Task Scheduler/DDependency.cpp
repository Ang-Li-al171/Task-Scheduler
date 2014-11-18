//
//  DDependency.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include "DDependency.h"

DDependency::DDependency(void){}

Graph DDependency::constructDependencyG(const FILE* instrFile){
    
    Graph g;
    
    g.addVertex("V1");
    g.addVertex("V2");
    g.addVertex("V3");
    g.addVertex("V4");
    g.addVertex("V5");
    
    g.addEdge("V1", "V2", 1);
    g.addEdge("V2", "V3", 1);
    g.addEdge("V3", "V4", 1);
    g.addEdge("V4", "V5", 1);
    
    return g;
}