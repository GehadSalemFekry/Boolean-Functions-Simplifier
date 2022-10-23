#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>

#include "Implicant.cpp"
#include "QmAlgo.cpp"

using namespace std;

int Partition(vector<int>& x, int begin, int end) {
	int Pivot = begin + (end - begin) / 2;
	int PivotValue = x[Pivot];
	int i = begin, j = end;
	int temp;
	while (i <= j) {
		while (x[i] < PivotValue) {
			i++;
		}
		while (x[j] > PivotValue) {
			j--;
		}
		if (i <= j) {
			temp = x[i];
			x[i] = x[j];
			x[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}

void Quicksort(vector<int>& x, int begin, int end) {
	if (begin < end) {
		int Pivot = Partition(x, begin, end);
		Quicksort(x, begin, Pivot - 1);
		Quicksort(x, Pivot, end);
	}
}

//checks if there is a repetition in any of the terms of the two vectors
bool repetition(vector<int> M, vector<int> DC) {
	int i = 0, j = 0;
		while (i < M.size() && j < DC.size()) {
			if (M[i] < DC[j])
				i++;
			else if (M[i] > DC[j])
				j++;
			else if (M[i] == DC[j])
				return true;
		}

	return false;
}

// Makes sure that all minterms and don't cares are within range
bool validate(int NoV, vector<int> M, vector<int> DC) {
	int Total = pow(2, NoV);
	for (int i : M) {
		if (i >= Total) return false;
	}

	for (int i : DC) {
		if (i >= Total) return false;
	}

	// Sort the two vectors then compare them to make sure there are no repeated terms
	Quicksort(M, 0, M.size() - 1);
	Quicksort(DC, 0, DC.size() - 1);

	if (repetition(M, DC)) return false;
	
	return true;
}

vector<int> seperate(string x) {
    vector<int> terms;
    if(x[0]=='-')return terms;
    string a = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == ',') {
            terms.push_back(stoi(a));
            a = "";
        } else {
            a += x[i];
        }
    }
    if(!a.empty()) // to avoid invalid argument for stoi
        terms.push_back(stoi(a));
    return terms;
}


int main() {
    freopen("testValid.in", "r", stdin);
    freopen("testValidOutput.out", "w", stdout);

    cout << "___________________________________________________________________________________________________\n\n";
    int testCases; cin >> testCases;
    int tc = 1;
    while (testCases--) {
        cout << "Test " << tc++ << "\n"; 
        cout << "---------------------------------------------------------------------------------------------------\n\n";
        int noVariables; 
        cin >> noVariables;
        string minTerms, dontCares; 
        cin >> minTerms >> dontCares;
        vector<int> min_terms = seperate(minTerms), dont_cares = seperate(dontCares);
        if (!validate(noVariables, min_terms, dont_cares)) {
            cout << "Sorry, this is an invalid input\n";
        } else {
            QmAlgo example(noVariables, min_terms, dont_cares);
            example.runAlgo();
        }
        cout << "___________________________________________________________________________________________________\n\n";
    } 
}