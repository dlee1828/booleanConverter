//
//  converter.hpp
//  booleanConverter
//
//  Created by Daniel Lee on 9/29/20.
//  Copyright © 2020 Daniel Lee. All rights reserved.
//

#ifndef converter_hpp
#define converter_hpp

#include "define.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class converter{
private:
    ifstream inFile;
    ofstream outFile;
    string inputFileName;
    int numIn; //number of input variables
    int numOut; //number of output variables
    vector<string> inVars;
    vector<string> outVars;
    int rows; //number of rows in truth table
    vector<vector<int>> inBits; //the input section of the truth table; v[0] = column 0
    vector<vector<int>> outBits; //the output section; v[0] = column 0
    
    string NOT(string s); //to get not s
    void read();
    string oneSOP(int n); //SOP for output variable of index n
    string onePOS(int n);
    void createAllExpressions();
    
public:
    vector<string> expressions; //expressions for each output var
    string allExpressions;
    string AND = ""; //the string used to represent AND
    string OR = " + "; //the string used to represent OR
    string NOTb = "!"; //string for NOT when it comes before the variable
    string NOTa = "'"; //string for NOT when it comes after the variable
    bool notBefore = true; //which NOT to use
    
    converter(string f);
    void setSymbols(string a, string o, string n); //setting the values of logic symbols
    void setNOTPosition(bool before);
    void SOP();
    void POS();
    void printExpressions(string outputFileName);
};

#endif /* converter_hpp */
