#ifndef Implicant_H
#define Implicant_H

#include "Term.h"
#include <vector>

using namespace std;

class Implicant{
    int noTerms;

    set<Term> coveredTerms;

public:
    

    void addTerm(const Term& term);


    int getNoTerms();

    set<Term> getCoveredTerms();
};
#endif