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

    set<int> coveredTerms;

    void pad(int n); // pad the binary representation of the Implicant with zeroes according to the number of bits
public:
    Implicant(int variables, int n); // paramterized constructor
    Implicant(string string, set<int> coveredTerms);

    Implicant(const Implicant& imp);
    string dectoBin(int n); // convert a decimal to a binary


    void setName();

    string getName();
    string getBin();
    int getNoTerms();

    void addTerm(int num);



    set<int> getCoveredTerms();

    string replace_complements(int idx); // replace the two differeing digits  with "-"

    void changeBit(int i);

    bool operator ==(Implicant& Implicant1); // check if two Implicants are equivalent
    bool operator <(Implicant& Implicant);
    char& operator [](int i);



};


#endif