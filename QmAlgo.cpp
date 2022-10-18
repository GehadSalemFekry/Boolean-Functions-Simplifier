#include "QmAlgo.h"

QmAlgo::QmAlgo(string in){
    fileName= in;
}




void QmAlgo::reduce(){
    




    for(auto it=Terms.begin(); it!=Terms.end();it++){
        Implicant pi;
        pi.addTerm(*it);
        primeImplicants
    }
}