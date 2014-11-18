//
//  Graph.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include "Graph.h"

Graph::Graph(void){}

void Graph::addVertex(const string &name){
    vmap::iterator itr = vertices.begin();
    itr = vertices.find(name);
    if(itr == vertices.end()){
        vertex *v;
        v = new vertex(name);
        vertices[name]=v;
        return;
    }
    cout << "\nVertex already exists!\n";
}

void Graph::addEdge(const string &from, const string &to, double cost){
    vertex *f = vertices.find(from)->second;
    vertex *t = vertices.find(to)->second;
    pair<int, vertex*> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}