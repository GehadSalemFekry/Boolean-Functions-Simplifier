#include "QmAlgo.h"

QmAlgo::QmAlgo(string in){
    fileName= in;
}




void QmAlgo::reduce(){
    

    int stringSize= variables;
    for(auto it=Implicants.begin();it!=Implicants.end();it++){
        Implicant& imp = it->first; // to easily traverse the implicant
        Implicant temp= it->first; // to change its bits and check its availability in the map
        for(int i=0; i<variables;i++){
            if(imp[i]=='0'){
                temp.changeBit(i);
                if(Implicants[temp]){
                    // found an implicant that differs by on digit





                    break;
                }


                temp.changeBit(i);
            }
        }
    }
}