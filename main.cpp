#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include <map>

using namespace std;

// struct temp{
//     string a;
//     int b;
// };

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
bool Repetition(vector<int> M, vector<int> DC) {
	int i = 0, j = 0;
		while (M[i] != NULL && DC[j] != NULL) {
			if (M[i] < DC[j])
				i++;
			else if (M[i] > DC[j])
				j++;
			else if (M[i] == DC[j])
				return true;
		}

	return false;
}

//makes sure that all minterms and don't cares are within range
bool Validate(int NoV, vector<int> M, vector<int> DC) {
	int Total = pow(2, NoV);
	for (int i : M) {
		if (i > Total) return false;
	}

	for (int i : DC) {
		if (i > Total) return false;
	}

	//sort the two vectors then compare them to make sure there are no repeated terms
	Quicksort(M, 0, M.size() - 1);
	Quicksort(DC, 0, DC.size() - 1);

	if ((Repetition(M, DC))) {
		return false;
	}


	return true;
}
int main(){

	ifstream in;
	int NumberofVariables;
    vector<int> Minterms;
	vector<int> DontCares;
	string line;
	string number;

	in.open("test.txt");
	if (in.is_open()) {

		//Read the number of variables in the first line and convert it to int
		getline(in, line);
		NumberofVariables = stoi(line);

		//Read the minterms in the second line and convert it to int
		getline(in, line);
		for (int i = 0; i < line.size(); i++) {
			while (line[i] != ',' && line[i] != NULL) {
				number.push_back(line[i]);
				i++;
			}

			if (!number.empty()) {
				Minterms.push_back(stoi(number));
				number.erase();
			}
		}

		number.erase();

		//Read the don't cares in the third line and convert it to int
		getline(in, line);
		for (int i = 0; i < line.size(); i++) {
			while (line[i] != ',' && line[i] != NULL) {
				number.push_back(line[i]);
				i++;
			}

			if (!number.empty()) {
				DontCares.push_back(stoi(number));
				number.erase();
			}
		}

	}
	else cout << "File can't open";

	cout << "Number of Variables: " << NumberofVariables << endl << "Minterms: ";

	for (int i : Minterms)
	{
		cout << i << ", ";
	}

	cout << endl << "Don't cares: ";
	for (int i : DontCares)
	{
		cout << i << ",";
	}

	cout << endl;
	if (Validate(NumberofVariables, Minterms, DontCares)) cout << "valid";
	else cout << "not valid";


    // temp x,y;
    // x.a="first",x.b=1;
    // y.a="second",x.b=2;

    // map<temp,bool> mp;

    // mp.insert(x);
    // mp.insert(y);

    // for(auto it=mp.begin(), it!=mp.end();it++){
    //     cout << 
    // }

    // int n;
    // cin >> n;
    // string name="";
    //cout << char('A'+1);
    // for(int i=0;i<n;i++){
    //     name+="A"+i;
    // }
    // cout << name << '\n';

}