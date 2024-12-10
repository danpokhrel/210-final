// COMSC-210 | Final | Dan Pokhrel
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <random>
using namespace std;

const int SIM_ROUNDS = 10, STARTING = 300, JOIN_PROB = 50;

struct Customer{
    string name;
    string order;
};

void read_file(string fname, vector<string> &vec);
string pick_random(vector<string> &vec);

int main(){
    srand(time(0));

    // Database variables
    vector<string> names;
    vector<string> coffee_orders;
    vector<string> muffin_orders;
    vector<string> bracelet_orders;
    vector<string> pizza_orders;

    // Read data files into variables
    read_file("names.txt", names);
    read_file("coffee.txt", coffee_orders);
    read_file("muffin.txt", muffin_orders);
    read_file("bracelet.txt", bracelet_orders);
    read_file("pizza.txt", pizza_orders);

    // Structs
    list<Customer> coffee_booth;

    // Initialize
    for (int i = 0; i < STARTING; i++){
        // generate random customer
        Customer customer = {pick_random(names), pick_random(coffee_orders)};
        coffee_booth.push_back(customer);
    }

    return 0;
}

void read_file(string fname, vector<string> &data)
{
    ifstream fin(fname);
    if (!fin.good()){
        cout << "Failed to open file <" << fname << ">";
        return;
    }
    while(fin.good()){
        string buf;
        getline(fin, buf);
        data.push_back(buf);
    }
}

string pick_random(vector<string> &vec)
{
    int i = rand() % vec.size();
    cout << vec[i] << endl;
    return vec[i];
}
