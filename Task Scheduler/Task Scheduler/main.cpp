//
//  main.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include <iostream>
#include "Graph.h"

int main(int argc, const char * argv[])
{

    // insert code here...
    
    Graph* g = new Graph();
    
    g->addVertex("V1");
    g->addVertex("V2");
    g->addVertex("V3");
    g->addVertex("V4");
    g->addVertex("V5");
    
    g->addEdge("V1", "V2", 1);
    g->addEdge("V2", "V3", 1);
    g->addEdge("V3", "V4", 1);
    g->addEdge("V4", "V5", 1);
    
    for(Graph::vmap::iterator itr = g->vertices.begin(); itr!= g->vertices.end(); itr++){
        cout << "vertex " << itr->second->name << " : " << endl;
        for(vector<vertex::ve>::iterator adjV = itr->second->adj.begin();
            adjV != itr->second->adj.end();
            adjV++){
            cout << "has neighbor " << adjV->second->name << endl;
        }
    }
    return 0;
}

