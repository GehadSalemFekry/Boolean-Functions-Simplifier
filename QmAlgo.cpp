#include "QmAlgo.h"

QmAlgo::QmAlgo(int variables, vector<int>& minterms, vector<int>& dontcares){
    this->variables = variables;
    for(int min: minterms){
        Implicant imp(variables, min);
        IMPLICANTS[imp]=false;
        TERMS[min]=true;
    }
    
    for(int dont: dontcares){
        Implicant imp(variables, dont);
        IMPLICANTS[imp]=false;
        TERMS[dont]=false;
    }
}

void QmAlgo::reduce(){
    // map to store the minImplicants and don't care values
    map<Implicant, bool, comparatorImp> merged = IMPLICANTS;
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

                        Implicant mergedB(newBinary, mergedSet);
                        
                        // Merged
                        merged[cur.first] = true; // current element that we are iterating over its bits is checked
                        merged[temp] = true; // implicant to merge with is also done( have to do it through the iterator to change the value in the map itself)

                        newlyMerged[mergedB] = false;
                    }
                }
            }
        }
        
        for(auto imp: merged) // Update previous values of implicants 
            IMPLICANTS[imp.first] = imp.second;
        for(auto imp: newlyMerged) // Add new values
            IMPLICANTS[imp.first] = imp.second;

        merged = newlyMerged;
    }
}

void QmAlgo::populatePrimeImplicants(){
    for (auto imp: IMPLICANTS){

        bool checkAllDontCare = false; // check if the implicant has dontcares only
        for(auto term: imp.first.getCoveredTerms()){
            if(!checkAllDontCare)
                checkAllDontCare=checkAllDontCare||TERMS[term];  // as long as term is a dontcare, keep looping until at least encountering one single minterm
        }

        if(checkAllDontCare)
            if (!imp.second)
                PrimeImplicants.push_back(imp.first);
    }
}

void QmAlgo::populateEssentialPrimeImplicants() {


    map<int, int> numOfCoversPerTerm;

    //check all covered terms in all implicants and record the frequency of each term
    for (auto imp : PrimeImplicants) {
        for (int term : imp.getCoveredTerms()) {
            if (COVERSOVERMINTERM.count(term)) COVERSOVERMINTERM[term].push_back(imp);
            else COVERSOVERMINTERM[term] = {imp};

            numOfCoversPerTerm[term]++;
            if (TERMS[term]) isMINTERMCOVERED[term] = false;
        }
    }

    //if the frequenncy of the term is 1 then its cover is an EPI
    set<Implicant, comparatorImp> essentialPIs;
    for (auto imp : PrimeImplicants) 
        for (int term : imp.getCoveredTerms()) 
            if (TERMS[term] && numOfCoversPerTerm[term] == 1) essentialPIs.insert(imp);

    EssentialPrimeImplicants.assign(essentialPIs.begin(), essentialPIs.end()); // To make sure there is not EPI duplicated

    for (auto essential : EssentialPrimeImplicants) 
        for (int term : essential.getCoveredTerms()) isMINTERMCOVERED[term] = true;

    //reduce the Boolean expression
    //find the minterm not covered by the EPIs and find the biggest PI that covers these terms
    for (auto term : isMINTERMCOVERED) {
        if (!term.second) {
            int mxNotCovered = 0;
            Implicant toInclude;
            for (auto imp : COVERSOVERMINTERM[term.first]) {
                int curNotCovered = 0;
                for (int u : imp.getCoveredTerms()) {
                    if (TERMS[u] && !isMINTERMCOVERED[u]) curNotCovered++;
                }
                if (curNotCovered > mxNotCovered) {
                    mxNotCovered = curNotCovered;
                    toInclude = imp;
                }
            }
            essentialPIs.insert(toInclude); // these aren't EPIs but to be added to the minimized expression
            for (int u : toInclude.getCoveredTerms()) isMINTERMCOVERED[u] = true;
        }
    }

    ReducedExpression.assign(essentialPIs.begin(), essentialPIs.end());

}

void QmAlgo::printPIs(){
    cout << "\t\t\t\t\tPrime IMPLICANTS\n\n"; // centered

    cout << "Prime Implicant\t\t\t" << "Minterms Covered\t\t" << "Don't Cares Covered\n";
    cout << "Binary Representation\t\t" << "Term\n"; 
    for(auto prime: PrimeImplicants){ 
        cout << prime.getBin() << "\t\t\t\t" << prime.getName() << "\t\t";

        set<int> coveredTerms = prime.getCoveredTerms();
        // minterms
        for (auto minterm : coveredTerms)
            if (TERMS[minterm]) 
                cout << minterm << ", ";
        cout << "\t\t\t\t";

        // dontcares
        for (auto dontcare : coveredTerms)
            if (!TERMS[dontcare]) 
                cout << dontcare << ", ";
    
        cout << "\n";
    }

    cout << "___________________________________________________________________________________________________\n\n";
}

void QmAlgo::printEPIs(){
    cout << "\t\t\t\t   Essential Prime IMPLICANTS\n\n"; // centered

    cout << "\tEssential Prime Implicant\t\t" << "Minterms Covered\t\t" << "Don't Cares Covered\n";
    cout << "Binary Representation\t\t" << "Term\n"; 
    for(auto prime: EssentialPrimeImplicants){ 
        cout << prime.getBin() << "\t\t\t\t" << prime.getName() << "\t\t";

        set<int> coveredTerms = prime.getCoveredTerms();
        // minterms
        for (auto minterm : coveredTerms)
            if (TERMS[minterm]) 
                cout << minterm << ", ";
        cout << "\t\t\t\t";

        // dontcares
        for (auto dontcare : coveredTerms)
            if (!TERMS[dontcare]) 
                cout << dontcare << ", ";
    
        cout << "\n";
    }

    cout << "___________________________________________________________________________________________________\n\n";
}


void QmAlgo::generateMinmizedLogicExpression() {
    cout << "\t\t\t   The Overall Reduced Boolean Expression is:\n"; // centered
    
    for (int i = 0; i < ReducedExpression.size(); i++) {
        cout << ReducedExpression[i].name;
        if (i != ReducedExpression.size() - 1) cout << " + ";
    }
    cout << "\n";
}

void QmAlgo::runAlgo() {
    reduce();
    populatePrimeImplicants();
    printPIs();
    populateEssentialPrimeImplicants();
    printEPIs();
    generateMinmizedLogicExpression();
}
