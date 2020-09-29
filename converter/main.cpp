//
//  main.cpp
//  booleanConverter
//
//  Created by Daniel Lee on 9/29/20.
//  Copyright © 2020 Daniel Lee. All rights reserved.
//

#include "converter.hpp"

int main() {
    converter c("truthTable.txt");
    c.setSymbols(" and ", " or ", "not ");
    c.setNOTPosition(true);
    c.POS();
    c.printExpressions();
}
