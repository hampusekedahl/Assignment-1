#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;



class CityAndDistance {
public:
    string name;
    int distance;

    CityAndDistance(string n, int d) : name(n), distance(d) {}
};

class CityInfo {
public:
    int straight_line_distance;
    vector<CityAndDistance> connections;

    CityInfo() {}
    CityInfo(int straight_line) : straight_line_distance(straight_line) {}
};

class Node {
public:
    Node* parent_node;
    string city_name;
    int depth, cost;

    Node() {}
    Node(Node* parent, string name, int d, int c) {
        parent_node = parent;
        city_name = name;
        depth = d;
        cost = c;
    }
};

bool operator<(const Node& left, const Node& right) {
    return left.cost > right.cost;
}

class Greedy {
public:

    Node* start;
    unordered_map<string, CityInfo> umap;

    Greedy() {}
    Greedy(string name, CityInfo info, unordered_map<string, CityInfo> map) {
        start = new Node(NULL, name, 0, info.straight_line_distance);
        umap = map;
    }

    Node run() {


        priority_queue<Node> open_list;
        unordered_map<string, int> closed_list;

        //Node temp = start;

        

        open_list.push(*start);

        

        while (!open_list.empty()) {
            Node * current = new Node(open_list.top().parent_node, open_list.top().city_name, open_list.top().depth, open_list.top().cost);
            open_list.pop();

            //cout << current->city_name << "\n";

            if (current->city_name == "Valladolid")
                return *current;


            Node * temp;
            for (CityAndDistance c : umap[current->city_name].connections) {
                
                if (closed_list.count(c.name) == 0) {
                    if (current->parent_node == NULL) {
                        temp = new Node(current, c.name, current->depth+1, umap[c.name].straight_line_distance);
                        open_list.push(*temp);
                        closed_list[c.name] = 0;
                    }
                    else {
                        if (c.name != current->parent_node->city_name) {
                            temp = new Node(current, c.name, current->depth + 1, umap[c.name].straight_line_distance);
                            open_list.push(*temp);
                            closed_list[c.name] = 0;
                        }
                    }
                }
            }
        }
        //return start; 
    }
};

int main()
{
    ifstream a_b_distance_file("connectionsDistance.txt"), straight_line_distances_file("straightLine.txt");
    unordered_map<string, CityInfo> umap;

    if (straight_line_distances_file) {
        string city_name;
        int straight_line_distance;

        while (straight_line_distances_file) {
           
            straight_line_distances_file >> city_name >> straight_line_distance;
            umap[city_name] = CityInfo(straight_line_distance);
        }

       

    }
    else {
        cout << "straightLine.txt couldn't be opened.";
    }

    if (a_b_distance_file) {
        string city_name_a, city_name_b;
        int distance_between;

        while (a_b_distance_file) {
            a_b_distance_file >> city_name_a >> city_name_b >> distance_between;
            umap[city_name_a].connections.push_back(CityAndDistance(city_name_b, distance_between));
            umap[city_name_b].connections.push_back(CityAndDistance(city_name_a, distance_between));
        }
    }
    else {
        cout << "connectionsDistance.txt couldn't be opened.";
    }


    Greedy greedy = Greedy("Malaga", umap["Malaga"], umap);
    Node soultion = greedy.run();

    cout << soultion.city_name << "\n";
    Node temp = *soultion.parent_node;
    while (temp.parent_node != NULL) {
        cout << temp.city_name << "\n";
        temp = *temp.parent_node;
    }
//550


//206+192+75+202+66+100 == 841  -> 291 diff
}

