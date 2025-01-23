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
        // [[(),(),()],[],[]]
        adjList[j].emplace_back(i, weight); 
    }

    vector<int> calculateHeuristics(int goal){
        vector<int> h(numNodes, INF);
        queue<int> q;
        h[goal] = 0;
        q.push(goal);

        while(!q.empty()){
            int current = q.front();
            q.pop();

            for(const auto& n : adjList[current]){
                int nextNode = n.first;
                if (h[nextNode] == INF){
                    h[nextNode] = h[current] + 1;
                    q.push(nextNode);
                }

            }
        }
        return h;
    }

    vector<int> aStar(int start, int goal, vector<int>& h){
        vector<int> g(numNodes, INF);
        vector<int> f(numNodes, INF);
        vector<int> parent(numNodes, -1);
        // [-1, -1, -1, -1]
        g[start] = 0;
        f[start] = h[start];

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>pq;
        pq.emplace(f[start], start);

        while(!pq.empty()){
            int currentNode = pq.top().second;
            pq.pop();
            if(currentNode == goal) {
                break;
            }
            for(const auto& n : adjList[currentNode]){
                int nextNode = n.first;
                int edgeWight = n.second;
                int totalWight = edgeWight + g[currentNode];
                int f1 = totalWight + h[nextNode];
                if (f1 < f[nextNode]){
                    g[nextNode] = totalWight;
                    f[nextNode] = g[nextNode] + h[nextNode];
                    // f(n) = g(n) + h(n)
                    parent[nextNode] = currentNode;
                    pq.emplace(f[nextNode], nextNode);
                    // [-1, C, -1, -1]
                    //   0   1  2   3
                }
            }
        }
        vector<int> path;
        int current = goal;
        while(current != -1){
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        cout << "path from: " << start << " to "<< goal<<endl;
        for(int n : path){
            cout << n << ", ";
        }
        return g;
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

    //vector<int> h = {3, 2, 1, 0}; // Heuristic values for each node
    int start = 0; // Start from A
    int goal = 3; // Goal is D
    vector<int> h = graph.calculateHeuristics(goal);
    cout << "H: " <<endl;
    for(int i : h){
        cout << i << ", ";
    }

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

// A ----> D ----> C   ===> g(C) = INF ====> 9
// A ----> B ----> C   ===> 12 

// B---1----> A
// C---3----> A
// D---1----> B
// D---1----> C

// h = [INF, InF, INF, 0]
// q = [D]

// current = D 
// B, C
// B ====> h[B] = h[D] + 1 = 1
// C ====> h[C] = h[D] + 1 = 1
// h = [INF, 1, 1, 0]
// q = [B, C]

// current = B
// D, A 
// A ====> h[A] = h[B] + 1 = 2
// h = [2, 1, 1, 0]

// A --1--> B -----> C ------> F -------> D
// A ---2---> E -----> D