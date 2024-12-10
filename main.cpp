// COMSC-210 | Final | Dan Pokhrel
#include <iostream>
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

class LinkedList{
private:
    struct Node{
        Customer value;
        Node* next;
        Node (Customer val) {value = val; next = nullptr;}
    };

    Node *head;

public:
    LinkedList() {head = nullptr;}
    ~LinkedList() {
        if (!head) return;

        Node *prev = head, *curr = head;
        while (curr){
            curr = curr->next;
            delete prev;
            prev = curr;
        }
    }

    void push_back(Customer val){
        Node *new_node = new Node(val);
        if (!head)
            head = new_node;
        else{
            Node *curr = head;
            while (curr->next){
                curr = curr->next;
            }
            curr->next = new_node;
        }
    }

    void pop_front(){
        if (!head) return;
        Node *prev = head;
        head = head->next;
        delete prev;
    }

    bool empty() {return !head;}

    struct Iterator {
        Node* curr;

        Iterator(Node* node) {curr = node;}

        Customer& operator*() { return curr->value; }
        Iterator& operator++() {
            curr = curr->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

void read_file(string fname, vector<string> &vec);
string pick_random(vector<string> &vec);
bool probability(int percent);

void print_booths(LinkedList &booth1, deque<Customer> &booth2, vector<Customer> &booth3, map<int, Customer> &booth4);
void print_list(LinkedList &booth);
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
    LinkedList coffee_booth;
    deque<Customer> muffin_booth;
    vector<Customer> bracelet_booth;
    map<int, Customer> pizza_booth;

    // Initialize
    for (int i = 0; i < STARTING; i++){
        // generate random customers
        coffee_booth.push_back({pick_random(names), pick_random(coffee_orders)});
        muffin_booth.push_back({pick_random(names), pick_random(muffin_orders)});
        bracelet_booth.push_back({pick_random(names), pick_random(bracelet_orders)});
        pizza_booth[i+1] = {pick_random(names), pick_random(pizza_orders)};
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
        int x = 0; // key
        if (!pizza_booth.empty()){ // Serve customer at front
            pizza_booth.erase(pizza_booth.begin());
            // Find largest key for insertion
            x = pizza_booth.rbegin()->first;
        }
        if (probability(JOIN_PROB))
            pizza_booth[x+1] = {pick_random(names), pick_random(pizza_orders)};
        
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

void print_booths(LinkedList &booth1, deque<Customer> &booth2, vector<Customer> &booth3, map<int, Customer> &booth4)
{
    print_list(booth1);
    print_deque(booth2);
    print_vector(booth3);
    print_map(booth4);
    cout << endl;
}

void print_list(LinkedList &booth)
{
    if (booth.empty()){
        cout << "<Coffee Booth Empty>\n";
        return;
    }
    cout << "Coffee Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_deque(deque<Customer> &booth)
{
    if (booth.empty()){
        cout << "<Muffin Booth Empty>\n";
        return;
    }
    cout << "Muffin Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_vector(vector<Customer> &booth)
{
    if (booth.empty()){
        cout << "<Bracelet Booth Empty>\n";
        return;
    }
    cout << "Bracelet Booth:\n";
    for (auto customer : booth)
        cout << " > " << customer.name << " - " << customer.order << endl;
}

void print_map(map<int, Customer> &booth)
{
    if (booth.empty()){
        cout << "<Pizza Booth Empty>\n";
        return;
    }
    cout << "Pizza Booth:\n";
    for (auto pair : booth)
        cout << " > " << pair.second.name << " - " << pair.second.order << endl;
}
