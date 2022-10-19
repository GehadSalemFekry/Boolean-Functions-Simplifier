#ifndef QMALGO
#define QMALGO

#include <fstream>
#include <map>
#include <vector>
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

    // to be done: map to list all minterms and dont cares' numbers to retrieve them easily

    map<int,bool> Terms; // storing minterms and dont cares, such that false means dontcare


    map<Implicant, bool, comparatorImp> Implicants; // map to store the minImplicants and don't care values
    // istaken or not

    vector<Implicant> primeImplicants;
    vector<Implicant> essentialPrimeImplicants;

    void reduce(); // Main Algorithm

public:
    // QmAlgo(string in); // constructor to take the name of the input file

    void validate(); // validate the user's input and insert it in the Implicants map

    void populateMinterms(int variables, vector<int>& minterms, vector<int>& dontcares); // populate the map from values validated in the validation method

    // dont need to bother the print methods of PIs and EPIs with populating
    
    void populatePrimeImplicants();

    void populateEssentialPrimeImplicants(); 

    void printPIs(); // print all prime Implicants

    void printEPIs(); // print all essential prime Implicants


    void PITable(); // print the prime Implicants table/chart


    void minmizedLogicExpression(); // get the very minimized logic expression of the function according to the PI table 

};

#endif