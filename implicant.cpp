#include "Implicant.h"


void Implicant::addTerm(const Term& term){
    coveredTerms.insert(term);
}

int Implicant::getNoTerms(){
    return this->noTerms;
}


set<Term> Implicant::getCoveredTerms(){
    return this->coveredTerms;
}