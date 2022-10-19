#include "Implicant.h"


Implicant::Implicant(int variables, int n,bool dontcare){
    this->val=n; // value 


    this-> binary = dectoBin(n);
    pad(variables-1); // padding the binary with zeroes

    int index= binary.length()-1; // start from the end since the binary is read from right to left

    this->name="";

    for(char i='A';i<char(65+variables+1);i++){ // write the expression in Implicants of letters according ('A'-->65)
        this->name+=i;
        if(this->binary[index--]=='0'){
            this->name+='\'';
        }
    }

    this->dontCare=dontCare;
}






string Implicant::dectoBin(int n){
    if(n==0)
        return "0";
    
    if(n%2==0)
        return dectoBin(n/2)+"0";
    
    return dectoBin(n/2)+"1";
}


void Implicant::pad(int variables){

    int actualLengthBeforePadding = binary.length();
    int zeroesPadded= variables-actualLengthBeforePadding;

    string b="";
    for(int i=0;i<zeroesPadded;i++){
        b+="0";
    }

    b=b+this->binary;

    this->binary=b; // zeroes added to the beginning of the binary 


}


string Implicant::getBin(){
    return binary;
}

string Implicant::getName(){
    return name;
}

int Implicant::getVal(){
    return val;
}

bool Implicant::isDontCare(){
    return dontCare;
}


void Implicant::replace_complements(string a){
    string temp="";
    for(int i=0;i<(int)a.size();i++){
        if(a[i]!=this->binary[i])
            temp+="-";
        else
            temp+=a[i];
    }

    this->binary=temp;
}


bool Implicant:: operator ==(Implicant& Implicant1){
    return this->binary==Implicant1.binary;
}

char& Implicant:: operator[](int i){
    return this->binary[i];
}

void Implicant::addTerm(int num){
    coveredImplicants.insert(num);
}

int Implicant::getNoImplicants(){
    return this->noImplicants;
}


set<int> Implicant::getCoveredImplicants(){
    return this->coveredImplicants;
}


void Implicant::changeBit(int i){
    if(this->binary[i]=='0')
        this->binary[i]='1';
    else
        this->binary[i]='0';
}

