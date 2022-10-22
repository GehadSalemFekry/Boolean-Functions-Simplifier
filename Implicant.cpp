#include "Implicant.h"


Implicant::Implicant(int variables, int n){
    this->noVariables = variables;
    this->binary = dectoBin(n);
    pad(variables); // padding the binary with zeroes

    generateName();
    coveredTerms.insert(n);
}

Implicant::Implicant(string x, set<int> coveredTerms) {
    this->binary = x;
    this->noVariables = x.size();
    this->coveredTerms = coveredTerms;
    generateName();
}


Implicant::Implicant(const Implicant& imp){
    this->binary = imp.binary;
    this->name = imp.name;
    this->coveredTerms = imp.coveredTerms;
    this->noVariables = imp.noVariables;
    generateName();
}

void Implicant::generateName() {
    name = "";

    for(char c = 'A'; c < char('A'+ noVariables); c++){ // write the expression in Implicants of letters
        int idx = c - 'A';
        if (binary[idx] != '-') {
            name += c;
            if(binary[idx] == '0'){
                name += '\'';
            }
        }
    }
}


string Implicant::dectoBin(int n){
    if(n == 0)
        return "0";
    
    if(n % 2 == 0)
        return dectoBin(n/2)+"0";
    
    return dectoBin(n/2)+"1";
}


void Implicant::pad(int variables){
    if (binary.length() > variables) {
        binary = binary.substr(1, binary.size() - 1);
        return;
    }

    int actualLengthBeforePadding = binary.length();
    int zeroesPadded= variables-actualLengthBeforePadding;

    string b = "";
    for(int i = 0;i < zeroesPadded; i++){
        b += "0";
    }

    b = b + this->binary;

    this->binary=b; // zeroes added to the beginning of the binary 
}


string Implicant::getBin(){
    return binary;
}

string Implicant::getName(){
    return name;
}


string Implicant::replace_complements(int idx){
    string temp = binary;
    temp[idx] = '-';
    return temp;
}

bool Implicant:: operator ==(const Implicant& Implicant1){
    return this->binary == Implicant1.binary;
}

char& Implicant:: operator[](int i){
    return this->binary[i];
}

bool Implicant:: operator <(const Implicant& Implicant1){
    return this->binary<Implicant1.binary;
}

void Implicant::addTerm(int num){
    coveredTerms.insert(num);
}

int Implicant::getNoTerms(){
    return this->coveredTerms.size();
}


set<int> Implicant::getCoveredTerms(){
    return this->coveredTerms;
}

void Implicant::changeBit(int i){
    if(this->binary[i] == '0')
        this->binary[i] = '1';
    else
        this->binary[i] = '0';
}

