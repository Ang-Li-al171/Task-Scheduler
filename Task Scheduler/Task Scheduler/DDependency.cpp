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

// register to line map: maps register name string to the line it's read/written, as a vertex ptr
typedef map<string,vertex*> r2lMap;
r2lMap read;
r2lMap written;

Graph dataG;


DDependency::DDependency(void){}

string replaceAll(string subject, const string& search, const string& replace){
    
    size_t pos = 0;
    while((pos=subject.find(search, pos)) != string::npos){
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

pair<string,string> nextToken(string line, const string& delimiter){
    size_t pos = line.find(delimiter);
    string token = line.substr(0, pos);
    line.erase(0, pos+delimiter.length());
    return make_pair(token, line);
}

string findRegInMemAddr(string memAddr){
    size_t pos = memAddr.find("(");
    size_t pos2 = memAddr.find(")");
    return memAddr.substr(pos+1, pos2-2);
}

vertex* writeDependency(const string& rd){
    r2lMap::iterator iter = read.find(rd);
    r2lMap::iterator iter2 = written.find(rd);
    if(iter!=read.end()){
        return iter->second;
    } else {
        if(iter2!=written.end()){
            return iter2->second;
        } else {
            return NULL;
        }
    }
}

vertex* readDependency(const string& r){
    r2lMap::iterator iter = written.find(r);
    if(iter!=read.end()){
        return iter->second;
    } else {
        return NULL;
    }
}

void rType(string line, const string& delimiter, const string& oriLine){
    
    pair<string,string> result;
    
    result = nextToken(line, delimiter);
    string rd = result.first;
    line = result.second;
    vertex* d = writeDependency(rd);
    if(d!=NULL){
        dataG.addEdge(d->name, oriLine, 1);
    }
    
    result = nextToken(line, delimiter);
    string rs = result.first;
    line = result.second;
    vertex* d2 = readDependency(rs);
    if(d2!=NULL){
        dataG.addEdge(d2->name, oriLine, 1);
    }
    
    result = nextToken(line, delimiter);
    string rt = result.first;
    line = result.second;
    vertex* d3 = readDependency(rt);
    if(d3!=NULL){
        dataG.addEdge(d3->name, oriLine, 1);
    }
    
    written[rd]=new vertex(oriLine);
    read[rs]=new vertex(oriLine);
    read[rt]=new vertex(oriLine);
    
    cout << rd << "+" << rs << "+" << rt << endl;
}

void iType(string line, const string& delimiter, const string& oriLine){
    
    pair<string,string> result;
    
    result = nextToken(line, delimiter);
    string rd = result.first;
    line = result.second;
    vertex* d = writeDependency(rd);
    if(d!=NULL){
        dataG.addEdge(d->name, oriLine, 1);
    }
    
    result = nextToken(line, delimiter);
    string rs = result.first;
    line = result.second;
    vertex* d2 = readDependency(rs);
    if(d2!=NULL){
        dataG.addEdge(d2->name, oriLine, 1);
    }
    
    written[rd]=new vertex(oriLine);
    read[rs]=new vertex(oriLine);
    
    cout << rd << "+" << rs << "+ " << endl;
}

void lwType(string line, const string& delimiter, const string& oriLine){
    
    pair<string,string> result;
    
    result = nextToken(line, delimiter);
    string rd = result.first;
    line = result.second;
    vertex* d = writeDependency(rd);
    if(d!=NULL){
        dataG.addEdge(d->name, oriLine, 1);
    }
    
    result = nextToken(line, delimiter);
    string rs = findRegInMemAddr(result.first);
    line = result.second;
    vertex* d2 = readDependency(rs);
    if(d2!=NULL){
        dataG.addEdge(d2->name, oriLine, 1);
    }
    
    written[rd]=new vertex(oriLine);
    read[rs]=new vertex(oriLine);
    
    cout << rd << "+" << rs << "+ " << endl;
}

void swType(string line, const string& delimiter, const string& oriLine){
    
    pair<string,string> result;
    
    result = nextToken(line, delimiter);
    string rs = result.first;
    line = result.second;
    vertex* d2 = readDependency(rs);
    if(d2!=NULL){
        dataG.addEdge(d2->name, oriLine, 1);
    }
    
    result = nextToken(line, delimiter);
    string rt = findRegInMemAddr(result.first);
    line = result.second;
    vertex* d3 = readDependency(rt);
    if(d3!=NULL){
        dataG.addEdge(d3->name, oriLine, 1);
    }
    
    read[rs]=new vertex(oriLine);
    read[rt]=new vertex(oriLine);
    
    cout << " " << "+" << rs << "+" << rt << endl;
}

Graph DDependency::constructDependencyG(ifstream& inFile){
    
    string line;
    int instrCnt = 0;
    
    if(inFile.is_open()){
        while(getline(inFile,line)){
            // clean up the line from raw input
            line = replaceAll(line, ",", "");
            
            // take the instr name from instruction first
            string delimiter = " ";
            string currToken;
            
            string originalLine = line;
            dataG.addVertex(line);
            
            pair<string,string> result = nextToken(line, delimiter);
            currToken = result.first;
            line = result.second;
            
            // tokenize the line, and deal with the instruction, assuming space delimited
            if(currToken.compare("add")==0 || currToken.compare("sub")==0
               || currToken.compare("mult")==0 || currToken.compare("div")==0){
                instrCnt++;
                rType(line, delimiter, originalLine);
            }
            else if(currToken.compare("addi")==0 || currToken.compare("subi")==0
                    || currToken.compare("multi")==0 || currToken.compare("divi")==0){
                instrCnt++;
                iType(line, delimiter, originalLine);
            }
            else if (currToken.compare("beq")==0 || currToken.compare("blt")==0 ||
                     currToken.compare("bgt")==0 || currToken.compare("bge")==0 ||
                     currToken.compare("ble")==0){
                instrCnt++;
                iType(line, delimiter, originalLine);
            }
            else if(currToken.compare("sw")==0){
                instrCnt++;
                swType(line, delimiter, originalLine);
            }
            else if(currToken.compare("lw")==0){
                instrCnt++;
                lwType(line, delimiter, originalLine);
            }
            else if(currToken.compare("addiu")==0 || currToken.compare("la")==0 ||
                    currToken.compare("li")==0 || currToken.compare("syscall")==0 ||
                    currToken.compare("move")==0 || currToken.compare("jr")==0 ||
                    currToken.compare("andi")==0 || currToken.compare("b")==0 ||
                    currToken.compare("j")==0 ){
                instrCnt++;
            }
        }
        
        dataG.instrCount = instrCnt;
        cout << "number of instr is " << instrCnt << endl;
        inFile.close();
        
    } else {
        cout << "Failure trying to read from input file" << endl;
    }
    
    return dataG;
}