#ifndef Implicant_H
#define Implicant_H
#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

class Implicant{
public:
    string name; // e.g., A'BCD, which is equivalent to 0111
    string binary; // 0111 equivalent to the name
    int noVariables;
    set<int> coveredTerms;

    Implicant();
    Implicant(int variables, int n); // paramterized constructor
    Implicant(string string, set<int> coveredTerms);
    Implicant(const Implicant& imp);

    void setName();
    void addTerm(int num); //adds a term to the coveredterms set

    void generateName();
    string getName();
    string getBin();
    int getNoTerms();  //gets the number of covered terms
    set<int> getCoveredTerms();

    void pad(int n); // pad the binary representation of the Implicant with zeroes according to the number of bits
    string dectoBin(int n); // convert a decimal to a binary
    string replace_complements(int idx); // replace the two differeing digits  with "-"
    void changeBit(int i);  //takes the index of the digit we want to change and changes it to its complement

    bool operator ==(const Implicant& Implicant1); // check if two Implicants are equivalent
    bool operator <(const Implicant& Implicant);
    char& operator [](int i);
};


#endif