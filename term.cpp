#include "Term.h"


Term::Term(int variables, int n,bool dontcare){
    this->val=n; // value 


    name="";
    this-> binary = dectoBin(n);
    pad(variables); // padding the binary with zeroes

    int index= binary.length()-1; // start from the end since the binary is read from right to left


    for(int i=0;i<n;i++){ // write the expression in Terms of letters according 
        if(this->binary[index--])
            this->name+=char("A"+i); 
        else{
            this->name+=char("A"+i);
            this->name+='\''; // for negation 
        }
    }

    this->dontCare=dontCare;
}






string Term::dectoBin(int n){
    if(n==0)
        return "0";
    
    if(n%2==0)
        return dectoBin(n/2)+"0";
    
    return dectoBin(n/2)+"1";
}


void Term::pad(int variables){

    int actualLengthBeforePadding = binary.length();
    int zeroesPadded= variables-actualLengthBeforePadding;

    string b="";
    for(int i=0;i<zeroesPadded;i++){
        b+="0";
    }

    b=b+this->binary;

    this->binary=b; // zeroes added to the beginning of the binary 


}


string Term::getBin(){
    return this->binary;
}

string Term::getName(){
    return this->name;
}

int Term::getVal(){
    return this->val;
}

bool Term::isDontCare(){
    return this->dontCare;
}


void Term::replace_complements(string a){
    string temp="";
    for(int i=0;i<(int)a.size();i++){
        if(a[i]!=this->binary[i])
            temp+="-";
        else
            temp+=a[i];
    }

    this->binary=temp;
}


bool Term:: operator ==(const Term& Term1){
    return this->binary==Term1.binary;
}

char& Term:: operator[](int i){
    if(i<this->binary[i]){
        return this->binary[i];}
}

