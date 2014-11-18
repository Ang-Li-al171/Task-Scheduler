//
//  main.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "Graph.h"
#include "DDependency.h"

const char* appendWithCWD(const char* fileName){
    char buffer[200];
    getcwd(buffer, 200);
    std::string file = std::string(buffer) + fileName;
    const char* filePath = file.c_str();
    return filePath;
}

int main(int argc, const char * argv[])
{
    
    // construct the data dependency graph
    DDependency dDependency;
    Graph g = dDependency.constructDependencyG(appendWithCWD("/input.txt"));
    
    // print out the data dependency graph for debugging
    for(Graph::vmap::iterator itr = g.vertices.begin(); itr!= g.vertices.end(); itr++){
        cout << "vertex " << itr->second->name << " : " << endl;
        for(vector<vertex::ve>::iterator adjV = itr->second->adj.begin();
            adjV != itr->second->adj.end();
            adjV++){
            cout << "has neighbor " << adjV->second->name << endl;
        }
    }
    
    
    return 0;
}

