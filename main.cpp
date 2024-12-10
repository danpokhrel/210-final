// COMSC-210 | Final | Dan Pokhrel
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const int SIM_ROUNDS = 10;
const int JOIN_PROB = 50;

struct Customer{
    string name;
    string order;
};

int main(){
    ifstream fin("names.txt");
    vector<string> names;
    while(fin.good()){
        string buf;
        
    }
    
    list<Customer> coffee_booth;

    return 0;
}