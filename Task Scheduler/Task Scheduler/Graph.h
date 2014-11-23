//
//  Graph.h
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#ifndef __Task_Scheduler__Graph__
#define __Task_Scheduler__Graph__

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj;
    string name;
    vertex(string s){
        name = s;
    }
};

class Graph{
    
public:
    
    Graph(void);
    typedef map<string, vertex*> vmap;
    vmap vertices;
    void addVertex(const string&);
    void addEdge(const string& from, const string& to, double cost);
    void printGraph(void);
};

#endif /* defined(__Task_Scheduler__Graph__) */
