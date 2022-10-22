#include "QmAlgo.h"

// QmAlgo::QmAlgo(string in){
//     fileName= in;
// }




void QmAlgo::populateMinterms(int variables, vector<int>& minterms, vector<int>& dontcares){
    this->variables = variables;
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

void QmAlgo::reduce(){
    // map to store the minImplicants and don't care values
    map<Implicant, bool, comparatorImp> merged = Implicants;
    while (!merged.empty()) {
        map<Implicant, bool, comparatorImp> newlyMerged;

        for (auto &cur : merged) {
            Implicant imp = cur.first; // to change its bits and check its availability in the map

            for(int i = 0; i < variables; i++) {
                Implicant temp = imp; 
                if(imp[i] == '0') {
                    temp.changeBit(i);

                    // check if the implicant exists
                    if(merged.count(temp)) { 
                        string newBinary = temp.replace_complements(i);
                        
                        Implicant found = merged.find(temp)->first; // in need for the key itself to retrieve its values, such as its covered terms

                        set<int> mergedSet = imp.getCoveredTerms();
                        set<int> coveredTerms2 = found.getCoveredTerms();
                        mergedSet.insert(coveredTerms2.begin(), coveredTerms2.end()); // merge the two sets

                        Implicant mergedB(newBinary, mergedSet); // to be done: add covered, add dont care
                        
                        // Merged
                        merged[cur.first] = true; // current element that we are iterating over its bits is checked
                        merged[temp] = true; // implicant to merge with is also done( have to do it through the iterator to change the value in the map itself)

                        newlyMerged[mergedB] = false;
                    }
                }
            }
        }
        
        for(auto imp: merged) // Update previous values of implicants 
            Implicants[imp.first] = imp.second;
        for(auto imp: newlyMerged) // Add new values
            Implicants[imp.first] = imp.second;

        merged = newlyMerged;
    }
}

void QmAlgo::populatePrimeImplicants(){
    for (auto imp: Implicants){
        if (!imp.second) // to be done: check if all terms of the implicants are dontcares, so dont add this implicant
            primeImplicants.push_back(imp.first);
    }
}

void QmAlgo::populateEssentialPrimeImplicants() {
    // map<int, pairimp> table;

    // for (auto imp : primeImplicants) {
    //     for (int term : imp.getCoveredTerms()) {
    //     map<int, pairimp> :: iterator it = table.find(term);
    //         it->second.frequency++;
    //         it->second.implicant = imp;
    //     }
    // }

    map<int, int> numOfCoversPerTerm;

    for (auto imp : primeImplicants) {
        for (int term : imp.getCoveredTerms()) {
            if (coversOverMinterms.count(term)) coversOverMinterms[term].push_back(imp);
            else coversOverMinterms[term] = {imp};

            numOfCoversPerTerm[term]++;
            if (Terms[term]) isMinTermCovered[term] = false;
        }
    }

    set<Implicant, comparatorImp> essentialPIs;
    for (auto imp : primeImplicants) 
        for (int term : imp.getCoveredTerms()) 
            if (Terms[term] && numOfCoversPerTerm[term] == 1) essentialPIs.insert(imp);

    essentialPrimeImplicants.assign(essentialPIs.begin(), essentialPIs.end()); // To make sure there is not EPI duplicated

    for (auto essential : essentialPrimeImplicants) 
        for (int term : essential.getCoveredTerms()) isMinTermCovered[term] = true;

    for (auto term : isMinTermCovered) {
        if (!term.second) {
            int mxNotCovered = 0;
            Implicant toInclude;
            for (auto imp : coversOverMinterms[term.first]) {
                int curNotCovered = 0;
                for (int u : imp.getCoveredTerms()) {
                    if (Terms[u] && !isMinTermCovered[u]) curNotCovered++;
                }
                if (curNotCovered > mxNotCovered) {
                    mxNotCovered = curNotCovered;
                    toInclude = imp;
                }
            }
            essentialPIs.insert(toInclude); // these aren't EPIs but to be added to the minimized expression
        }
    }

    reducedExpression.assign(essentialPIs.begin(), essentialPIs.end());
    
    // vector<int> mintermscovered;
    // for (auto it : table) {
    //     if (it.second.frequency == 1) {
    //         essentialPrimeImplicants.push_back(it.second.implicant);
    //         mintermscovered.insert(mintermscovered.end(), it.second.implicant.coveredTerms.begin(), it.second.implicant.coveredTerms.end());
    //     }
    // }

    // for (int i : minterms) {
    //     if (find(mintermscovered.begin(), mintermscovered.end(), i) == mintermscovered.end()) mintermsnotcovered.push_back(i);
    // }
}

void QmAlgo::printPIs(){
    cout << "\t\t\tPrime Implicants\n"; // centered

    cout << "\t\tPrime Implicant\t\t\t" << "Minterms Covered\t\t" << "Don't Cares Covered\n";
    cout << "Binary Representation\t\t" << "Term\n"; 
    for(auto prime: primeImplicants){ 
        cout << prime.getBin() << "\t\t\t\t" << prime.getName() << "\t\t";

        set<int> coveredTerms = prime.getCoveredTerms();
        // minterms
        for (auto minterm : coveredTerms)
            if (Terms[minterm]) 
                cout << minterm << ", ";
        cout << "\t\t\t\t";

        // dontcares
        for (auto dontcare : coveredTerms)
            if (!Terms[dontcare]) 
                cout << dontcare << ", ";
    
        cout << "\n";
    }

    cout << "___________________________________________________________________________________________________\n\n";
}

void QmAlgo::printEPIs(){
    cout << "\t\t\tEssential Prime Implicants\n"; // centered

    cout << "\tEssential Prime Implicant\t\t" << "Minterms Covered\t\t" << "Don't Cares Covered\n";
    cout << "Binary Representation\t\t" << "Term\n"; 
    for(auto prime: essentialPrimeImplicants){ 
        cout << prime.getBin() << "\t\t\t\t" << prime.getName() << "\t\t";

        set<int> coveredTerms = prime.getCoveredTerms();
        // minterms
        for (auto minterm : coveredTerms)
            if (Terms[minterm]) 
                cout << minterm << ", ";
        cout << "\t\t\t\t";

        // dontcares
        for (auto dontcare : coveredTerms)
            if (!Terms[dontcare]) 
                cout << dontcare << ", ";
    
        cout << "\n";
    }

    cout << "___________________________________________________________________________________________________\n\n";
}


void QmAlgo::generateMinmizedLogicExpression() {
    cout << "\t\t\tThe Overall Reduced Boolean Expression is:\n"; // centered
    for (int i = 0; i < reducedExpression.size(); i++) {
        cout << reducedExpression[i].name;
        if (i != reducedExpression.size() - 1) cout << " + ";
    }
    cout << "\n";
    cout << "___________________________________________________________________________________________________\n\n";
}

void QmAlgo::runAlgo() {
    reduce();
    populatePrimeImplicants();
    printPIs();
    populateEssentialPrimeImplicants();
    printEPIs();
    generateMinmizedLogicExpression();
}