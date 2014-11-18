//
//  DDependency.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/17/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include "DDependency.h"
#include <map>
#include <string>
#include <fstream>

DDependency::DDependency(void){}

std::string replaceAll(std::string subject, const std::string& search, const std::string& replace){
    
    size_t pos = 0;
    while((pos=subject.find(search, pos)) != std::string::npos){
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

pair<std::string,std::string> nextToken(std::string line, const std::string& delimiter){
    size_t pos = line.find(delimiter);
    std::string token = line.substr(0, pos);
    line.erase(0, pos+delimiter.length());
    return make_pair(token, line);
}

void rType(map<string,vertex*> read, map<string,vertex*> written, string line, const string& delimiter){
    
    pair<std::string,std::string> result;
    
    result = nextToken(line, delimiter);
    std::string rd = result.first;
    line = result.second;
    
    result = nextToken(line, delimiter);
    std::string rs = result.first;
    line = result.second;
    
    result = nextToken(line, delimiter);
    std::string rt = result.first;
    line = result.second;
    
    cout << rd << "+" << rs << "+" << rt << endl;
}

void iType(map<string,vertex*> read, map<string,vertex*> written, string line, const string& delimiter){
    
    pair<std::string,std::string> result;
    
    result = nextToken(line, delimiter);
    std::string rd = result.first;
    line = result.second;
    
    result = nextToken(line, delimiter);
    std::string rs = result.first;
    line = result.second;
    
    cout << rd << "+" << rs << "+ " << endl;
}

void lwType(map<string,vertex*> read, map<string,vertex*> written, string line, const string& delimiter){
    
    pair<std::string,std::string> result;
    
    result = nextToken(line, delimiter);
    std::string rd = result.first;
    line = result.second;
    
    result = nextToken(line, delimiter);
    std::string rs = result.first;
    line = result.second;
    
    cout << rd << "+" << rs << "+ " << endl;
}

void swType(map<string,vertex*> read, map<string,vertex*> written, string line, const string& delimiter){
    
    pair<std::string,std::string> result;
    
    result = nextToken(line, delimiter);
    std::string rs = result.first;
    line = result.second;
    
    result = nextToken(line, delimiter);
    std::string rt = result.first;
    line = result.second;
    
    cout << " " << "+" << rs << "+" << rt << endl;
}

Graph DDependency::constructDependencyG(const string &instrFile){
    
    // register to line map: maps register name string to the line it's read/written
    typedef map<string,vertex*> r2lMap;
    r2lMap read;
    r2lMap written;
    
    // for file inputs
    string line;
    ifstream inFile (instrFile);
    
    if(inFile.is_open()){
        while(getline(inFile,line)){
            // clean up the line from raw input
            line = replaceAll(line, ",", "");
            
            // take the instr name from instruction first
            std::string delimiter = " ";
            std::string currToken;
            
            pair<std::string,std::string> result = nextToken(line, delimiter);
            currToken = result.first;
            line = result.second;
            
            // tokenize the line, and deal with the instruction, assuming space delimited
            if(currToken.compare("add")==0){
                rType(read, written, line, delimiter);
            }
            else if(currToken.compare("addi")==0){
                iType(read, written, line, delimiter);
            }
            else if(currToken.compare("sw")==0){
                swType(read, written, line, delimiter);
            }
            else if(currToken.compare("lw")==0){
                lwType(read, written, line, delimiter);
            }
            else if(currToken.compare("mult")==0){
                rType(read, written, line, delimiter);
            }
        }
        inFile.close();
        
    } else {
        cout << "Failure trying to read from input file" << endl;
    }
    
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