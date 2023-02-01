#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;

class Item {
public:
    int id, benefit, weight;

    Item(int i, int b, int w) : id(i), benefit(b), weight(w) {}
};

class Node {
public:
    int depth, total_benefit, total_weight;
    vector<bool> items_in_bag;

    Node() {}
    Node(int d, int tb, int tw, vector<bool> b) : depth(d), total_benefit(tb), total_weight(tw), items_in_bag(b) {}
};

class BFS {
public:
    Node best_node;
    int max_weight;
    vector<Item> items;


    BFS(int weight_capacity, vector<Item> i) : max_weight(weight_capacity), items(i) {}

    void run() {
        queue<Node> queue;
        Node root, current, take, dont_take;


        queue.push(root);

        while (!queue.empty()) {
            current = queue.front();
            queue.pop();

            if (current.total_benefit > best_node.total_benefit)
                best_node = current;

            if (current.depth < items.size()) {
                vector<bool> updated_bag;

                //Take new item
                if (current.total_weight + items[current.depth].weight <= max_weight) {
                    updated_bag = current.items_in_bag;
                    updated_bag.push_back(true);
                    take = Node(current.depth + 1, current.total_benefit + items[current.depth].benefit, current.total_weight + items[current.depth].weight, updated_bag);
                    queue.push(take);
                }

                //Dont take item
                updated_bag = current.items_in_bag;
                updated_bag.push_back(false);
                dont_take = Node(current.depth + 1, current.total_benefit, current.total_weight, updated_bag);
                queue.push(dont_take);
            }
        }
    }


    void printBest() {
        int index, benefit, weight;
        index = benefit = weight = 0;

        cout << "BFS-SOULTION->\n\n";

        for (bool i : best_node.items_in_bag) {
            if (i) {
                benefit = benefit + items[index].benefit;
                weight = weight + items[index].weight;
                cout << "+ID:" << items[index].id << " B:" << items[index].benefit << " W:" << items[index].weight << "\n";
                cout << "TB:" << benefit << " TW:" << weight << "\n\n";

            }
            index++;
        }
    }

    void printItems() {
        for (Item d : items) {
            cout << d.id << " " << d.benefit << " " << d.weight << "\n";
        }
    }
};

class DFS {
public:
    Node best_node;
    int max_weight;
    vector<Item> items;


    DFS(int weight_capacity, vector<Item> i) : max_weight(weight_capacity), items(i) {}

    void run() {
        stack<Node> stack;
        Node root, current, take, dont_take;


        stack.push(root);

        while (!stack.empty()) {
            current = stack.top();
            stack.pop();

            if (current.total_benefit > best_node.total_benefit)
                best_node = current;

            if (current.depth < items.size()) {
                vector<bool> updated_bag;

                //Take new item
                if (current.total_weight + items[current.depth].weight <= max_weight) {
                    updated_bag = current.items_in_bag;
                    updated_bag.push_back(true);
                    take = Node(current.depth + 1, current.total_benefit + items[current.depth].benefit, current.total_weight + items[current.depth].weight, updated_bag);
                    stack.push(take);
                }

                //Dont take item
                updated_bag = current.items_in_bag;
                updated_bag.push_back(false);
                dont_take = Node(current.depth + 1, current.total_benefit, current.total_weight, updated_bag);
                stack.push(dont_take);
            }
        }
    }


    void printBest() {
        int index, benefit, weight;
        index = benefit = weight = 0;

        cout << "DFS-SOULTION->\n\n";

        for (bool i : best_node.items_in_bag) {
            if (i) {
                benefit = benefit + items[index].benefit;
                weight = weight + items[index].weight;
                cout << "+ID:" << items[index].id << " B:" << items[index].benefit << " W:" << items[index].weight << "\n";
                cout << "TB:" << benefit << " TW:" << weight << "\n\n";

            }
            index++;
        }
    }

    void printItems() {
        for (Item d : items) {
            cout << d.id << " " << d.benefit << " " << d.weight << "\n";
        }
    }
};

int main()
{
    ifstream input_file("knapsack.txt");
    vector<Item> item_list;

    if (input_file) {
        int i, b, w;
        while (input_file) {
            input_file >> i >> b >> w;
            item_list.push_back(Item(i, b, w));
        }
    }
    else {
        cout << "Cant open file.";
    }


    BFS bfs = BFS(420, item_list);
    DFS dfs = DFS(420, item_list);

    auto begin = chrono::high_resolution_clock::now();
    bfs.run();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("BFS: %.6f seconds.\n", elapsed.count() * 1e-9);
    //bfs.printBest();


    begin = chrono::high_resolution_clock::now();
    dfs.run();
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("DFS: %.6f seconds.\n", elapsed.count() * 1e-9);
    //dfs.printBest();

    return 0;
}

