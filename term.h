#ifndef TERM_H
#define TERM_H

#include <fstream>
#include <map>
#include <set>

using namespace std;

class Term{
    string name; // e.g., A'BCD --> 0111
    string binary; // 0111
    bool dontCare; // true if Term is a don't care
    int val;


    void pad(int n); // pad the binary representation of the Term with zeroes according to the number of bits
public:
    Term(int variables, int n,bool dontcare); // paramterized constructor


    string dectoBin(int n); // convert a decimal to a binary


    string getName();
    string getBin();
    bool isDontCare();
    int getVal();


    void replace_complements(string a); // replace the two differeing digits  with "-"

    bool operator ==(const Term& Term1); // check if two Terms are equivalent
    char& operator [](int i);

};


#endif