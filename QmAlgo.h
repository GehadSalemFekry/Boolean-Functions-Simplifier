#ifndef QMALGO_H
#define QMALGO_H

#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "Implicant.h"

using namespace std;

/*
Naming Convention:
 - Maps are capitalized
 - Vectors are camelCased
*/

struct comparatorImp {
    bool operator()(const Implicant &a, const Implicant &b) const {
        return a.binary < b.binary;
    }
};

class QmAlgo {
    int variables; // no of variables

    string fileName; // input file 
    fstream inputFile;

    map<int, bool> TERMS; // storing minterms and dont cares, such that false means dontcare
    map<Implicant, bool, comparatorImp> IMPLICANTS; // map to store the minImplicants (bool: istaken or not)
    map<int, vector<Implicant>> COVERSOVERMINTERM;
    map<int, bool> isMINTERMCOVERED;

    vector<Implicant> PrimeImplicants;
    vector<Implicant> EssentialPrimeImplicants;
    vector<Implicant> ReducedExpression;

    void reduce(); // Main Algorithm

public:
    QmAlgo(int variables, vector<int>& minterms, vector<int>& dontcares); // populate the map from values validated in the validation method
    
    void populatePrimeImplicants();
    void populateEssentialPrimeImplicants();

    void printPIs(); // print all prime Implicants
    void printEPIs(); // print all essential prime Implicants
    
    void generateMinmizedLogicExpression(); // get the very minimized logic expression of the function according to the PI table
    void runAlgo(); 
};

#endif