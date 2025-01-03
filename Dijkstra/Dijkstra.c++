#include <iostream>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph{
private:
    int numNodes;
    vector<vector<pair<int, int>>> djList;
public:
    Graph(int nodes) : numNodes(nodes){
        djList.resize(numNodes);
    }
    
    void addEdge(int i, int j, int weight){
        djList[i].emplace_back(j, weight);
        djList[j].emplace_back(i, weight);
    }

    vector<int> dijkstra(int start){
        vector<int> distances(numNodes, INF);
        distances[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, start);

        while(!pq.empty()){

        }

        return distances;

    }

    void display(){
        for(int i=0; i < numNodes; ++i){
            cout << "Node: " << i <<endl;
            for(auto& n: djList[i]){
                cout << "To: "<< n.first << ", Weight: "<< n.second<<endl;
            }
        }
    }

};

int main(){
    int numNodes = 6;

    Graph graph(numNodes);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    graph.display();
    return 0;
}

// A ---2----> B
// A ---5----> C
// B ---1----> C
// ditances = [0, +, +]
// list = [(0, A)]
// list = [(2, B), (5, C)]
// list = [(3, C), (5, C)]
// list = [(5, C)]
// list = []
// [0, 2, 3]
