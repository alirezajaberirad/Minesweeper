/*#include "mfield.h"#include <random>
using namespace std;

void MField::Tile::landM(){
    if(!hasM)
        hasM=true;
}

bool MField::Tile::HasM() const{
    return hasM
}


MField::MField(int numOfM)
{
    if(numOfM>0 && numOfM<width*height){
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> xDist(0,width-1);
        uniform_int_distribution<int> yDist(0,height-1);
        for(int i=0,i<numOfM;i++){

        }
    }
}
*/
