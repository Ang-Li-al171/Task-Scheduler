//
//  ControlPenalty.cpp
//  Task Scheduler
//
//  Created by Ang Li on 11/22/14.
//  Copyright (c) 2014 Ang Li. All rights reserved.
//

#include "ControlPenalty.h"
#include <fstream>
#include <string>

typedef map<string,string> strMap;
strMap labelToLoopCount;

Graph controlFlowG;

ControlPenalty::ControlPenalty(void){}

pair<string,string> ControlPenalty::nextToken(string line, const string& delimiter){
    size_t pos = line.find(delimiter);
    string token = line.substr(0, pos);
    line.erase(0, pos+delimiter.length());
    return make_pair(token, line);
}

int ControlPenalty::calculateBranchPenalty(processor* p, ifstream& inFile){
    
    string line;
    
    int branchInstrCount = 0;
    int totalInstrCount = 0;
    
    if(inFile.is_open()){
        while(getline(inFile,line)){
            
            // take the instr name from instruction first
            string delimiter = " ";
            string currToken;
            
            pair<string,string> result = nextToken(line, delimiter);
            currToken = result.first;
            
            totalInstrCount++;
            
            if(currToken.compare("beq") == 0 || currToken.compare("blt") == 0
               || currToken.compare("bgt") == 0 || currToken.compare("bge") == 0
               || currToken.compare("ble") == 0){
                branchInstrCount++;
            }
        }
        inFile.close();
    }
    
    return (p->branchPenaltyPerMiss)*branchInstrCount;
}

int ControlPenalty::calculateLoopPenalty(processor* p, ifstream& inFile){
    
    string line;
    string lastLine = "";
    int totalPenalty = 0;
    
    if(inFile.is_open()){
        while(getline(inFile,line)){
            
            // take the instr name from instruction first
            string delimiter = " ";
            string currToken;
            pair<string,string> result = nextToken(line, delimiter);
            currToken = result.first;
            
            if(currToken.find(":") == currToken.length()-1){
                labelToLoopCount[currToken.substr(0, currToken.length()-1)]=lastLine;
            }
            
            if(currToken.compare("beq") == 0 || currToken.compare("blt") == 0
               || currToken.compare("bgt") == 0 || currToken.compare("bge") == 0
               || currToken.compare("ble") == 0){
                
                string label = nextToken(nextToken(nextToken(result.second, delimiter).second, delimiter).second, delimiter).first;
                strMap::iterator mapItr = labelToLoopCount.find(label);
                if(mapItr != labelToLoopCount.end()){
                    string numIteration = mapItr->second;
//                    cout << "loop " << label << " runs " << numIteration << " times..." << endl;
                    totalPenalty += p->branchPenaltyPerMiss*atoi(numIteration.c_str());
                }
            }
            
            if(currToken.compare("j") == 0 || currToken.compare("b") == 0){
                
                string label = nextToken(result.second, delimiter).first;
                strMap::iterator mapItr = labelToLoopCount.find(label);
                if(mapItr != labelToLoopCount.end()){
                    string numIteration = mapItr->second;
                    //                    cout << "loop " << label << " runs " << numIteration << " times..." << endl;
                    totalPenalty += p->branchPenaltyPerMiss*atoi(numIteration.c_str());
                }
            }
            
            lastLine = result.second; // this is what's left after useful tokens
            
        }
        inFile.close();
    }
    
    return totalPenalty;
}