// muliple-files/averageMain.cpp -- Print above average numbers.
//      Illustrates multiple source file compilations.
// Fred Swartz -- 2004-11-17

//... Standard includes
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

//... Private include for average function.
#include "average.h"

//=========================================================== main
int main(){
    
    vector<float> fv;    // Store the input floats here.
    float         temp;  // Temp for input.
    
    //... Read floats into vector
    /*while (cin >> temp) {
        fv.push_back(temp);
    } */  

    fv.push_back(1.0);
    fv.push_back(2.0);
    fv.push_back(2.5);
    fv.push_back(3.5);
    fv.push_back(4.5);
    fv.push_back(10);
    fv.push_back(12);
    fv.push_back(8.0);
    fv.push_back(9.0);
    
    //... Compute average.
    float avg = average(fv); 
  
    //... Print greater than average numbers.
    cout << "Average = " << avg << endl;
    for (int i = 0; i < fv.size(); i++) {
        if (fv[i] > avg) {
            cout << fv[i] << endl;
        }
    }      
	
    return 0;
}

