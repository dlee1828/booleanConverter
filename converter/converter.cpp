//
//  converter.cpp
//  booleanConverter
//
//  Created by Daniel Lee on 9/29/20.
//  Copyright © 2020 Daniel Lee. All rights reserved.
//

#include "converter.hpp"

converter::converter(string f){
    inputFileName = f;
}

string converter::NOT(string s){
    string ans = "";
    if(notBefore){
        ans.append(NOTb);
        ans.append(s);
    }
    else{
        ans.append(s);
        ans.append(NOTa);
    }
    return ans;
}

void converter::setSymbols(string a, string o, string n){
    AND = a;
    OR = o;
    NOTa = n;
    NOTb = n;
}

void converter::setNOTPosition(bool before){
    notBefore = before;
}

void converter::read(){
    inFile.open(inputFileName);
    
    //reading variables
    string temp;
    inFile >> numIn >> numOut;
    lp(i, numIn){
        inFile >> temp;
        inVars.push_back(temp);
    }
    lp(i, numOut){
        inFile >> temp;
        outVars.push_back(temp);
    }
    //reading bits
    string line;
    stringstream ss;
    int bit;
    inBits.resize(numIn);
    outBits.resize(numOut);
    inFile.ignore();
    while (getline(inFile, line)) {
        ss.clear();
        ss.str(line);
        lp(i, numIn){ //push_back the bit that is read
            ss >> bit;
            inBits[i].push_back(bit);
        }
        lp(i, numOut){
            ss >> bit;
            outBits[i].push_back(bit);
        }
    }
    rows = (int)inBits[0].size();
    
    inFile.close();
}

string converter::oneSOP(int n){
    string exp = ""; //expression
    vector<int> vals = outBits[n]; //output column;
    int inVal; //input value;
    string term; //single term in sum
    
    lp(i, rows){
        if(vals[i] == 0) continue;
        term = "(";
        lp(j, numIn){
            inVal = inBits[j][i];
            if(j > 0) term.append(AND);
            if(inVal == 0) term.append(NOT(inVars[j]));
            else term.append(inVars[j]);
        }
        term.push_back(')');
        if(exp != "") exp.append(OR);
        exp.append(term);
    }
    
    if(exp == "") return "0";
    
    return exp;
}

string converter::onePOS(int n){
    string exp = ""; //expression
    vector<int> vals = outBits[n]; //output column;
    int inVal; //input value;
    string term; //single term in sum
    
    lp(i, rows){
        if(vals[i] == 1) continue;
        term = "(";
        lp(j, numIn){
            inVal = inBits[j][i];
            if(j > 0) term.append(OR);
            if(inVal == 0) term.append(inVars[j]);
            else term.append(NOT(inVars[j]));
        }
        term.push_back(')');
        if(exp != "") exp.append(AND);
        exp.append(term);
    }
    
    if(exp == "") return "1";
    
    return exp;
}

void converter::createAllExpressions(){
    //puts all expressions into 1 string;
    lp(i, numOut){
        allExpressions.append(outVars[i] + " = " + expressions[i] + "\n");
    }
}

void converter::SOP(){
    read();
    lp(i, numOut){
        expressions.push_back(oneSOP(i));
    }
    createAllExpressions();
}

void converter::POS(){
    read();
    lp(i, numOut){
        expressions.push_back(onePOS(i));
    }
    createAllExpressions();
}

void converter::printExpressions(string outputFileName){
    outFile.open(outputFileName);
    
    outFile << allExpressions;
    
    outFile.close();
}
