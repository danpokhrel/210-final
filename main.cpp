// COMSC-210 | Final | Dan Pokhrel
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <deque>
#include <map>
using namespace std;

const int SIM_ROUNDS = 10, STARTING = 3, JOIN_PROB = 50;

struct Customer{
    string name;
    string order;
};

void read_file(string fname, vector<string> &vec);
string pick_random(vector<string> &vec);
bool probability(int percent);

void print_booths(list<Customer> &booth1, deque<Customer> &booth2, vector<Customer> &booth3, map<int, Customer> &booth4);
void print_list(list<Customer> &booth);
void print_deque(deque<Customer> &booth);
void print_vector(vector<Customer> &booth);
void print_map(map<int, Customer> &booth);

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
    deque<Customer> muffin_booth;
    vector<Customer> bracelet_booth;
    map<int, Customer> pizza_booth;

    // Initialize
    for (int i = 0; i < STARTING; i++){
        // generate random customers
        coffee_booth.push_back({pick_random(names), pick_random(coffee_orders)});
        muffin_booth.push_back({pick_random(names), pick_random(muffin_orders)});
        bracelet_booth.push_back({pick_random(names), pick_random(bracelet_orders)});
        pizza_booth[i] = {pick_random(names), pick_random(pizza_orders)};
    }
    cout << "--- Initial Booths ---\n";
    print_booths(coffee_booth, muffin_booth, bracelet_booth, pizza_booth);
    
    // Simulate
    for (int i = 0; i < SIM_ROUNDS; i++){
        // coffee booth
        if (!coffee_booth.empty()) // Serve customer at front
            coffee_booth.pop_front();
        if (probability(JOIN_PROB))
            coffee_booth.push_back({pick_random(names), pick_random(coffee_orders)});

        // muffin booth
        if (!muffin_booth.empty()) // Serve customer at front
            muffin_booth.pop_front();
        if (probability(JOIN_PROB))
            muffin_booth.push_back({pick_random(names), pick_random(muffin_orders)});
            
        // bracelet booth
        if (!bracelet_booth.empty()) // Serve customer at front
            bracelet_booth.erase(bracelet_booth.begin());
        if (probability(JOIN_PROB))
            bracelet_booth.push_back({pick_random(names), pick_random(bracelet_orders)});

        // pizza booth
        if (!pizza_booth.empty()){ // Serve customer at front
            // Find largest key
            int x = 
        }
        
        cout << "--- Iteration " << i+1 << " ---\n";
        print_booths(coffee_booth, muffin_booth, bracelet_booth, pizza_booth);
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
    return vec[i];
}

bool probability(int percent)
{
    return rand()%100+1 <= percent;
}

void print_booths(list<Customer> &booth1, deque<Customer> &booth2, vector<Customer> &booth3, map<int, Customer> &booth4)
{
    print_list(booth1);
    print_deque(booth2);
    print_vector(booth3);
    print_map(booth4);
    cout << endl;
}

void print_list(list<Customer> &booth)
{
    cout << "Coffee Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_deque(deque<Customer> &booth)
{
    cout << "Muffin Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_vector(vector<Customer> &booth)
{
    cout << "Bracelet Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_map(map<int, Customer> &booth)
{
    cout << "Pizza Booth:\n";
    for (auto pair : booth)
        cout << " > " << pair.first << " | " << pair.second.name << " - " << pair.second.order << endl;
}
