#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;

bool he(vector<string> h, string a) {
    for (string d : h) {
        if(d == a)
            return true;
    }
    return false;
}


class CityAndDistance {
public:
    string name;
    int distance;

    
    CityAndDistance(string n, int d) : name(n), distance(d) {}
};

class City {
public:
    string city_name;
    int distance_to_goal;
    vector<CityAndDistance> connections;
    
    City() {}
    City(string c, int d) : city_name(c), distance_to_goal(d) {}

};



class Node {
public:
    Node* parent;
    int cost;
    int depth;
    City city;
    
    Node(){}
    Node(Node * n, int c, int d) : parent(n), cost(c), depth(d) {}
    Node(Node* n, int c, int d, City ci) {
        parent = n;
        cost = c;
        depth = d;
        city = ci;
    }

    
};

bool operator<(const Node& left, const Node& right) {
    return left.cost > right.cost;
}

bool operator>(const Node& left, const Node& right) {
    return left.cost > right.cost;
}



class Greedy {
public:
   
    Node start;
    vector<City> city_list;
    
    Greedy(){}
    Greedy(const Node s, vector<City> c) {
        start = s;
        city_list = c;
    }

    Node run() {
        
        
        priority_queue<Node> open;
        
        vector<string> clossed;

        Node temp = start;

        open.push(temp);

        while (!open.empty()) {
            Node current = open.top();

            cout << current.city.city_name << "\n";
            if (current.city.city_name == "Valladolid")
                return current;

            open.pop();


            for (CityAndDistance c : current.city.connections) {
                //cout << c.name << "\n";
                if (!he(clossed, c.name)){
                    
                for (City ci : city_list) {
                    
                        
                    if (c.name == ci.city_name)
                        if (current.parent == NULL) {
                            //cout << ci.city_name << "\n";
                            open.push(Node(&current, c.distance, current.depth + 1, ci));
                            clossed.push_back(current.city.city_name);
                            break;
                        }
                        else{
                            if(c.name != current.parent->city.city_name)
                                //cout << ci.city_name << "\n";
                                open.push(Node(&current, c.distance, current.depth + 1, ci));
                                clossed.push_back(current.city.city_name);
                                break;
                        }
                }
                }
            }


        }
        
    }
};













/*
class Greedy{
public:
    Node start;
    Node current;
    vector<City> city_list;
    vector<City> clossed;
    priority_queue<Node> open;

    Greedy(Node s, Node a) : start(s), current(a) {}
    
    Node run() {
        open.push(start);
        
        while (!open.empty()) {
            current = open.top();

            if (current.city.city_name == "Valladolid")
                return current;

            open.pop();

            
            for (CityAndDistance c : current.city.connections) {
                for (City ci : city_list) {
                    if (c.name == ci.city_name)
                        open.push(Node(&current, c.distance, current.depth + 1, ci));
                }



            }
            

        }
        

        return start;
        

    }
    
};
*/





int main()
{
    ifstream input_file("d.txt"), input("c.txt");

    vector<City> city_list;

    if (input_file) {   
        int b;
        string i;

        while (input_file) {
            input_file >> i >> b;
            city_list.push_back(City(i, b));
        }
    }
    else {
        cout << "Cant open file.";
    }

    string cityA, cityB;
    int distance;

    if (input) {
        while(input){
            input >> cityA >> cityB >> distance;
            for (int a = 0; a < city_list.size(); a++) {
                if (city_list[a].city_name == cityA)
                    city_list[a].connections.push_back(CityAndDistance(cityB, distance));      
            
                if (city_list[a].city_name == cityB)
                    city_list[a].connections.push_back(CityAndDistance(cityA, distance));
            }
        }        
    }
    else {
        cout << "Cant open file.";
    }


    //cout << city_list.front().connections.front().name << " " << city_list.front().connections.front().distance << "\n";

    //cout << city_list[1].connections.front().name << " " << city_list[1].connections.front().distance << "\n";

    //for (CityAndDistance x : city_list[1].connections) {
        //cout << x.name << " " << x.distance << "\n";
    //}

   
    City y;

    for (City x : city_list)
        if (x.city_name == "Malaga") {
            //cout << x.city_name << "\n";
            y = x;
            break;
        }


    Node banana = Node(NULL, 0, 0, y);
   

    
    Greedy greedy = Greedy(banana, city_list);
    
    Node sol = greedy.run();
    
    //cout << greedy.start.city.city_name << "\n";



    return 0;
}


