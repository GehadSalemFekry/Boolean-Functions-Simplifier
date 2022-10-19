#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>

#include "Implicant.h"
#include "QmAlgo.h"
#include "implicant.h"

using namespace std;

// int Partition(vector<int>& x, int begin, int end) {
// 	int Pivot = begin + (end - begin) / 2;
// 	int PivotValue = x[Pivot];
// 	int i = begin, j = end;
// 	int temp;
// 	while (i <= j) {
// 		while (x[i] < PivotValue) {
// 			i++;
// 		}
// 		while (x[j] > PivotValue) {
// 			j--;
// 		}
// 		if (i <= j) {
// 			temp = x[i];
// 			x[i] = x[j];
// 			x[j] = temp;
// 			i++;
// 			j--;
// 		}
// 	}
// 	return i;
// }

// void Quicksort(vector<int>& x, int begin, int end) {
// 	if (begin < end) {
// 		int Pivot = Partition(x, begin, end);
// 		Quicksort(x, begin, Pivot - 1);
// 		Quicksort(x, Pivot, end);
// 	}
// }

// //checks if there is a repetition in any of the terms of the two vectors
// bool Repetition(vector<int> M, vector<int> DC) {
// 	int i = 0, j = 0;
// 		while (M[i] != NULL && DC[j] != NULL) {
// 			if (M[i] < DC[j])
// 				i++;
// 			else if (M[i] > DC[j])
// 				j++;
// 			else if (M[i] == DC[j])
// 				return true;
// 		}

// 	return false;
// }

// //makes sure that all minterms and don't cares are within range
// bool Validate(int NoV, vector<int> M, vector<int> DC) {
// 	int Total = pow(2, NoV);
// 	for (int i : M) {
// 		if (i > Total) return false;
// 	}

// 	for (int i : DC) {
// 		if (i > Total) return false;
// 	}

// 	//sort the two vectors then compare them to make sure there are no repeated terms
// 	Quicksort(M, 0, M.size() - 1);
// 	Quicksort(DC, 0, DC.size() - 1);

// 	if ((Repetition(M, DC))) {
// 		return false;
// 	}


// 	return true;
// }
int main(){
    // temp x,y;
    // x.a="first",x.b=1;
    // y.a="second",x.b=2;

    // map<temp,bool> mp;

    // mp.insert(x);
    // mp.insert(y);

    // for(auto it=mp.begin(), it!=mp.end();it++){
    //     cout << 
    // }

	QmAlgo test1;

	vector<int> minterms,dontcares;

	minterms.push_back(1);
	minterms.push_back(2);
	minterms.push_back(5);

	dontcares.push_back(0);
	dontcares.push_back(8);

	test1.populateMinterms(4,minterms,dontcares);

	

}