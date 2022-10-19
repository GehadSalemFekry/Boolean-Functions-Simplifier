#ifndef Implicant_H
#define Implicant_H
#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

class Implicant{
    string name; // e.g., A'BCD, which is equivalent to 0111
    string binary; // 0111
    bool dontCare; // true if object is a don't care
    int val;

    set<int> coveredImplicants;

    void pad(int n); // pad the binary representation of the Implicant with zeroes according to the number of bits
public:
    Implicant(int variables, int n, bool dontcare); // paramterized constructor
    Implicant(string string);

    string dectoBin(int n); // convert a decimal to a binary

    string getName();
    string getBin();
    bool isDontCare();
    int getVal();
    int getNoImplicants();

    void addImplicant(int num);



    set<int> getCoveredImplicants();

    string replace_complements(int idx); // replace the two differeing digits  with "-"

    void changeBit(int i);

    bool operator ==(Implicant& Implicant1); // check if two Implicants are equivalent
    char& operator [](int i);

};


#endif