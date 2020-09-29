//
//  main.cpp
//  booleanConverter
//
//  Created by Daniel Lee on 9/29/20.
//  Copyright © 2020 Daniel Lee. All rights reserved.
//

#include "converter.hpp"

int main() {
    converter c("truthTables/table1.txt");
    c.SOP();
    c.printExpressions("outputFiles/expressions1.txt");
    
    c = converter("truthTables/table2.txt");
    c.setSymbols(" and ", " or ", "not ");
    c.setNOTPosition(true);
    c.POS();
    c.printExpressions("outputFiles/expressions2.txt");
    
    c = converter("truthTables/table3.txt");
    c.setNOTPosition(true);
    c.setSymbols(" ^ ", " v ", "¬ ");
    c.SOP();
    c.printExpressions("outputFiles/expressions3.txt");
}
