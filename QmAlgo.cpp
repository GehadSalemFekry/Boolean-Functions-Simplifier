#include "QmAlgo.h"

QmAlgo::QmAlgo(string in){
    fileName= in;
}




void QmAlgo::reduce(){
    

    int stringSize= variables;


    map<Implicant, bool> merged = Implicants; // map to store the minImplicants and don't care values
    while (!merged.empty()) {
        map<Implicant, bool> newlyMerged;
        for (auto cur : merged) {
            // Implicant& imp = it.first; // to easily traverse the implicant
            Implicant imp = cur.first; // to change its bits and check its availability in the map
            for(int i = 0; i < variables; i++) {
                Implicant temp = imp; 
                if(imp[i] == '0') {
                    imp.changeBit(i);
                    if(merged.count(imp)) {
                        string newBinary = temp.replace_complements(i);
                        Implicant mergedB(newBinary); // to be done: add covered, add dont care

                        // Merged
                        cur.second = true;
                        merged[imp] = true;

                        newlyMerged[mergedB] = false;
                    }
                    temp.changeBit(i);
                }
            }
            // to be reconsidered: remove the element after finishing it.
        }
        merged = newlyMerged;
        // add all elements in merged to implicants
    }
   

    for(auto it=Implicants.begin();it!=Implicants.end();it++){
        
    }
}