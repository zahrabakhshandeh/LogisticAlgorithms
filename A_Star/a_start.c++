#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>


using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private:
    int numNodes;
    vector<vector<pair<int, int>>> adjList;
    
public:
    Graph(int nodes) : numNodes(nodes) {
        adjList.resize(numNodes);
    }
    
    void addEdge(int i, int j, int weight) {
        adjList[i].emplace_back(j, weight);
        adjList[j].emplace_back(i, weight); 
    }

    vector<int> aStar(int start, int goal, vector<int>& h){
        vector<int> g(numNodes, INF);
        vector<int> f(numNodes, INF);
        vector<int> parent(numNodes, -1);
        g[start] = 0;
        f[start] = h[start];

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>pq;
        pq.emplace(f[start], start);

        while(!pq.empty()){
            int currentNode = pq.top().second();
            pq.pop();
            if(currentNode == goal) {
                break;
            }

        }



    }

    void display() {
        for (int i = 0; i < numNodes; ++i) {
            cout << "Node: " << i << endl;
            for (auto& n : adjList[i]) {
                cout << "To: " << n.first << ", Weight: " << n.second << endl;
            }
        }
    }
};

int main() {
    int numNodes = 4; // Example with 4 nodes (A, B, C, D)
    Graph graph(numNodes);
    graph.addEdge(0, 1, 1); // A -- B (weight 1)
    graph.addEdge(0, 2, 3); // A -- C (weight 3)
    graph.addEdge(1, 3, 1); // B -- D (weight 1)
    graph.addEdge(2, 3, 1); // C -- D (weight 1)

    vector<int> h = {3, 2, 1, 0}; // Heuristic values for each node

    int start = 0; // Start from A
    int goal = 3; // Goal is D

    vector<int> path = graph.aStar(start, goal, h);

    return 0;
}

// B---1----> A
// C---3----> A
// D---1----> B
// D---1----> C
// A ??? D
// h(A) = 3, h(B) = 2, h(c) = 1, h(D) = 0
// step1:
// open = [(3, A)], close = []
// 0 + 3 = 3
// step2:
// open=[B, C], close=[A]
// B = 1 + 2 = 3 , C = 3 + 1 = 4
// f = g + h
// step3:
// open=[C, D], close=[A, B]
// C = 1 + 3 = 4, D = 0 + 1 + 1 = 2 =====> h(D) + 1 + 1
// step4:
// open=[C], close[A, B, D]