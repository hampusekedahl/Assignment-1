#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include<sstream>

using namespace std;

int getNumberFromString(string s) {
    stringstream str_strm;
    str_strm << s;
    string temp_str;
    int temp_int;
    while(!str_strm.eof()) {
        str_strm >> temp_str;
        if(stringstream(temp_str) >> temp_int) {
            return temp_int;
        }
    }
    return 0;
}

class Node{
public:
    int depth, weight, benefit;
    vector<bool> itemsInBag;
    
    Node() {depth = 0; weight = 0; benefit = 0;}
    Node(int depth, int weight, int benefit, vector<bool> & itemsInBag) : depth(depth), weight(weight), benefit(benefit), itemsInBag(itemsInBag) {}
    
};

class BFS{
public:
    int maxWeight;
    Node solution;
    
    BFS(int max) : maxWeight(max) {}
    
    void run(vector<pair<int, int>> itemsList){
        queue<Node> queue;
        Node root, optimal, current, add, empty;
        queue.push(root);
        
        while(!queue.empty()){
            current = queue.front();
            queue.pop();
            
            if(current.benefit > optimal.benefit)
                optimal = current;
            
            if(current.depth < itemsList.size()){
                
                vector<bool> temp;
                temp = current.itemsInBag;
                temp.push_back(true);
                add = Node(current.depth+1, current.weight + itemsList[current.depth].first, current.benefit + itemsList[current.depth].second, temp);
                
                if(add.weight <= maxWeight)
                    queue.push(add);
                
                temp = current.itemsInBag;
                temp.push_back(false);
                empty = Node(current.depth+1, current.weight, current.benefit, temp);
                
                queue.push(empty);
                
            }
        }
        solution = optimal;
    }
};

class DFS{
    
    void run(vector<pair<int, int>>){
        
    }
};

int main(int argc, const char * argv[]) {
    
    /*
    ifstream inputFile("Assignment 1 knapsack.txt");
    
    vector<pair<int, int>> itemList;

    if(inputFile){
        string inputStr;
        
        
        for(int i = 0; i < 7; i++)
            getline(inputFile, inputStr);
        
        int id, weight, benefit;
        inputFile >> id >> weight >> benefit;
        while(inputFile){
            itemList.push_back(make_pair(benefit, weight));
            inputFile >> id >> weight >> benefit;
        }
    }
    else{
        cout << "'Assignment 1 knapsack.txt' could't be opened.";
    }
    
    BFS bfs = BFS(420);
    bfs.run(itemList);
    cout << bfs.solution.weight << " "<< bfs.solution.benefit;
    */
    
    vector<pair<int, int>> itemList;
    int maxWeight = 0, numberOfItems = 0;
    
    
    string fileName = "Assignment 1 knapsack.txt";
    ifstream inputFile(fileName);

    string line;
    
    if(inputFile){
        
        while(getline(inputFile, line))
        {
            if (line.find("ID b w") != string::npos){
                break;
            } else if (line.find("DIMENSION") != string::npos) {
                numberOfItems = getNumberFromString(line);
                
            } else if (line.find("MAXIMUM WEIGHT") != string::npos) {
                maxWeight = getNumberFromString(line);
            }
            cout << line;
        }
        
        int id, weight, benefit;
        inputFile >> id >> weight >> benefit;
        while(inputFile){
            itemList.push_back(make_pair(benefit, weight));
            inputFile >> id >> weight >> benefit;
        }
        
        
    } else {
        cout << "'" << fileName << "' could't be opened.";
    }
    
    BFS bfs = BFS(maxWeight);
    bfs.run(itemList);
    cout << bfs.solution.weight << " " << bfs.solution.benefit;

    return 0;
}


