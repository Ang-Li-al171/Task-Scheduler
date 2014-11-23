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
    
    g.printGraph();
    
    cout << endl << "Graph has maximum depth " << g.maximumDepth << endl;
    
    return 0;
}

