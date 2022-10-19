#include <iostream>
#include <map>

#include "Implicant.h"
#include "implicant.h"

// struct temp{
//     string a;
//     int b;
// };
using namespace std;

int main(){
    int vars, n;
    cin >> vars >> n;
    while(n!=-1){
        Implicant t1(vars,n,false);
        cout << "Implicant Name: " << t1.getName() << '\n';
        cout << "Implicant Binary: " << t1.getBin() << '\n';
        cout << "Implicant Value: " << t1.getVal() << '\n';
        cin >> vars >> n;
    }

}