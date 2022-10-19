#include "QmAlgo.h"

// QmAlgo::QmAlgo(string in){
//     fileName= in;
// }




void QmAlgo::populateMinterms(int variables, vector<int>& minterms, vector<int>& dontcares){

    for(int min: minterms){
        Implicant imp(variables, min);
        Implicants[imp]=false;
        Terms[min]=true;
    }
    
    for(int dont: dontcares){
        Implicant imp(variables, dont);
        Implicants[imp]=false;
        Terms[dont]=false;
    }

}

// void QmAlgo::validate(){
    
// }

void QmAlgo::reduce(){
    

    // int stringSize= variables;

    map<Implicant, bool, comparatorImp> merged = Implicants; // map to store the minImplicants and don't care values
    while (!merged.empty()) {

        map<Implicant, bool, comparatorImp> newlyMerged;

        for (auto cur : merged) {
            Implicant imp = cur.first; // to change its bits and check its availability in the map

            for(int i = 0; i < variables; i++) {
                Implicant temp = imp; 
                if(imp[i] == '0' || imp[i] == '1') {

                    temp.changeBit(i);

                    auto it = merged.find(temp); // in need for the key itself to retrieve its values, such as its covered terms


                    if(it!=merged.end() && !it->second) { // check if the implicant exists && if it is visited before or not


                        Implicant foundImplicant = it->first; // implicant to merge with

                        string newBinary = temp.replace_complements(i);

                        set<int> mergedSet = imp.getCoveredTerms();
                        set<int> coveredTerms2 = foundImplicant.getCoveredTerms();

                        mergedSet.insert(coveredTerms2.begin(), coveredTerms2.end()); // merge the two sets


                        Implicant mergedB(newBinary, mergedSet); // to be done: add covered, add dont care



                        // Merged
                        cur.second = true; // current element that we are iterating over its bits is checked
                        it->second = true; // implicant to merge with is also done( have to do it through the iterator to change the value in the map itself)

                        newlyMerged[mergedB] = false;
                    }
                }
            }
        }
        merged = newlyMerged;
        for(auto imp: merged)
            Implicants.insert(imp);
    }
}

void QmAlgo::populatePrimeImplicants(){
    for (auto imp: Implicants){
        if (imp.second)
            primeImplicants.push_back(imp.first);
    }
}

void QmAlgo::printPIs(){
    cout << "\t\t\tPrime Implicants\n"; // centered


    cout << " Prime Implicant\t\t\t\t\t" << " Minterms Covered\t\t\t" << " DontCares Covered\n";
    cout << "Binary Representation" << "Term\n"; 
    for(auto it: primeImplicants){ 
        cout << it.getBin() << "  " << it.getName();
        cout << "\t\t\t";

        set<int> coveredTerms=it.getCoveredTerms();

        // minterms
        for (auto minterm:coveredTerms){
            if (Terms[minterm]) {
                cout << minterm << ",";
            }
            cout << '\n';
        }
        

        // dontcares
        for (auto dontcare:coveredTerms){
            if (!Terms[dontcare]) {
                cout << dontcare << ",";
            }
            cout << '\n';
        }
    }
}