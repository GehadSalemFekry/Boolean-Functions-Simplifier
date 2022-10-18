#ifndef QMALGO
#define QMALGO

#include <fstream>
#include <map>
#include <vector>
#include "implicant.h"
#include "term.h"

using namespace std;

// Term is the minterm and it is the smallest buiding block
// Using terms, we can build implicants to finally reach prime or essential prime implicants

class QmAlgo {
    int variables; // no of variables

    string fileName; // input file 

    fstream inputFile;


    map<Term, bool> Terms; // map to store the minTerms and don't care values

    vector<Implicant> primeImplicants;
    vector<Implicant> essentialPrimeImplicants;

    void reduce(); // Main Algorithm

public:
    QmAlgo(string in); // constructor to take the name of the input file

    void validate(); // validate the user's input and insert it in the Terms map



    void printPIs(); // print all prime Implicants

    void printEPIs(); // print all essential prime Implicants


    void PITable(); // print the prime Implicants table/chart


    void minmizedLogicExpression(); // get the very minimized logic expression of the function according to the PI table 

};

#endif